#ifndef _PFSP_ACCEPT_FUNCTOR_HPP
#define _PFSP_ACCEPT_FUNCTOR_HPP

namespace pfsp{
namespace accept{

/**
 * Functor template for acceptance criterion evaluators.
 *
 * @author Ooms Aurélien
 *
 * @param <V> val type
 *
 */

template<typename V>
struct functor{

	/**
	 * Virtual operator() for acceptance criterion evaluator.
	 * 
	 * <p>
	 * Virtual operator() for acceptance criterion evaluator.
	 * Returns if perturbation is accepted.
	 *
	 * @param val delta < 0
	 *
	 */

	virtual bool operator()(const V val) = 0;
};

} // accept
} // pfsp

#endif // _PFSP_ACCEPT_FUNCTOR_HPP