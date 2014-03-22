#ifndef _PFSP_INIT_SLACK_HPP
#define _PFSP_INIT_SLACK_HPP

#include "lib/random/sample.hpp"
#include "pfsp/init/functor.hpp"


namespace pfsp{
namespace init{

template<typename G, typename D, typename S, typename T>
struct slack{

	struct fn : functor<S>{
		G& g;
		fn(G& g):g(g){};

		virtual void operator()(S& sol){
			std::iota(sol.begin(), sol.end(), 0);
			lib::random::sample<G, D, S, T>(g, sol.size(), sol, 1, sol.size() + 1);
		}
	};

	fn f;

	slack(G& g):f(g){}

};


}
}

#endif // _PFSP_INIT_SLACK_HPP