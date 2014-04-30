#ifndef _PFSP_NEIGHBORHOOD_FUNCTOR_HPP
#define _PFSP_NEIGHBORHOOD_FUNCTOR_HPP

#include <stddef.h>

namespace pfsp{
namespace neighborhood{


/**
 * Functor interface template for neighborhood walkthrough.
 *
 * @author Ooms Aurélien
 * 
 * @param <S> Solution type
 * @param <FN> Callback pointer type
 *
 * 
 */

template<typename S, typename FN>
struct functor{

	/**
	 * Walker operator.
	 * The function applies a callback on each neighbour and
	 * returns if the return value of the callback evaluates to false.
	 * 
	 * @author Ooms Aurélien
	 *
	 * @param src the solution whose neighborhood is explored
	 * @param fn the callback pointer
	 */
	virtual void operator()(const S& src, FN fn) = 0;

	virtual ~functor(){}

};






} // neighborhood
} // pfsp

#endif // _PFSP_NEIGHBORHOOD_FUNCTOR_HPP