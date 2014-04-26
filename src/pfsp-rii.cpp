#include <iostream>
#include <fstream>

#include "lib/io.hpp"
#include "lib/error/exception.hpp"

#include "pfsp/io/parse/body.hpp"
#include "pfsp/io/parse/header.hpp"
#include "pfsp/mem/allocate.hpp"

#include "pfsp_rii/global.hpp"
#include "pfsp_rii/config.hpp"

using namespace pfsp_rii;


void run(){

// PARSE INPUT
	
	std::ifstream fileIn;
	fileIn.open(global::params[0]);

	if(!fileIn.is_open()) throw lib::error::exception("Could not open input file");

	pfsp::io::parse::header(fileIn, global::i.nbJob, global::i.nbMac);
	pfsp::mem::allocate(global::i.processing, global::i.dueDates, global::i.priority, global::i.nbJob, global::i.nbMac);
	global::proxy.resize(&global::i.processing[0], global::i.nbJob + 1, global::i.nbMac + 1);
	pfsp::io::parse::body(fileIn, global::i.nbJob, global::i.nbMac, global::proxy, global::i.dueDates, global::i.priority);

	fileIn.close();

	if(global::verbose){
		std::cout << "Number of jobs : " << global::i.nbJob << std::endl;
		std::cout << "Number of machines : " << global::i.nbMac << std::endl;
	}


// INIT EVAL

	E e(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::proxy);
	TE te(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::proxy, e.wt, e.detail);
	IE ie(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::proxy, e.wt, e.detail);
	EE ee(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::proxy, e.wt, e.detail);
	global::transpose.eval =  &te;
	global::insert.eval = &ie; 
	global::exchange.eval = &ee;


// SOLUTION

	S s(e.nbJob + 1);


// GEN INITIAL SOLUTION

	auto init = global::init[global::options["--init"][0]];
	(*init)(s);
	val_t val = e(s);
	val_t opt = val;
	S argopt(s);

	// PRINT IT
	if(global::verbose){
		std::cout << "init: ";
		lib::io::format(std::cout, s, global::list_p) << std::endl;
		std::cout << val << std::endl;
	}


// ALIAS

	auto neighborhood = global::neighborhood[global::options["--neighborhood"][0]];
	auto pivoting = global::pivoting;


// FIND LOCAL OPTIMUM

	hrclock::time_point beg = hrclock::now();

	// RII ALGORITHM
	while(
		(!global::max_steps || global::steps < global::max_steps) &&
		(!global::max_time.count() || global::time < global::max_time)
	){
		M m;

		if(global::r(global::g) < global::wp){
			m = (*neighborhood->random)(global::g, s);
		}
		else{
			m = pivoting(s, neighborhood->walk, neighborhood->eval).second;
		}

		val += (*neighborhood->eval)(s, m, e.detail, e.wt);
		(*neighborhood->apply)(s, m);

		++global::steps;
		global::duration = hrclock::now() - beg;
		global::time = std::chrono::duration_cast<std::chrono::seconds>(global::duration);

		if(val < opt){
			opt = val;
			argopt = s;
			std::cout << "best "  << opt ;
			std::cout << " step " << global::steps;
			std::cout << " time " << std::chrono::duration_cast<std::chrono::milliseconds>(global::duration).count();
			std::cout << std::endl;
		}
	}
	// <end>

	hrclock::time_point end = hrclock::now();


// OUTPUT

	// BEST

	if(global::verbose){
		std::cout << "best: ";
		lib::io::format(std::cout, argopt, global::list_p) << std::endl;
	}

	std::cout << opt << std::endl;

	// TIME

	if(global::verbose) std::cout << "time : ";
	global::duration = end - beg;
	std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(global::duration);
	std::cout << elapsed.count();
	if(global::verbose) std::cout << " ms";
	std::cout << std::endl;

	// SEED

	if(global::verbose) std::cout << "seed : ";
	lib::io::format(std::cout, global::seed_v, global::list_p) << std::endl;
}


int main(int argc, char *argv[]){
	
	config::fill(argc, argv);

	if(global::help){
		config::help();
		return 0;
	}

	try{
		config::check();
		run();
	}
	catch(const std::exception& e){
		std::cout << "error -> " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
