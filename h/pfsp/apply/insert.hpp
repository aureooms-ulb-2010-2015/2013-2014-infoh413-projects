#ifndef _PFSP_APPLY_INSERT_HPP
#define _PFSP_APPLY_INSERT_HPP

#include <tuple>
#include <algorithm>


namespace pfsp{
namespace apply{


/**
 * Function template for insert neighborhood perturbation application.
 *
 * @param <S> solution type
 * @param <M> perturbation type
 *
 * @param sol The solution the perturbation will be applied to
 * @param mutation The perturbation to apply
 *
 * @author Ooms Aurélien
 *
 */

template<typename S, typename M>
void insert(S& sol, const M& mutation){
	
	size_t i = std::get<0>(mutation), j = std::get<1>(mutation);
	size_t s = j > i;
	size_t a[] = {i, j};

	typename S::value_type tmp = sol[i];

	std::copy(
		sol.begin() + a[1-s] + s,
		sol.begin() + a[s] + s,
		sol.begin() + a[1-s] + 1 - s
	);

	sol[j] = tmp;
	
}

} // apply
} // pfsp

#endif // _PFSP_APPLY_INSERT_HPP