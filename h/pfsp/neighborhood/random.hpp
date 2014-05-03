#ifndef _PFSP_NEIGHBORHOOD_RANDOM_HPP
#define _PFSP_NEIGHBORHOOD_RANDOM_HPP

#include <stddef.h>
#include "pfsp/neighborhood/functor.hpp"

namespace pfsp{
namespace neighborhood{


/**
 * Function template for neighborhood random walkthrough.
 * <p>
 * Function template for neighborhood random walkthrough.
 * The function applies a callback on a neighbor chosen uniformly at random and
 * returns if the return value of the callback evaluates to false.
 * Else repeat.
 *
 * @author Ooms Aurélien
 * 
 * @param <G> generator type
 * @param <PG> Perturbation generator type
 * @param <S> Solution type
 * @param <FN> Callback pointer type
 * @param <M> Perturbation type
 *
 * @param generator
 * @param pg Perturbation generator
 * @param src the solution whose neighborhood is explored
 * @param fn the callback pointer
 * 
 */

template<typename G, typename PG, typename S, typename FN, typename M>
struct random : functor<S, FN>{
	void operator()(G& generator, PG pg, const S& src, FN fn){
		while((*fn)((*pg)(generator, src)));
	}
};




} // neighborhood
} // pfsp

#endif // _PFSP_NEIGHBORHOOD_RANDOM_HPP