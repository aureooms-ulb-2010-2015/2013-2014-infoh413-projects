#ifndef _PFSP_EVAL_TRANSPOSE_HPP
#define _PFSP_EVAL_TRANSPOSE_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>

#include "pfsp/eval/functor.hpp"

namespace pfsp{
namespace eval{

template<
	typename addr_t,
	typename val_t,
	typename priority_t,
	typename S,
	typename M,
	typename A1,
	typename A2,
	typename A3,
	typename A4,
	typename A5,
	typename A6
>
class transpose : public functor<val_t, S, M, A6, A5>{
public:

	const addr_t& nbJob;
	const addr_t& nbMac;

	const A1& dueDates;
	const A2& priority;
	const A3& processing;

	A4 detail_src;
	A6 detail;
	A5 wt;
	const A5& wt_r;
	const A6& detail_r;


	transpose(
		const addr_t& nbJob,
		const addr_t& nbMac,
		const A1& dueDates,
		const A2& priority,
		const A3& processing,
		const A5& wt_r,
		const A6& detail_r
	):
	nbJob(nbJob),
	nbMac(nbMac),
	dueDates(dueDates),
	priority(priority),
	processing(processing),
	detail_src((nbJob + 1) * (nbMac + 1), 0),
	detail(&detail_src[0], nbJob + 1, nbMac + 1),
	wt(nbJob + 1, 0),
	wt_r(wt_r),
	detail_r(detail_r){}

	virtual val_t operator()(const S& sol, const M& mutation){
		return operator()(sol, mutation, detail, wt);
	}

	virtual val_t operator()(const S& sol, const M& mutation, A6& detail, A5& wt){
		addr_t beg, end;
		std::tie(beg, end) = mutation;

		// SWAP BEG, END
		addr_t _beg = sol[end], _end = sol[beg];

		detail[beg][1] = detail_r[beg-1][1] + processing[_beg][1];
		detail[end][1] = detail[end-1][1] + processing[_end][1];
		for(addr_t j = end + 1; j <= nbJob; ++j){
			detail[j][1] = detail[j-1][1] + processing[sol[j]][1];
		}

		for(addr_t m = 2; m <= nbMac; ++m){
			detail[beg][m] = std::max(detail[beg][m-1], detail_r[beg-1][m]) + processing[_beg][m];
			detail[end][m] = std::max(detail[end][m-1], detail[end-1][m]) + processing[_end][m];
		}
		for(addr_t j = end + 1; j <= nbJob; ++j){
			for(addr_t m = 2; m <= nbMac; ++m){
				detail[j][m] = std::max(detail[j][m-1], detail[j-1][m]) + processing[sol[j]][m];
			}
		}

		val_t wtd = 0;

		wt[beg] = (std::max(detail[beg][nbMac] - dueDates[_beg], val_t(0)) * priority[_beg]);
		wtd += wt[beg];

		wt[end] = (std::max(detail[end][nbMac] - dueDates[_end], val_t(0)) * priority[_end]);
		wtd += wt[end];

		for(addr_t j = end + 1; j <= nbJob; ++j){
			wt[j] = (std::max(detail[j][nbMac] - dueDates[sol[j]], val_t(0)) * priority[sol[j]]);
			wtd += wt[j];
		}

		for(addr_t j = beg; j <= nbJob; ++j) wtd -= wt_r[j];

		return wtd;
	}
};

}
}



#endif // _PFSP_EVAL_TRANSPOSE_HPP
