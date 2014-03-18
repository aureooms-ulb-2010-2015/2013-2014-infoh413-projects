#include <iostream>
#include <fstream>

#include "pfsp/instance.hpp"
#include "pfsp/io/parse/body.hpp"
#include "pfsp/io/parse/header.hpp"
#include "pfsp/mem/allocate.hpp"

#include "lib/io.hpp"

#include "impl1/typedef.hpp"

using namespace pfsp;


int main(int argc, char *argv[]){
	std::vector<long long> seed_v;

	if(seed_v.size() == 0){
		seed_v.push_back(sysclock::now().time_since_epoch().count());
	}

	std::seed_seq seed(seed_v.begin(), seed_v.end());

	random_engine g(seed);


	if (argc == 1){
		std::cout << "Usage: ./flowshopTWT <instance_file>" << std::endl;
		return 0;
	}

	/* Create instance object */
	pfsp::Instance<addr_t, val_t, priority_t> instance;

	/* Read data from file */
	std::ifstream fileIn;
	fileIn.open(argv[1]);

	if(!fileIn.is_open()) return 1;

	io::parse::header(fileIn, instance.nbJob, instance.nbMac);
	mem::allocate(instance.processingTimesMatrix, instance.dueDates, instance.priority, instance.nbJob, instance.nbMac);
	io::parse::body(fileIn, instance.nbJob, instance.nbMac, instance.processingTimesMatrix, instance.dueDates, instance.priority);

	fileIn.close();

	/* 1 based index FTW !¸··}#{}¼CHANGE THIS FUCKSHIT */
	solution s(instance.getNbJob() + 1);
	std::iota(s.begin(), s.end(), 0);

	/* shuffle the vector */
	sample(g, instance.getNbJob(), s, 1, instance.getNbJob() + 1);

	std::cout << "Random solution: " << s << std::endl;

	/* Compute the TWT of this solution */
	val_t totalWeightedTardiness = instance.computeWT(s);
	std::cout << "Total weighted tardiness: " << totalWeightedTardiness << std::endl;
	std::cout << "seed : " << seed_v << std::endl;

	return 0;
}
