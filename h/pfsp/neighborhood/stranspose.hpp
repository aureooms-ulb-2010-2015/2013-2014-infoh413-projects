#ifndef _PFSP_NEIGHBORHOOD_STRANSPOSE_HPP
#define _PFSP_NEIGHBORHOOD_STRANSPOSE_HPP

#include <stddef.h>

namespace pfsp{
namespace neighborhood{


/**
 * Function template for transpose neighborhood random walkthrough.
 * <p>
 * Function template for transpose neighborhood random walkthrough.
 * The function applies a callback on each neighbour and
 * returns if the return value of the callback evaluates to false.
 * Neighborhood is explored in a random way.
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
void stranspose(const S& src, FN fn){
	if(src.size() < 2) return;

	const size_t n = src.size() - 1;

	for(size_t i = 1; i < n; ++i){
		if(!(*fn)(M(i, i+1))) return;
	}
}






} // neighborhood
} // pfsp

#endif // _PFSP_NEIGHBORHOOD_STRANSPOSE_HPP