#ifndef _PFSP_EVAL_INSERT_HPP
#define _PFSP_EVAL_INSERT_HPP

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
	typename A5
>
class insert : public functor<val_t, S, M>{
public:

	const addr_t& nbJob;
	const addr_t& nbMac;

	const A1& dueDates;
	const A2& priority;
	const A3& processing;

	A4 detail;
	A5 wt;
	const A5& wt_r;
	const A4& detail_r;

	insert(const addr_t& nbJob, const addr_t& nbMac, const A1& dueDates,
		const A2& priority, const A3& processing, const A5& wt_r, const A4& detail_r)
	:nbJob(nbJob), nbMac(nbMac), dueDates(dueDates),
	priority(priority), processing(processing),
	detail(nbJob + 1), wt(nbJob + 1, 0), wt_r(wt_r), detail_r(detail_r){
		for(addr_t i = 0; i <= nbJob; ++i) detail[i].resize(nbMac + 1, 0);
	}

	virtual val_t operator()(const S& sol, const M& mutation){
		addr_t beg, end, x, l, r, _beg, _end;
		std::tie(beg, end) = mutation;

		if(beg < end){
			x = 1;
			l = beg;
			r = end;
			_beg = sol[l+x];
			_end = sol[beg];
		}
		else{
			x = -1;
			l = end;
			r = beg;
			_beg = sol[beg];
			_end = sol[r+x];
		}

		detail[l][1] = detail_r[l-1][1] + processing[_beg][1];
		for(addr_t j = l + 1; j < r; ++j) detail[j][1] = detail[j-1][1] + processing[sol[j+x]][1];
		for(addr_t m = 2; m <= nbMac; ++m){
			detail[l][m] = std::max(detail[l][m-1], detail_r[l-1][m]) + processing[_beg][m];
			for(addr_t j = l + 1; j < r; ++j){
				detail[j][m] = std::max(detail[j][m-1], detail[j-1][m]) + processing[sol[j+x]][m];
			}
		}

		detail[r][1] = detail[r-1][1] + processing[_end][1];
		for(addr_t j = r + 1; j <= nbJob; ++j) detail[j][1] = detail[j-1][1] + processing[sol[j]][1];
		for(addr_t m = 2; m <= nbMac; ++m){
			detail[r][m] = std::max(detail[r][m-1], detail[r-1][m]) + processing[_end][m];
			for(addr_t j = r + 1; j <= nbJob; ++j){
				detail[j][m] = std::max(detail[j][m-1], detail[j-1][m]) + processing[sol[j]][m];
			}
		}


		val_t wtd = 0;
		wt[l] = (std::max(detail[l][nbMac] - dueDates[_beg], 0L) * priority[_beg]);
		for(addr_t j = l + 1; j < r; ++j){
			wt[j] = (std::max(detail[j][nbMac] - dueDates[sol[j+x]], 0L) * priority[sol[j+x]]); 
			wtd += wt[j] - wt_r[j];
		}
		wt[r] = (std::max(detail[r][nbMac] - dueDates[_end], 0L) * priority[_end]);
		for(addr_t j = r + 1; j <= nbJob; ++j){
			wt[j] = (std::max(detail[j][nbMac] - dueDates[sol[j]], 0L) * priority[sol[j]]); 
			wtd += wt[j] - wt_r[j];
		}


		return wtd + wt[l] - wt_r[l] + wt[r] - wt_r[r];
	}
};

}
}



#endif // _PFSP_EVAL_INSERT_HPP
