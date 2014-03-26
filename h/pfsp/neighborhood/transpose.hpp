#ifndef _PFSP_NEIGHBORHOOD_TRANSPOSE_HPP
#define _PFSP_NEIGHBORHOOD_TRANSPOSE_HPP

namespace pfsp{
namespace neighborhood{

template<typename S, typename FN>
void transpose(const S& src, FN fn){
	if(src.size() < 2) return;

	S sol(src);

	const size_t n = src.size() - 1;

	for(size_t i = 1; i < n; ++i){
		std::swap(sol[i], sol[i+1]);
		if(!(*fn)(sol)) return;
		std::swap(sol[i+1], sol[i]);
	}
}

}
}

#endif // _PFSP_NEIGHBORHOOD_TRANSPOSE_HPP