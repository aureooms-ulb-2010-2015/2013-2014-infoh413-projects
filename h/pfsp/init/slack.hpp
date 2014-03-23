#ifndef _PFSP_INIT_SLACK_HPP
#define _PFSP_INIT_SLACK_HPP

#include "lib/random/sample.hpp"
#include "pfsp/init/functor.hpp"

#include <algorithm>


namespace pfsp{
namespace init{

template<typename S, typename addr_t, typename val_t, typename priority_t, typename A1, typename A2, typename A3>
struct slack{

	struct fn : functor<S>{

		addr_t& nbJob;
		addr_t& nbMac;

		A1& dueDates;
		A2& priority;
		A3& processingTimesMatrix;

		fn(addr_t& nbJob, addr_t& nbMac, A1& dueDates, A2& priority, A3& processingTimesMatrix)
		:nbJob(nbJob), nbMac(nbMac), dueDates(dueDates), priority(priority), processingTimesMatrix(processingTimesMatrix){};

		virtual void operator()(S& sol){
			std::vector<val_t> prev(nbMac + 1, 0);

			// JOBS TO ADD
			std::list<addr_t> jobsLeft;
			for(addr_t i = 1; i <= nbJob; ++i) jobsLeft.push_back(i);

			for(addr_t i = 1; i <= nbJob; ++i){
				// first job
				auto it = jobsLeft.begin();
				val_t sum = 0;

				for(addr_t j = 1; j <= nbMac; ++j){
					sum = std::max(prev[j], sum) + processingTimesMatrix[*it][j];
				}

				val_t opt = priority[*it] * (dueDates[*it] - sum);
				auto argopt = it;


				// other jobs
				for(++it; it != jobsLeft.end(); ++it){
					sum = 0;
					for(addr_t j = 1; j <= nbMac; ++j){
						sum = std::max(prev[j], sum) + processingTimesMatrix[*it][j];
					}

					val_t tmp = priority[*it] * (dueDates[*it] - sum);

					if(tmp < opt){
						opt = tmp;
						argopt = it;
					}
				}

				for(addr_t j = 1; j <= nbMac; ++j){
					prev[j] = std::max(prev[j-1], prev[j]) + processingTimesMatrix[*argopt][j];
				}

				sol[i] = *argopt;
				jobsLeft.erase(argopt);
			}
		}
	};

	fn f;

	slack(addr_t& nbJob, addr_t& nbMac, A1& dueDates, A2& priority, A3& processingTimesMatrix)
	:f(nbJob, nbMac, dueDates, priority, processingTimesMatrix){}

};


}
}

#endif // _PFSP_INIT_SLACK_HPP