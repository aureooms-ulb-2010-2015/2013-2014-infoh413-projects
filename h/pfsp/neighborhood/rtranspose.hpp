#ifndef _PFSP_NEIGHBORHOOD_RTRANSPOSE_HPP
#define _PFSP_NEIGHBORHOOD_RTRANSPOSE_HPP

namespace pfsp{
namespace neighborhood{

template<typename S, typename FN, typename M>
void rtranspose(const S& src, FN fn){
	if(src.size() < 2) return;

	const size_t n = src.size() - 2;

	for(size_t i = n; i > 0; --i){
		if(!(*fn)(M(i, i+1))) return;
	}
}

}
}

#endif // _PFSP_NEIGHBORHOOD_RTRANSPOSE_HPP