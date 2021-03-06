#ifndef _PFSP_APPLY_TRANSPOSE_HPP
#define _PFSP_APPLY_TRANSPOSE_HPP

#include <tuple>

namespace pfsp{
namespace apply{


/**
 * Function template for transpose neighborhood perturbation application.
 *
 * @param <S> solution type
 * @param <M> perturbation type
 *
 * @param sol The solution the perturbation will be applied to
 * @param mutation The perturbation to apply
 *
 * @author Ooms Aurélien
 *
 */

template<typename S, typename M>
void transpose(S& sol, const M& mutation){
	std::swap(sol[std::get<0>(mutation)], sol[std::get<1>(mutation)]);
}

} // apply
} // pfsp

#endif // _PFSP_APPLY_TRANSPOSE_HPP