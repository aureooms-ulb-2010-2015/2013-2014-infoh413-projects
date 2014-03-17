#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "pfspinstance.h"

#include "io/parse/body.h"
#include "io/parse/header.h"

#include "mem/allocate.h"

using namespace infoh413;

int generateRndPosition(int min, int max){
	return (rand() % max + min);
}


/* Fill the solution with numbers between 1 and nbJobs, shuffled */
void randomPermutation(int nbJobs, std::vector<int>& sol){

	std::vector<bool> alreadyTaken(nbJobs+1, false); // nbJobs elements with value false
	std::vector<int> choosenNumber(nbJobs+1, 0);

	int nbj;
	int rnd, i, j, nbFalse;

	nbj = 0;
	for(i = nbJobs; i >= 1; --i){
		rnd = generateRndPosition(1, i);
		nbFalse = 0;

		/* find the rndth cell with value = false : */
		for(j = 1; nbFalse < rnd; ++j) if(!alreadyTaken[j]) ++nbFalse;

		--j;

		sol[j] = i;

		++nbj;
		choosenNumber[nbj] = j;

		alreadyTaken[j] = true;
	}
}

/***********************************************************************/

int main(int argc, char *argv[]){
	int i;
	long int totalWeightedTardiness;


	if (argc == 1){
		std::cout << "Usage: ./flowshopTWT <instance_file>" << std::endl;
		return 0;
	}

	/* initialize random seed: */
	srand(time(NULL)); // HELL WTF USE STD C++11

	/* Create instance object */
	PfspInstance instance;

	/* Read data from file */
	std::ifstream fileIn;
	fileIn.open(argv[1]);

	if(!fileIn.is_open()) return 1;

	io::parse::header(fileIn, instance.nbJob, instance.nbMac);
	mem::allocate(instance.processingTimesMatrix, instance.dueDates, instance.priority, instance.nbJob, instance.nbMac);
	io::parse::body(fileIn, instance.nbJob, instance.nbMac, instance.processingTimesMatrix, instance.dueDates, instance.priority);

	fileIn.close();

	/* Create a vector of int to represent the solution
		WARNING: By convention, we store the jobs starting from index 1,
		thus the size nbJob + 1. */
	std::vector<int> solution(instance.getNbJob()+1);

	/* Fill the vector with a random permutation */
	randomPermutation(instance.getNbJob(), solution);

	std::cout << "Random solution: ";
	for (i = 1; i <= instance.getNbJob(); ++i) std::cout << solution[i] << " ";
	std::cout << std::endl;

	/* Compute the TWT of this solution */
	totalWeightedTardiness = instance.computeWT(solution);
	std::cout << "Total weighted tardiness: " << totalWeightedTardiness << std::endl;

	return 0;
}
