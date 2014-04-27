#ifndef _PFSP_PIVOTING_METROPOLIS_OR_BEST_HPP
#define _PFSP_PIVOTING_METROPOLIS_OR_BEST_HPP

#include <cmath>
#include <limits>

#include "pfsp/pivoting/functor.hpp"


namespace pfsp{
namespace pivoting{


/**
 * Function template for metropolis condition neighborhood pivoting.
 *
 * <p>
 * Function template for metropolis condition neighborhood pivoting.
 * Works by forwarding a callback to a neighborhood explorer.
 *
 * @author Ooms Aurélien
 * 
 * @param <G> is the generator type
 * @param <D> is the distribution type
 * @param <R> is the return value type
 * @param <val_t> is the opt type
 * @param <S> is the solution type
 * @param <M> is the perturbation type
 * @param <W> is the neighborhood walker type
 * @param <ME> is the perturbation evaluator type
 * @param <real> is the real number type
 *
 * @param generator
 * @param distribution
 * @param src The current solution
 * @param w The neighborhood walker pointer
 * @param e The perturbation evaluator pointer
 */


template<typename G, typename D, typename real, typename R, typename val_t, typename S, typename M, typename W, typename ME>
R metropolis_or_best(G& generator, D& distribution, const real T, const S& src, W w, ME e){

	struct fn : functor<M>{
		G& generator;
		D& distribution;
		const real T;
		ME e;
		const S& sol;
		val_t opt;
		M argopt;
		
		fn(G& generator, D& distribution, const real T, ME e, const S& sol):
		generator(generator), distribution(distribution), T(T), e(e),
		sol(sol), opt(std::numeric_limits<val_t>::max()), argopt(){}

		virtual bool operator()(const M& mutation){

			val_t delta = (*e)(sol, mutation);

			bool accept = false;

			if(delta < 0) accept = true;
			else if(delta == 0) accept = distribution(generator) < 0.5;
			else accept = distribution(generator) < std::exp(-real(delta) / T);

			if(delta <= opt){
				opt = delta;
				argopt = mutation;
			}

			return !accept;
		}
	} f(generator, distribution, T, e, src);

	w(src, &f);
	return R(f.opt, f.argopt);
}

} // pivoting
} // pfsp

#endif // _PFSP_PIVOTING_METROPOLIS_OR_BEST_HPP