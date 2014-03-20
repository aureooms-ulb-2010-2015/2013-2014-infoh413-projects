#ifndef _PFSP_PIVOTING_FIRST_HPP
#define _PFSP_PIVOTING_FIRST_HPP

#include <limits>

#include "pfsp/pivoting/functor.hpp"


namespace pfsp{
namespace pivoting{


template<typename S, typename N, typename E>
S first(const S& src, N n, E e){

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
				return false;
			}
			return true;
		}
	} f(e, sol);

	n(src, &f);
	return sol;
}

}
}

#endif // _PFSP_PIVOTING_FIRST_HPP