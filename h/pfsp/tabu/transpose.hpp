#ifndef _PFSP_TABU_TRANSPOSE_HPP
#define _PFSP_TABU_TRANSPOSE_HPP

#include <stddef.h>
#include <tuple>

namespace pfsp{
namespace tabu{


/**
 * Function template for transpose neighborhood tabu checking.
 * <p>
 * Function template for transpose neighborhood tabu checking.
 * The function returns if pair m is tabu.
 *
 * @author Ooms Aurélien
 * 
 * @param <S> Solution type
 * @param <M> Perturbation type
 * @param <T> Tabu array type
 * @param <K> Step type
 *
 * @param s current solution
 * @param m perturbation to check
 * @param tabu tabu array
 * @param k release step
 * 
 */

template<typename S, typename M, typename T, typename K>
bool transpose(const S& s, const M& m, const T& tabu, const K k){
	return tabu[s[std::get<0>(m)]] > k || tabu[s[std::get<1>(m)]] > k;
}




} // tabu
} // pfsp

#endif // _PFSP_TABU_TRANSPOSE_HPP