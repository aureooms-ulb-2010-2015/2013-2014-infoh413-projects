#ifndef _PFSP_RANDOM_SAMPLE_HPP
#define _PFSP_RANDOM_SAMPLE_HPP

#include <stddef.h>
#include <tuple>

namespace pfsp{
namespace random{


/**
 * Function template for neighborhood sampling.
 * <p>
 * Function template for neighborhood sampling.
 * The function returns the best mutation for a solution s,
 * from a sample of size k,
 * using perturbation genarator pg and petrubation evaluator pe.
 *
 * @author Ooms Aurélien
 * 
 * @param <G> Generator type
 * @param <V> Value  type
 * @param <S> Solution type
 * @param <P> Perturbation type
 * @param <PE> Perturbation evaluator type
 * @param <PG> Perturbation generator type
 *
 * @param generator
 * @param src the solution whose neighborhood is explored
 * @param k > 0
 * 
 */

template<typename G, typename V, typename S, typename P, typename PE, typename PG>
std::pair<P, V> sample(G& g, const S& s, PG pg, PE pe, size_t k){

	P argopt = (*pg)(g, s);
	V opt = (*pe)(s, argopt);

	while(--k){
		P p = (*pg)(g, s);
		V v = (*pe)(s, p);
		if(v < opt){
			opt = v;
			argopt = p;
		}
	}

	return std::pair<P, V>(argopt, opt);
}




} // random
} // pfsp

#endif // _PFSP_RANDOM_SAMPLE_HPP