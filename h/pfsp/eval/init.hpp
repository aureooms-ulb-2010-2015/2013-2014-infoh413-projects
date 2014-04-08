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


/**
 * Class template for initial evaluation functors.
 *
 * @author Ooms Aurélien
 * 
 * @param <addr_t> job/machine indices type
 * @param <val_t> weighted tardiness type
 * @param <priority_t> priority type
 * @param <A1> dueDates array type
 * @param <A2> priority array type
 * @param <A3> processing array type
 * @param <A4> detail array type
 * @param <A5> wt array type
 * @param <A6> detail array proxy type
 *
 */

template<
	typename addr_t, 
	typename val_t, 
	typename priority_t, 
	typename A1, 
	typename A2, 
	typename A3, 
	typename A4, 
	typename A5,
	typename A6
>
class init{
public:

	const addr_t& nbJob;
	const addr_t& nbMac;

	const A1& dueDates;
	const A2& priority;
	const A3& processing;

	A4 detail_src;
	A6 detail;
	A5 wt;

	init(
		const addr_t& nbJob,
		const addr_t& nbMac,
		const A1& dueDates,
		const A2& priority,
		const A3& processing
	):
	nbJob(nbJob),
	nbMac(nbMac),
	dueDates(dueDates),
	priority(priority),
	processing(processing),
	detail_src((nbJob + 1) * (nbMac + 1), 0),
	detail(&detail_src[0], nbJob + 1, nbMac + 1),
	wt(nbJob + 1, 0){}


	/**
	 * operator() for initial evaluation.
	 * <p>
	 * Evaluates a solution.
	 *
	 * @param sol The solution to evaluate
	 * 
	 * @return the evaluation value (total weighted tardiness)
	 *
	 */
	
	template<typename S>
	val_t operator()(S& sol){

		for(addr_t j = 1; j <= nbJob; ++j){
			detail[j][1] = detail[j-1][1] + processing[sol[j]][1];
		}

		for(addr_t m = 2; m <= nbMac; ++m){
			detail[1][m] = detail[1][m-1] + processing[sol[1]][m];

			for(addr_t j = 2; j <= nbJob; ++j){
				detail[j][m] = std::max(detail[j][m-1], detail[j-1][m]) + processing[sol[j]][m];
			}
		}

		val_t twt = 0;
		for(addr_t j = 1; j <= nbJob; ++j){
			wt[j] = (std::max(detail[j][nbMac] - dueDates[sol[j]], val_t(0)) * priority[sol[j]]); 
			twt += wt[j];
		}

		return twt;
	}
};

} // eval
} // pfsp



#endif // _PFSP_EVAL_INIT_HPP
