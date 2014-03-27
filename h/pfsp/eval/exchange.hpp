#ifndef _PFSP_EVAL_EXCHANGE_HPP
#define _PFSP_EVAL_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>

namespace pfsp{
namespace eval{

template<typename addr_t, typename val_t, typename priority_t, typename A1, typename A2, typename A3, typename A4, typename A5>
class exchange{
public:
	typedef val_t val;

	const addr_t& nbJob;
	const addr_t& nbMac;

	const A1& dueDates;
	const A2& priority;
	const A3& processingTimesMatrix;

	A4 previousMachineEndTime;
	A5 wt;
	A5& ref;

	exchange(const addr_t& nbJob, const addr_t& nbMac, const A1& dueDates,
		const A2& priority, const A3& processingTimesMatrix, const A5& ref)
	:nbJob(nbJob), nbMac(nbMac), dueDates(dueDates),
	priority(priority), processingTimesMatrix(processingTimesMatrix),
	previousMachineEndTime(nbJob + 1), wt(nbJob + 1, 0), ref(ref){}

	template<typename S, typename M>
	val_t operator()(const S& sol, const M& mutation){
		addr_t beg, end;
		std::tie(beg, end) = mutation;

		// SWAP BEG, END
		addr_t _beg = sol[end], _end = sol[beg];

		previousMachineEndTime[beg-1] = 0;

		previousMachineEndTime[beg] = previousMachineEndTime[beg-1] + processingTimesMatrix[_beg][1];
		for(addr_t j = beg + 1; j < end; ++j){
			previousMachineEndTime[j] = previousMachineEndTime[j-1] + processingTimesMatrix[sol[j]][1];
		}
		previousMachineEndTime[end] = previousMachineEndTime[end-1] + processingTimesMatrix[_end][1];

		for(addr_t m = 2; m <= nbMac; ++m){

			previousMachineEndTime[beg] += processingTimesMatrix[_beg][m];
			val_t previousJobEndTime = previousMachineEndTime[beg];

			for(addr_t j = beg + 1; j < end; ++j){
				if(previousMachineEndTime[j] > previousJobEndTime){
					previousMachineEndTime[j] = previousMachineEndTime[j] + processingTimesMatrix[sol[j]][m];
					previousJobEndTime = previousMachineEndTime[j];
				}
				else{
					previousJobEndTime += processingTimesMatrix[sol[j]][m];
					previousMachineEndTime[j] = previousJobEndTime;
				}
			}

			if(previousMachineEndTime[end] > previousJobEndTime){
				previousMachineEndTime[end] = previousMachineEndTime[end] + processingTimesMatrix[_end][m];
			}
			else{
				previousMachineEndTime[end] = previousJobEndTime + processingTimesMatrix[_end][m];
			}
		}

		val_t wtd = 0;
		wt[beg] = (std::max(previousMachineEndTime[beg] - dueDates[_beg], 0L) * priority[_beg]);
		for(addr_t j = beg + 1; j < end; ++j){
			wt[j] = (std::max(previousMachineEndTime[j] - dueDates[sol[j]], 0L) * priority[sol[j]]); 
			wtd += wt[j] - ref[j];
		}
		wt[end] = (std::max(previousMachineEndTime[end] - dueDates[_end], 0L) * priority[_end]);
		return wtd + wt[beg] - ref[beg] + wt[end] - ref[end];
	}
};

}
}



#endif // _PFSP_EVAL_EXCHANGE_HPP
