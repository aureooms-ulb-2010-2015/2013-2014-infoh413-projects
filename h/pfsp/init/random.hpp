#ifndef _PFSP_INIT_RANDOM_HPP
#define _PFSP_INIT_RANDOM_HPP

#include "lib/random/sample.hpp"
#include "pfsp/init/functor.hpp"


namespace pfsp{
namespace init{

template<typename G, typename D, typename S, typename T>
void random(G& g, S& sol){

	struct fn : functor<S>{
		E e;
		val_t opt = std::numeric_limits<val_t>::max();
		S& argopt;
		fn(E e, S& sol):e(e), argopt(sol){};

		virtual bool operator()(S& sol){
			std::iota(sol.begin(), sol.end(), 0);
			lib::random::sample<G, D, S, T>(g, sol.size(), sol, 1, sol.size() + 1);
		}
	} f(e, sol);

}



template<typename S, typename N, typename E>
S best(const S& src, N n, E e){

	typedef typename E::val val_t;

	S sol;

	struct fn : functor<S>{
		E e;
		val_t opt = std::numeric_limits<val_t>::max();
		S& argopt;
		fn(E e, S& sol):e(e), argopt(sol){};

		virtual bool operator()(const S& sol){
			val_t tmp = e(sol);
			if(tmp < opt){
				argopt = sol;
				opt = tmp;
			}
			return true;
		}
	} f(e, sol);

	n(src, &f);
	return sol;
}

}
}

#endif // _PFSP_INIT_RANDOM_HPP