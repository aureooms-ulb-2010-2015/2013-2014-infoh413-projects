#ifndef _PFSP_PIVOTING_BEST_HPP
#define _PFSP_PIVOTING_BEST_HPP

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


template<typename val_t, typename S, typename M, typename W, typename ME, typename X>
val_t best(S& src, W w, ME e, X x){

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
			}
			return true;
		}
	} f(e, src);

	w(src, &f);
	if(f.opt < 0) x(src, f.argopt);
	return f.opt;
}

}
}

#endif // _PFSP_PIVOTING_BEST_HPP