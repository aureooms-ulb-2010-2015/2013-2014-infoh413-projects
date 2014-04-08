#ifndef _PFSP_EVAL_FUNCTOR_HPP
#define _PFSP_EVAL_FUNCTOR_HPP

namespace pfsp{
namespace eval{


/**
 * Interface template for partial evaluation functors.
 * 
 * @author Ooms Aurélien
 *
 * @param <V> delta wt type
 * @param <S> solution type
 * @param <M> perturbation type
 * @param <A6> detail array type
 * @param <A5> wt array type
 *
 */

template<typename V, typename S, typename M, typename A6, typename A5>
struct functor{


	/**
	 * Virtual operator() for partial evaluation.
	 * <p>
	 * Evaluates a perturbation on a solution.
	 *
	 * @param sol The current solution
	 * @param mutation The perturbation to evaluate
	 * 
	 * @return the evaluation delta
	 *
	 */
	
	virtual V operator()(const S& sol, const M& mutation) = 0;


	/**
	 * Virtual operator() for partial evaluation.
	 * <p>
	 * Evaluates a perturbation on a solution and updates
	 * the current solution detail and wt arrays.
	 *
	 * @param sol The current solution
	 * @param mutation The perturbation to evaluate
	 * @param detail The current solution detail array
	 * @param wt The current solution wt array
	 * 
	 * 
	 * @return the evaluation delta
	 *
	 */
	
	virtual V operator()(const S& sol, const M& mutation, A6& detail, A5& wt) = 0;
};

} // eval
} // pfsp

#endif // _PFSP_EVAL_FUNCTOR_HPP