#ifndef _PFSP_ACCEPT_METROPOLIS_HPP
#define _PFSP_ACCEPT_METROPOLIS_HPP

#include <cmath>

#include "pfsp/accept/functor.hpp"


namespace pfsp{
namespace accept{


/**
 * Functor template for metropolis condition neighborhood accept.
 *
 * <p>
 * Functor template for metropolis condition neighborhood accept.
 * Works by forwarding a callback to a neighborhood explorer.
 *
 * @author Ooms Aurélien
 * 
 * @param <G> is the generator type
 * @param <D> is the real distribution type
 * @param <real> is the real number type
 * @param <V> is the opt type
 * @param <M> is the perturbation type
 * 
 */


template<typename G, typename D, typename real, typename V, typename M>
struct metropolis : functor<V>{

	G& generator;
	D& distribution;
	const real& T;
	const V& val;

	/**
	 * ctor
	 * 
	 * @param generator
	 * @param distribution
 	 * @param T temperature ref
	 * @param val twt reference
	 */
	
	metropolis(G& generator, D& distribution, const real& T, const V& val):
	generator(generator), distribution(distribution), T(T), val(val){}


	/**
	 * Implementation of
	 * pfsp::accept::functor<V>::operator()(const V)
	 */

	virtual bool operator()(const V delta){
		return distribution(generator) < std::exp(- real(delta) / real(val) / T);
	}

};

} // accept
} // pfsp

#endif // _PFSP_ACCEPT_METROPOLIS_HPP