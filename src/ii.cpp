#include <iostream>
#include <fstream>

#include "lib/io.hpp"
#include "lib/error/exception.hpp"

#include "pfsp/io/parse/body.hpp"
#include "pfsp/io/parse/header.hpp"
#include "pfsp/mem/allocate.hpp"

#include "ex1/global.hpp"
#include "ex1/config.hpp"

using namespace ex1;


void run(){

	// INPUT
	
	std::ifstream fileIn;
	fileIn.open(global::params[0]);

	if(!fileIn.is_open()) throw lib::error::exception("Could not open input file");

	pfsp::io::parse::header(fileIn, global::i.nbJob, global::i.nbMac);
	pfsp::mem::allocate(global::i.processingTimesMatrix, global::i.dueDates, global::i.priority, global::i.nbJob, global::i.nbMac);
	pfsp::io::parse::body(fileIn, global::i.nbJob, global::i.nbMac, global::i.processingTimesMatrix, global::i.dueDates, global::i.priority);

	fileIn.close();

	// evaluator functors
	E e(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::i.processingTimesMatrix);
	TE te(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::i.processingTimesMatrix, e.wt, e.detail);
	IE ie(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::i.processingTimesMatrix, e.wt, e.detail);
	EE ee(global::i.nbJob, global::i.nbMac, global::i.dueDates, global::i.priority, global::i.processingTimesMatrix, e.wt, e.detail);
	global::transpose.eval =  &te;
	global::insert.eval = &ie; 
	global::exchange.eval = &ee;


	// based index FTW !¸··}#{}¼CHANGE THIS FUCKSHIT
	S s(e.nbJob + 1);

	// GEN INITIAL SOLUTION

	auto init = global::init[global::options["--init"][0]];
	(*init)(s);

	std::cout << "init: ";
	lib::io::format(std::cout, s, global::list_p);
	std::cout << std::endl;
	val_t opt = e(s);
	std::cout << opt << std::endl;

	auto neighborhood = global::neighborhood[global::options["--neighborhood"][0]];
	auto pivoting = global::pivoting[global::options["--pivoting"][0]];

	// FIND LOCAL OPTIMUM

	R best = pivoting(s, neighborhood->walk, neighborhood->eval);
	while(best.first){
		opt += best.first;
		(*neighborhood->eval)(s, best.second, e.detail, e.wt);
		(*neighborhood->apply)(s, best.second);
		best = pivoting(s, neighborhood->walk, neighborhood->eval);
	} 

	// OUTPUT

	std::cout << "best: ";
	lib::io::format(std::cout, s, global::list_p);
	std::cout << std::endl;
	std::cout << opt << std::endl;
	
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
