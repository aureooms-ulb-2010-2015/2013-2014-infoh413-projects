#ifndef _PFSP_EVAL_HPP
#define _PFSP_EVAL_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

namespace pfsp{

template<typename addr_t, typename val_t, typename priority_t, typename A1, typename A2, typename A3>
class eval{
public:
	typedef val_t val;

	addr_t& nbJob;
	addr_t& nbMac;

	A1& dueDates;
	A2& priority;
	A3& processingTimesMatrix;

	/* We need end times on previous machine : */
	std::vector<val_t> previousMachineEndTime;

	eval(addr_t& nbJob, addr_t& nbMac, A1& dueDates, A2& priority, A3& processingTimesMatrix)
	:nbJob(nbJob), nbMac(nbMac), dueDates(dueDates),
	priority(priority), processingTimesMatrix(processingTimesMatrix),
	previousMachineEndTime(nbJob + 1){}

	/* Compute the weighted tardiness of a given solution */
	template<typename S>
	val_t operator()(S& sol){
		addr_t j, m;
		addr_t jobNumber;
		val_t wt;

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
