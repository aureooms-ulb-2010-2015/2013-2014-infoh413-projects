#ifndef _PFSP_PIVOTING_METROPOLIS_HPP
#define _PFSP_PIVOTING_METROPOLIS_HPP

#include <cmath>

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
 * @param <D> is the real distribution type
 * @param <PG> is the perturbation generator type
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
 * @param pg perturbation generator
 * @param T temperature ref
 * @param src The current solution
 * @param w The neighborhood walker pointer
 * @param e The perturbation evaluator pointer
 */


template<typename G, typename D, typename PG, typename real, typename R, typename val_t, typename S, typename M, typename W, typename ME>
R metropolis(G& generator, D& distribution, PG pg, const real T, const S& src, W w, ME e){

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
		sol(sol), opt(), argopt(){}

		virtual bool operator()(const M& mutation){

			val_t delta = (*e)(sol, mutation);

			bool accept = false;

			if(delta < 0) accept = true;
			else if(delta == 0) accept = distribution(generator) < 0.5;
			else accept = distribution(generator) < std::exp(-real(delta) / T);

			if(accept){
				opt = delta;
				argopt = mutation;
			}

			return !accept;
		}
	} f(generator, distribution, T, e, src);

	w(generator, pg, src, &f);
	return R(f.opt, f.argopt);
}

} // pivoting
} // pfsp

#endif // _PFSP_PIVOTING_METROPOLIS_HPP