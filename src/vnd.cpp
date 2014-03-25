#include <iostream>
#include <fstream>

#include "lib/io.hpp"
#include "lib/error/exception.hpp"

#include "pfsp/eval.hpp"
#include "pfsp/io/parse/body.hpp"
#include "pfsp/io/parse/header.hpp"
#include "pfsp/mem/allocate.hpp"

#include "ex2/global.hpp"
#include "ex2/config.hpp"

using namespace ex2;


void run(){

	// INPUT
	
	std::ifstream fileIn;
	fileIn.open(global::params[0]);

	if(!fileIn.is_open()) throw lib::error::exception("Could not open input file");

	pfsp::io::parse::header(fileIn, global::i.nbJob, global::i.nbMac);
	pfsp::mem::allocate(global::i.processingTimesMatrix, global::i.dueDates, global::i.priority, global::i.nbJob, global::i.nbMac);
	pfsp::io::parse::body(fileIn, global::i.nbJob, global::i.nbMac, global::i.processingTimesMatrix, global::i.dueDates, global::i.priority);

	fileIn.close();

	/* evaluator functor */
	eval e(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::i.processingTimesMatrix);

	/* 1 based index FTW !¸··}#{}¼CHANGE THIS FUCKSHIT */
	solution s(e.nbJob + 1);

	// GEN INITIAL SOLUTION

	auto init = global::init[global::options["--init"][0]];
	(*init)(s);

	std::cout << "init: ";
	lib::io::format(std::cout, s, global::list_p);
	std::cout << std::endl;
	std::cout << e(s) << std::endl;

	auto ordering = global::ordering[global::options["--ordering"][0]];
	auto pivoting = global::pivoting[global::options["--pivoting"][0]];

	// FIND LOCAL OPTIMUM

	size_t k = 0;

	while(k < ordering.size()){
		solution n = pivoting(s, ordering[k], e);
		while(e(n) < e(s)){
			k = 0;
			s = n;
			n = pivoting(s, ordering[k], e);
		}
		++k;
	}

	// OUTPUT

	std::cout << "best: ";
	lib::io::format(std::cout, s, global::list_p);
	std::cout << std::endl;
	std::cout << e(s) << std::endl;
	
	// SEED

	std::cout << "seed : ";
	lib::io::format(std::cout, global::seed_v, global::list_p);
	std::cout << std::endl;
}


int main(int argc, char *argv[]){
	
	config::fill(argc, argv);

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
