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
 * <N> is the neighborhood walker type
 * <A> is the augmentation evaluator type
 * <X> is the muter type
 */


template<typename S, typename M, typename N, typename A, typename X>
bool first(S& src, N n, A a, X x){

	typedef typename A::val val_t;

	struct fn : functor<S>{
		A a;
		const S& sol;
		val_t opt;
		M argopt;
		
		fn(A a, const S& sol):a(a), sol(sol), opt(0), argopt(N::id){}

		virtual bool operator()(const M& mutation){
			val_t delta = a(sol, mutation);
			if(delta < opt){
				argopt = mutation;
				opt = delta;
				return false;
			}
			return true;
		}
	} f(a, src);

	n(src, &f);
	x(src, f.argopt);
	return f.opt;
}

}
}

#endif // _PFSP_PIVOTING_FIRST_HPP