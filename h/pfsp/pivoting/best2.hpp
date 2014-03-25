#ifndef _PFSP_PIVOTING_BEST_HPP
#define _PFSP_PIVOTING_BEST_HPP

#include <limits>
#include <memory>

#include "pfsp/pivoting/functor.hpp"


namespace pfsp{
namespace pivoting{


template<typename S, typename N, typename E>
S best(const S& src, N n, E e){

	typedef typename E::val val_t;

	S sol(src);

	struct fn : functor<S>{
		E e;
		val_t opt;
		S& argopt;
		
		fn(E e, S& sol):e(e), opt(e(sol)), argopt(sol){}

		virtual bool operator()(const S& sol){
			val_t tmp = e(sol);
			if(tmp < opt){
				argopt = sol;
				opt = tmp;
			}
			return true;
		}
	} f(e, sol);

	for(auto& e : n(sol)){
		val_t aug = a(sol, e);
		if(aug > opt){
			argopt = e;
			opt = aug;
		}
	}

	n(src, &f);
	return sol;
}

}
}

#endif // _PFSP_PIVOTING_BEST_HPP