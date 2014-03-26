#ifndef _PFSP_EVAL_INIT_HPP
#define _PFSP_EVAL_INIT_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

namespace pfsp{
namespace eval{

template<typename addr_t, typename val_t, typename priority_t, typename A1, typename A2, typename A3>
class init{
public:
	typedef val_t val;

	const addr_t& nbJob;
	const addr_t& nbMac;

	const A1& dueDates;
	const A2& priority;
	const A3& processingTimesMatrix;

	std::vector<val_t> previousMachineEndTime;
	std::vector<val_t> wt;

	init(const addr_t& nbJob, const addr_t& nbMac, const A1& dueDates,
		const A2& priority, const A3& processingTimesMatrix)
	:nbJob(nbJob), nbMac(nbMac), dueDates(dueDates),
	priority(priority), processingTimesMatrix(processingTimesMatrix),
	previousMachineEndTime(nbJob + 1), wt(nbJob + 1, 0){}

	template<typename S>
	val_t operator()(S& sol){

		previousMachineEndTime[0] = 0;
		for(addr_t j = 1; j <= nbJob; ++j){
			addr_t jobNumber = sol[j];
			previousMachineEndTime[j] = previousMachineEndTime[j-1] + processingTimesMatrix[jobNumber][1];
		}

		for(addr_t m = 2; m <= nbMac; ++m){
			previousMachineEndTime[1] += processingTimesMatrix[sol[1]][m];
			val_t previousJobEndTime = previousMachineEndTime[1];


			for(addr_t j = 2; j <= nbJob; ++j){
				addr_t jobNumber = sol[j];

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

		val_t twt = 0;
		for(addr_t j = 1; j <= nbJob; ++j){
			wt[j] = (std::max(previousMachineEndTime[j] - dueDates[sol[j]], 0L) * priority[sol[j]]); 
			twt += wt[j];
		}

		return twt;
	}
};

}
}



#endif // _PFSP_EVAL_INIT_HPP
