#ifndef _PFSP_APPLY_TRANSPOSE_HPP
#define _PFSP_APPLY_TRANSPOSE_HPP

#include <tuple>

namespace pfsp{
namespace apply{

template<typename S, typename M>
void transpose(S& sol, const M& mutation){
	std::swap(sol[std::get<0>(mutation)], sol[std::get<1>(mutation)]);
}

}
}

#endif // _PFSP_APPLY_TRANSPOSE_HPP