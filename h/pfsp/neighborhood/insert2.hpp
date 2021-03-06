#ifndef _PFSP_NEIGHBORHOOD_INSERT2_HPP
#define _PFSP_NEIGHBORHOOD_INSERT2_HPP

#include <stddef.h>
#include "pfsp/neighborhood/functor.hpp"

namespace pfsp{
namespace neighborhood{


/**
 * Function template for insert neighborhood walkthrough.
 * <p>
 * Function template for insert neighborhood walkthrough.
 * The function applies a callback on each neighbour and
 * returns if the return value of the callback evaluates to false.
 * Neighborhood is explored in a 'i goes in j or j goes in i' way,
 * beginning with the first position.
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
 * /!\ M(i, i+1) <=> M(i+1, i)
 * 
 */

template<typename S, typename FN, typename M>
struct insert2 : functor<S, FN>{
	void operator()(const S& src, FN fn){
		if(src.size() < 2) return;

		const size_t s = src.size(), f = s - 1;

		for(size_t i = 1; i < f; ++i){
			if(!(*fn)(M(i, i + 1))) return;
			for(size_t j = i + 2; j < s; ++j){
				if(!(*fn)(M(i, j))) return;
				if(!(*fn)(M(j, i))) return;
			}
		}
	}
};



} // neighborhood
} // pfsp

#endif // _PFSP_NEIGHBORHOOD_INSERT2_HPP