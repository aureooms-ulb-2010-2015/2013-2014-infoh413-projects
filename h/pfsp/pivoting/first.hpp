#ifndef _PFSP_PIVOTING_FIRST_HPP
#define _PFSP_PIVOTING_FIRST_HPP

#include <limits>
#include <memory>

#include "pfsp/pivoting/functor.hpp"


namespace pfsp{
namespace pivoting{


/**
 * Function template for first improvement neighborhood pivoting.
 *
 * <p>
 * Function template for first improvement neighborhood pivoting.
 * Works by forwarding a callback to a neighborhood explorer.
 *
 * @author Ooms Aurélien
 * 
 * @param <R> is the return value type
 * @param <val_t> is the opt type
 * @param <S> is the solution type
 * @param <M> is the perturbation type
 * @param <W> is the neighborhood walker type
 * @param <ME> is the perturbation evaluator type
 *
 * @param src The current solution
 * @param w The neighborhood walker pointer
 * @param e The perturbation evaluator pointer
 */


template<typename R, typename val_t, typename S, typename M, typename W, typename ME>
R first(const S& src, W w, ME e){

	struct fn : functor<M>{
		ME e;
		const S& sol;
		val_t opt;
		M argopt;
		
		fn(ME e, const S& sol):e(e), sol(sol), opt(0), argopt(){}

		virtual bool operator()(const M& mutation){
			val_t delta = (*e)(sol, mutation);
			if(delta < opt){
				opt = delta;
				argopt = mutation;
				return false;
			}
			return true;
		}
	} f(e, src);

	(*w)(src, &f);
	return R(f.opt, f.argopt);
}

} // pivoting
} // pfsp

#endif // _PFSP_PIVOTING_FIRST_HPP