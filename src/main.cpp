#include <iostream>
#include <fstream>

#include "lib/io.hpp"
#include "lib/error/exception.hpp"

#include "pfsp/instance.hpp"
#include "pfsp/io/parse/body.hpp"
#include "pfsp/io/parse/header.hpp"
#include "pfsp/mem/allocate.hpp"

#include "ex1/global.hpp"
#include "ex1/config.hpp"

using namespace ex1;


void run(){
	/* Create instance object */
	pfsp::Instance<addr_t, val_t, priority_t> instance;

	/* Read data from file */
	std::ifstream fileIn;
	fileIn.open(ex1::global::params[0]);

	if(!fileIn.is_open()) throw lib::error::exception("Could not open input file");

	pfsp::io::parse::header(fileIn, instance.nbJob, instance.nbMac);
	pfsp::mem::allocate(instance.processingTimesMatrix, instance.dueDates, instance.priority, instance.nbJob, instance.nbMac);
	pfsp::io::parse::body(fileIn, instance.nbJob, instance.nbMac, instance.processingTimesMatrix, instance.dueDates, instance.priority);

	fileIn.close();

	/* 1 based index FTW !¸··}#{}¼CHANGE THIS FUCKSHIT */
	solution s(instance.getNbJob() + 1);
	std::iota(s.begin(), s.end(), 0);

	/* shuffle the vector */
	sample(global::g, instance.getNbJob(), s, 1, instance.getNbJob() + 1);

	std::cout << "Random solution: ";
	lib::io::format(std::cout, s, global::list_p);
	std::cout << std::endl;

	/* Compute the TWT of this solution */
	val_t totalWeightedTardiness = instance.computeWT(s);
	std::cout << "Total weighted tardiness: " << totalWeightedTardiness << std::endl;
	
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
