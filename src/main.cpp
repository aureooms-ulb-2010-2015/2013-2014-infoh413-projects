#include <iostream>
#include <fstream>

#include "lib/io.hpp"
#include "lib/error/exception.hpp"

#include "pfsp/eval.hpp"
#include "pfsp/io/parse/body.hpp"
#include "pfsp/io/parse/header.hpp"
#include "pfsp/mem/allocate.hpp"

#include "ex1/global.hpp"
#include "ex1/config.hpp"

using namespace ex1;


void run(){
	/* evaluator functor */
	eval e;

	/* Read data from file */
	std::ifstream fileIn;
	fileIn.open(ex1::global::params[0]);

	if(!fileIn.is_open()) throw lib::error::exception("Could not open input file");

	pfsp::io::parse::header(fileIn, e.nbJob, e.nbMac);
	pfsp::mem::allocate(e.processingTimesMatrix, e.dueDates, e.priority, e.nbJob, e.nbMac);
	pfsp::io::parse::body(fileIn, e.nbJob, e.nbMac, e.processingTimesMatrix, e.dueDates, e.priority);

	fileIn.close();

	/* 1 based index FTW !¸··}#{}¼CHANGE THIS FUCKSHIT */
	solution s(e.nbJob + 1);
	std::iota(s.begin(), s.end(), 0);

	/* shuffle the vector */
	sample(global::g, e.nbJob, s, 1, e.nbJob + 1);

	std::cout << "Random solution: ";
	lib::io::format(std::cout, s, global::list_p);
	std::cout << std::endl;

	/* Compute the TWT of this solution */
	val_t totalWeightedTardiness = e(s);
	std::cout << "Total weighted tardiness: " << totalWeightedTardiness << std::endl;
	/* Compute the TWT of this solution */
	totalWeightedTardiness = e(s);
	std::cout << "Total weighted tardiness: " << totalWeightedTardiness << std::endl;

	auto neighborhood = global::neighborhood[ex1::global::options["--neighborhood"][0]];
	auto pivoting = pfsp::pivoting::best<solution, walk, eval>;
	solution n = pivoting(s, neighborhood, e);

	std::cout << "Total weighted tardiness n: " << e(n) << std::endl;
	
	std::cout << "seed : ";
	lib::io::format(std::cout, global::seed_v, global::list_p);
	std::cout << std::endl;
}


int main(int argc, char *argv[]){
	
	ex1::config::fill(argc, argv);

	try{
		ex1::config::check();
		run();
	}
	catch(const std::exception& e){
		std::cout << "error -> " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
