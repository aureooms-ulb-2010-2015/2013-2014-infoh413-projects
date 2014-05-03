#ifndef _PFSP_NEIGHBORHOOD_REXCHANGE_HPP
#define _PFSP_NEIGHBORHOOD_REXCHANGE_HPP

#include <stddef.h>
#include "pfsp/neighborhood/functor.hpp"

namespace pfsp{
namespace neighborhood{


/**
 * Function template for exchange neighborhood walkthrough.
 * <p>
 * Function template for exchange neighborhood walkthrough.
 * The function applies a callback on each neighbour and
 * returns if the return value of the callback evaluates to false.
 * Neighborhood is explored in a 'Who could I change place with?' way,
 * beginning with the last position.
 *
 * @author Ooms Aurélien
 * 
 * @param <S> Solution type
 * @param <FN> Callback pointer type
 * @param <M> Perturbation type
 *
 * @param src the solution whose neighborhood is explored
 * @param fn the callback pointer
 * 
 */

template<typename S, typename FN, typename M>
struct rexchange : functor<S, FN>{
	void operator()(const S& src, FN fn){
		if(src.size() < 2) return;

		const size_t s = src.size(), f = s - 2;

		for(size_t i = f; i > 0; --i){
			for(size_t j = i + 1; j < s; ++j){
				if(!(*fn)(M(i, j))) return;
			}
		}
	}
};




} // neighborhood
} // pfsp

#endif // _PFSP_NEIGHBORHOOD_REXCHANGE_HPP