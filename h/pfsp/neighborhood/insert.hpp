#ifndef _PFSP_NEIGHBORHOOD_INSERT_HPP
#define _PFSP_NEIGHBORHOOD_INSERT_HPP

#include <stddef.h>

namespace pfsp{
namespace neighborhood{


/**
 * Function template for insert neighborhood walkthrough.
 * <p>
 * Function template for insert neighborhood walkthrough.
 * The function applies a callback on each neighbour and
 * returns if the return value of the callback evaluates to false.
 * Neighborhood is explored in a 'Where could I go?' way,
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
void insert(const S& src, FN fn){
	if(src.size() < 2) return;

	const size_t n = src.size();

	for(size_t i = 1; i < n; ++i){
		for(size_t j = 1; j < i; ++j){
			if(!(*fn)(M(i, j))) return;
		}
		for(size_t j = i + 2; j < n; ++j){
			if(!(*fn)(M(i, j))) return;
		}
	}
}

} // neighborhood
} // pfsp

#endif // _PFSP_NEIGHBORHOOD_INSERT_HPP