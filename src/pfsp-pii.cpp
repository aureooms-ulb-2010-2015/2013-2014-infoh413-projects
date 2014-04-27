#include <iostream>
#include <fstream>

#include "lib/io.hpp"
#include "lib/error/exception.hpp"

#include "pfsp/io/parse/body.hpp"
#include "pfsp/io/parse/header.hpp"
#include "pfsp/mem/allocate.hpp"

#include "pfsp_pii/global.hpp"
#include "pfsp_pii/config.hpp"

#include "pfsp_commons/framework.hpp"

using namespace pfsp_pii;


void run(){

// PARSE INPUT

	pfsp::framework::parse(global::params[0], global::i);

	if(global::verbose){
		std::cout << "jobs " << global::i.nbJob << std::endl;
		std::cout << "mach " << global::i.nbMac << std::endl;
	}


// INIT EVAL

	pfsp::framework::init_eval<I,E,TE,IE,EE>(global::i, global::e, global::transpose.eval, global::insert.eval, global::exchange.eval);


// SOLUTION

	S s(global::i.nbJob + 1);


// GEN INITIAL SOLUTION

	auto init = global::init[global::options["--init"][0]];
	(*init)(s);
	val_t val = (*global::e)(s);
	val_t opt = val;
	S argopt(s);

	// PRINT IT
	if(global::verbose){
		std::cout << "init ";
		lib::io::format(std::cout, s, global::list_p) << std::endl;
		std::cout << "best " << val << std::endl;
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
		R neighbour = pivoting(global::g, global::r, global::T, s, neighborhood->walk, neighborhood->eval);

		val += neighbour.first;
		(*neighborhood->eval)(s, neighbour.second, global::e->detail, global::e->wt);
		(*neighborhood->apply)(s, neighbour.second);

		++global::steps;
		global::duration = hrclock::now() - beg;
		global::time = std::chrono::duration_cast<delta_t>(global::duration);

		if(val < opt){
			opt = val;
			argopt = s;
			if(global::verbose){
				pfsp::framework::print_step(std::cout, global::steps, global::duration, opt);
			}
		}
	}
	// <end>

	hrclock::time_point end = hrclock::now();


// CLEAN

	pfsp::framework::clean_eval(global::e, global::transpose.eval, global::insert.eval, global::exchange.eval);


// OUTPUT

	pfsp::framework::output(std::cout, global::verbose, s, global::list_p, opt, end - beg, global::seed_v);
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
		std::cout << "error " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
