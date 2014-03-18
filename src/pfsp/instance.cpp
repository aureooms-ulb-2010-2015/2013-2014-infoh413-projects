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

/* Allocates the memory for the processing times matrix : */
void Instance::allowMatrixMemory(const int nbJ, const int nbM){
	processingTimesMatrix.resize(nbJ+1);

	for (int cpt = 0; cpt < nbJ+1; ++cpt) processingTimesMatrix[cpt].resize(nbM+1);

	dueDates.resize(nbJ+1);
	priority.resize(nbJ+1);
}


long int Instance::getTime(const int job, const int machine){
	if(job == 0) return 0;
	else{
		if((job < 1) || (job > nbJob) || (machine < 1) || (machine > nbMac))
			std::cout << "ERROR. file:Instance.cpp, method:getTime. Out of bound. job=" << job
			<< ", machine=" << machine << std::endl;

		return processingTimesMatrix[job][machine];
	}
}


/* Read the instance from file : */
bool Instance::readDataFromFile(char * fileName){

	bool everythingOK = true;
	int j, m; // iterators
	long int readValue;
	std::string str;
	std::ifstream fileIn;
	char* aux2;
	char fileNameOK[100] = "";

	aux2 = (strrchr(fileName, '/'));

	if(aux2 == NULL) aux2 = fileName;
	else             aux2 += 1;

	strcat(fileNameOK, aux2);

	std::cout << "name : " << fileNameOK << std::endl;
	std::cout << "file : " << fileName << std::endl;

	fileIn.open(fileName);

	if(fileIn.is_open()){
		std::cout << "File " << fileName << " is now open, start to read..." << std::endl;

		fileIn >> nbJob;
		std::cout << "Number of jobs : " << nbJob << std::endl;
		fileIn >> nbMac;
		std::cout << "Number of machines : " << nbMac << std::endl;
		std::cout << "Allow memory for the matrix..." << std::endl;
		this->allowMatrixMemory(nbJob, nbMac);
		std::cout << "Memory allowed." << std::endl;
		std::cout << "Start to read matrix..." << std::endl;

		for(j = 1; j <= nbJob; ++j){
			for(m = 1; m <= nbMac; ++m){
				fileIn >> readValue; // The number of each machine, not important !
				fileIn >> readValue; // Process Time

				processingTimesMatrix[j][m] = readValue;
			}
		}

		fileIn >> str; // this is not read

		for (j = 1; j <= nbJob; ++j){
			fileIn >> readValue; // -1
			fileIn >> readValue;
			dueDates[j] = readValue;
			fileIn >> readValue; // -1
			fileIn >> readValue;
			priority[j] = readValue;
		}

		std::cout << "All is read from file." << std::endl;
		fileIn.close();
	}
	else{
		std::cout << "ERROR. file:Instance.cpp, method:readDataFromFile, "
		<< "error while opening file " << fileName << std::endl;

		everythingOK = false;
	}

	return everythingOK;
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
