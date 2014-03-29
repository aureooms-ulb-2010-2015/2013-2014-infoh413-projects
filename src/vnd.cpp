#include <iostream>
#include <fstream>

#include "lib/io.hpp"
#include "lib/error/exception.hpp"

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
	E e(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::i.processingTimesMatrix);
	TE te(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::i.processingTimesMatrix, e.wt, e.detail);
	IE ie(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::i.processingTimesMatrix, e.wt, e.detail);
	EE ee(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::i.processingTimesMatrix, e.wt, e.detail);
	global::transpose.eval = &te;
	global::insert.eval = &ie; 
	global::exchange.eval = &ee;

	/* 1 based index FTW !¸··}#{}¼CHANGE THIS FUCKSHIT */
	S s(e.nbJob + 1);

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
		val_t nlo = pivoting(s, ordering[k]->walk, ordering[k]->eval, ordering[k]->apply);
		while(nlo){
			// lib::io::format(std::cout, s, global::list_p);
			// std::cout << std::endl;
			//std::cout << nlo << " " <<
			e(s)
			// << std::endl
			; // TODO KICK IT
			k = 0;
			nlo = pivoting(s, ordering[k]->walk, ordering[k]->eval, ordering[k]->apply);
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
