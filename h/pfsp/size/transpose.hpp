#ifndef _PFSP_SIZE_TRANSPOSE_HPP
#define _PFSP_SIZE_TRANSPOSE_HPP

#include <stddef.h>

namespace pfsp{
namespace size{


/**
 * Function template for transpose neighborhood size computation.
 *
 * @author Ooms Aurélien
 *
 * @param <addr_t> return type
 * @param <S> Solution type
 *
 * @param src the solution whose neighborhood size is computed
 *
 * @return the neighborhood size
 * 
 */

template<typename addr_t, typename S>
addr_t transpose(const S& src){
	return (src.size() - 2);
}




} // size
} // pfsp

#endif // _PFSP_SIZE_TRANSPOSE_HPP