#ifndef _PFSP_RANDOM_TRANSPOSE_HPP
#define _PFSP_RANDOM_TRANSPOSE_HPP

#include <stddef.h>

namespace pfsp{
namespace random{


/**
 * Function template for transpose neighborhood random neighbour generation.
 * <p>
 * Function template for transpose neighborhood random neighbour generation.
 * The function returns a pair (i, i + 1), chosen uniformly at random.
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
M transpose(G& generator, const S& src){

	D randi(1, src.size() - 2);

	const auto i = randi(generator);

	return M(i, i + 1);
}




} // random
} // pfsp

#endif // _PFSP_RANDOM_TRANSPOSE_HPP