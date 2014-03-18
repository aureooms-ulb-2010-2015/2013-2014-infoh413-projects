#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

#include "pfsp/instance.hpp"

namespace pfsp{

Instance::Instance(){}
Instance::~Instance(){}


int Instance::getNbJob(){return nbJob;}
int Instance::getNbMac(){return nbMac;}

long int Instance::getTime(const int job, const int machine){
	if(job == 0) return 0;
	else{
		if((job < 1) || (job > nbJob) || (machine < 1) || (machine > nbMac))
			std::cout << "ERROR. file:Instance.cpp, method:getTime. Out of bound. job=" << job
			<< ", machine=" << machine << std::endl;

		return processingTimesMatrix[job][machine];
	}
}

/* Compute the weighted tardiness of a given solution */
long int Instance::computeWT(std::vector<int>& sol){
	int j, m;
	int jobNumber;
	long int wt;

	/* We need end times on previous machine : */
	std::vector<long int> previousMachineEndTime(nbJob + 1);
	/* And the end time of the previous job, on the same machine : */
	long int previousJobEndTime;

	/* 1st machine : */
	previousMachineEndTime[0] = 0;
	for(j = 1; j <= nbJob; ++j){
		jobNumber = sol[j];
		previousMachineEndTime[j] = previousMachineEndTime[j-1] + processingTimesMatrix[jobNumber][1];
	}

	/* others machines : */
	for(m = 2; m <= nbMac; ++m){
		previousMachineEndTime[1] += processingTimesMatrix[sol[1]][m];
		previousJobEndTime = previousMachineEndTime[1];


		for(j = 2; j <= nbJob; ++j){
			jobNumber = sol[j];

			if(previousMachineEndTime[j] > previousJobEndTime){
				previousMachineEndTime[j] = previousMachineEndTime[j] + processingTimesMatrix[jobNumber][m];
				previousJobEndTime = previousMachineEndTime[j];
			}
			else{
				previousJobEndTime += processingTimesMatrix[jobNumber][m];
				previousMachineEndTime[j] = previousJobEndTime;
			}
		}
	}

	wt = 0;
	for(j = 1; j<= nbJob; ++j)
		wt += (std::max(previousMachineEndTime[j] - dueDates[sol[j]], 0L) * priority[sol[j]]);

	return wt;
}


}
