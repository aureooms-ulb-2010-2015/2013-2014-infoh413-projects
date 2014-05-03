#ifndef _PFSP_NEIGHBORHOOD_SINSERT_HPP
#define _PFSP_NEIGHBORHOOD_SINSERT_HPP

#include <stddef.h>
#include <vector>
#include "lib/random/sample.hpp"

#include "pfsp/neighborhood/functor.hpp"

namespace pfsp{
namespace neighborhood{


/**
 * Functor template for insert neighborhood random walkthrough.
 *
 * @author Ooms Aurélien
 * 
 * @param <G> generator type
 * @param <D> distribution type
 * @param <S> Solution type
 * @param <FN> Callback pointer type
 * @param <M> Perturbation type
 * 
 */

template<typename G, typename D, typename S, typename FN, typename M>
struct sinsert : functor<S, FN>{

	G& g;

	sinsert(G& g):g(g){

	}

	/**
	 * Implementation of pfsp::neighborhood::functor<S,FN>::operator(const S&, FN)
	 * Neighborhood is explored in a random way.
	 */


	virtual void operator()(const S& src, FN fn){
		if(src.size() < 2) return;

		const size_t s = src.size(), f = s - 1, t = (f-1) * (f-1);

		std::vector<M> v(t);

		size_t k = t;
		for(size_t i = 1; i < f; ++i){
			v[--k] = M(i, i + 1);
			for(size_t j = i + 2; j < s; ++j){
				v[--k] = M(i, j);
				v[--k] = M(j, i);
			}
		}

		lib::random::sample<G, D, std::vector<M>, size_t>(g, t, v, 0, t);

		k = t;
		while(k) if(!(*fn)(v[--k])) return;
	}


};



} // neighborhood
} // pfsp

#endif // _PFSP_NEIGHBORHOOD_SINSERT_HPP