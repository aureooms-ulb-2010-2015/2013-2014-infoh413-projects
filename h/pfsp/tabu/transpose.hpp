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
 * @param <M> Perturbation type
 * @param <T> Tabu array type
 * @param <K> Step type
 *
 * @param m perturbation to check
 * @param tabu tabu array
 * @param k release step
 * 
 */

template<typename M, typename T, typename K>
bool transpose(const M& m, const T& tabu, const K k){
	return tabu[std::get<0>(m)] > k || tabu[std::get<1>(m)] > k;
}




} // tabu
} // pfsp

#endif // _PFSP_TABU_TRANSPOSE_HPP