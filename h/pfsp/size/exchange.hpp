#ifndef _PFSP_SIZE_EXCHANGE_HPP
#define _PFSP_SIZE_EXCHANGE_HPP

#include <stddef.h>

namespace pfsp{
namespace size{


/**
 * Function template for exchange neighborhood size computation.
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
addr_t exchange(const S& src){
	return (src.size() - 1) * (src.size() - 2) / 2;
}




} // size
} // pfsp

#endif // _PFSP_SIZE_EXCHANGE_HPP