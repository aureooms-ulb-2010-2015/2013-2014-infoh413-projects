#ifndef _PFSP_PIVOTING_FUNCTOR_HPP
#define _PFSP_PIVOTING_FUNCTOR_HPP

namespace pfsp{
namespace pivoting{

/**
 * Functor template for neighborhood exploration callbacks.
 *
 * @author Ooms Aurélien
 *
 * @param <M> perturbation type
 *
 */

template<typename M>
struct functor{

	/**
	 * Virtual operator() for solution perturbation handling.
	 * 
	 * <p>
	 * Virtual operator() for solution perturbation handling.
	 * Returns false if exploration can stop immediatly.
	 *
	 * @param mutation the perturbation to handle
	 *
	 */

	virtual bool operator()(const M& mutation) = 0;
};

} // pivoting
} // pfsp

#endif // _PFSP_PIVOTING_FUNCTOR_HPP