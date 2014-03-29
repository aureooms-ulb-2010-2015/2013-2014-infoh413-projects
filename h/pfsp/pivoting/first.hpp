#ifndef _PFSP_PIVOTING_FIRST_HPP
#define _PFSP_PIVOTING_FIRST_HPP

#include <limits>
#include <memory>

#include "pfsp/pivoting/functor.hpp"


namespace pfsp{
namespace pivoting{

/*
 * <S> is the solution type
 * <M> is the mutation type
 * <W> is the neighborhood walker type
 * <ME> is the mutation evaluator type
 * <X> is the muter type
 */


template<typename R, typename val_t, typename S, typename M, typename W, typename ME>
R first(S& src, W w, ME e){

	struct fn : functor<M>{
		ME e;
		const S& sol;
		val_t opt;
		M argopt;
		
		fn(ME e, const S& sol):e(e), sol(sol), opt(0), argopt(){}

		virtual bool operator()(const M& mutation){
			val_t delta = (*e)(sol, mutation);
			if(delta < opt){
				argopt = mutation;
				opt = delta;
				return false;
			}
			return true;
		}
	} f(e, src);

	w(src, &f);
	return R(f.opt, f.argopt);
}

}
}

#endif // _PFSP_PIVOTING_FIRST_HPP