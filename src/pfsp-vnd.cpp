#include <iostream>
#include <fstream>

#include "lib/io.hpp"
#include "lib/error/exception.hpp"

#include "pfsp/io/parse/body.hpp"
#include "pfsp/io/parse/header.hpp"
#include "pfsp/mem/allocate.hpp"

#include "pfsp_vnd/global.hpp"
#include "pfsp_vnd/config.hpp"

#include "pfsp_commons/framework.hpp"

using namespace pfsp_vnd;


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
	val_t opt = (*global::e)(s);

	// PRINT IT
	if(global::verbose){
		std::cout << "init ";
		lib::io::format(std::cout, s, global::list_p) << std::endl;
		std::cout << opt << std::endl;
	}


// ALIAS

	auto ordering = global::ordering[global::options["--ordering"][0]];
	auto pivoting = global::pivoting[global::options["--pivoting"][0]];

// FIND LOCAL OPTIMUM

	hrclock::time_point beg = hrclock::now();


	// VND ALGORITHM
	size_t k = 0;

	while(k < ordering.size()){
		R best = pivoting(s, ordering[k]->walk, ordering[k]->eval);
		while(best.first){
			opt += best.first;
			(*ordering[k]->eval)(s, best.second, global::e->detail, global::e->wt);
			(*ordering[k]->apply)(s, best.second);

			if(global::verbose){
				++global::steps;
				pfsp::framework::print_step(std::cout, global::steps, hrclock::now() - beg, opt);
			}

			k = 0;
			best = pivoting(s, ordering[k]->walk, ordering[k]->eval);
		}
		++k;
	}
	// <end>
	
	hrclock::time_point end  = hrclock::now();


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
