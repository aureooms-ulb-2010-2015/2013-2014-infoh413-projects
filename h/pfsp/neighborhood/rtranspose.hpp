#ifndef _PFSP_NEIGHBORHOOD_RTRANSPOSE_HPP
#define _PFSP_NEIGHBORHOOD_RTRANSPOSE_HPP

#include <stddef.h>
#include "pfsp/neighborhood/functor.hpp"

namespace pfsp{
namespace neighborhood{


/**
 * Function template for transpose neighborhood walkthrough.
 * <p>
 * Function template for transpose neighborhood walkthrough.
 * The function applies a callback on each neighbour and
 * returns if the return value of the callback evaluates to false.
 * Neighborhood is explored in a sequential way,
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
struct rtranspose : functor<S, FN>{
	void operator()(const S& src, FN fn){
		if(src.size() < 2) return;

		const size_t n = src.size() - 2;

		for(size_t i = n; i > 0; --i){
			if(!(*fn)(M(i, i+1))) return;
		}
	}
};






} // neighborhood
} // pfsp

#endif // _PFSP_NEIGHBORHOOD_RTRANSPOSE_HPP