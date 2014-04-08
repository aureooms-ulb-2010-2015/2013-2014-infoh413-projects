#ifndef _PFSP_INIT_FUNCTOR_HPP
#define _PFSP_INIT_FUNCTOR_HPP


namespace pfsp{
namespace init{


/**
 * Interface template for initial solution generators.
 * 
 * @author Ooms Aurélien
 *
 * @param <S> solution type
 *
 */

template<typename S>
struct functor{


	/**
	 * Virtual operator() for initial solution generation.
	 * <p>
	 * Generates an initial solution.
	 *
	 * @param sol The solution
	 *
	 */
	
	virtual void operator()(S& sol) = 0;
};

} // init
} // pfsp



#endif // _PFSP_INIT_FUNCTOR_HPP