#ifndef _PFSP_RANDOM_EXCHANGE_HPP
#define _PFSP_RANDOM_EXCHANGE_HPP

#include <stddef.h>

namespace pfsp{
namespace random{


/**
 * Function template for exchange neighborhood random neighbour generation.
 * <p>
 * Function template for exchange neighborhood random neighbour generation.
 * The function returns a pair (i, j), i < j, chosen uniformly at random.
 *
 * @author Ooms Aurélien
 * 
 * @param <G> Generator type
 * @param <D> Distribution type
 * @param <S> Solution type
 * @param <M> Perturbation type
 *
 * @param generator
 * @param src the solution whose neighborhood is explored
 * 
 */

template<typename G, typename D, typename S, typename M>
M exchange(G& generator, const S& src){

	D randi(1, src.size() - 1);
	D randj(1, src.size() - 2);

	const auto i = randi(generator);
	const auto j = randj(generator);

	return j >= i ? M(i, j + 1) : M(j, i);
}




} // random
} // pfsp

#endif // _PFSP_RANDOM_EXCHANGE_HPP