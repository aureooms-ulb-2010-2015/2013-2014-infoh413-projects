#ifndef _PFSP_INSTANCE_HPP
#define _PFSP_INSTANCE_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

namespace pfsp{

template<typename addr_t, typename val_t, typename priority_t>
class Instance{
public:
	addr_t nbJob;
	addr_t nbMac;
	std::vector<val_t> dueDates;
	std::vector<priority_t> priority;

	std::vector<std::vector<val_t>> processingTimesMatrix;



	/* Read\Write values in the matrix : */
	void setTime(addr_t job, addr_t machine, val_t processTime);

	val_t getDueDate(addr_t job);
	void setDueDate(addr_t job, val_t value);

	val_t getPriority(addr_t job);
	void setPriority(addr_t job, priority_t value);


	Instance(){}
	~Instance(){}


	addr_t getNbJob(){return nbJob;}
	addr_t getNbMac(){return nbMac;}

	val_t getTime(const addr_t job, const addr_t machine){
		if(job == 0) return 0;
		else{
			if((job < 1) || (job > nbJob) || (machine < 1) || (machine > nbMac))
				std::cout << "ERROR. file:Instance.cpp, method:getTime. Out of bound. job=" << job
				<< ", machine=" << machine << std::endl;

			return processingTimesMatrix[job][machine];
		}
	}

	/* Compute the weighted tardiness of a given solution */
	val_t computeWT(std::vector<addr_t>& sol){
		addr_t j, m;
		addr_t jobNumber;
		val_t wt;

		/* We need end times on previous machine : */
		std::vector<val_t> previousMachineEndTime(nbJob + 1);
		/* And the end time of the previous job, on the same machine : */
		val_t previousJobEndTime;

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
		for(j = 1; j <= nbJob; ++j)
			wt += (std::max(previousMachineEndTime[j] - dueDates[sol[j]], 0L) * priority[sol[j]]);

		return wt;
	}
};

}

#endif
