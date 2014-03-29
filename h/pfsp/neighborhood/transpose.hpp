#ifndef _PFSP_NEIGHBORHOOD_TRANSPOSE_HPP
#define _PFSP_NEIGHBORHOOD_TRANSPOSE_HPP

namespace pfsp{
namespace neighborhood{

template<typename S, typename FN, typename M>
void transpose(const S& src, FN fn){
	if(src.size() < 2) return;

	const size_t n = src.size() - 1;

	for(size_t i = 1; i < n; ++i){
		if(!(*fn)(M(i, i+1))) return;
	}
}

}
}

#endif // _PFSP_NEIGHBORHOOD_TRANSPOSE_HPP