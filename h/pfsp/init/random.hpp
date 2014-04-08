#ifndef _PFSP_INIT_RANDOM_HPP
#define _PFSP_INIT_RANDOM_HPP

#include "lib/random/sample.hpp"
#include "pfsp/init/functor.hpp"

#include <numeric>

namespace pfsp{
namespace init{


/**
 * Class template for random solution generators.
 * 
 * @author Ooms Aurélien
 *
 * @param <G> random generator type
 * @param <D> distribution type
 * @param <S> solution type
 * @param <T> array index type
 *
 */

template<typename G, typename D, typename S, typename T = size_t>
struct random{

	struct fn : functor<S>{
		G& g;
		fn(G& g):g(g){};


		/**
		 * Implementation of pfsp::init::functor<S>::operator()(S&).
		 */

		virtual void operator()(S& sol){
			std::iota(sol.begin(), sol.end(), 0);
			lib::random::sample<G, D, S, T>(g, sol.size() - 1, sol, 1, sol.size());
		}
		
	};

	fn f;

	random(G& g):f(g){}

};


} // init
} // pfsp

#endif // _PFSP_INIT_RANDOM_HPP