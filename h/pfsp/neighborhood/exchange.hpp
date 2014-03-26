#ifndef _PFSP_NEIGHBORHOOD_EXCHANGE_HPP
#define _PFSP_NEIGHBORHOOD_EXCHANGE_HPP

namespace pfsp{
namespace neighborhood{

template<typename S, typename FN>
void exchange(const S& src, FN fn){
	if(src.size() < 2) return;

	S sol(src);

	const size_t s = src.size(), f = s - 1;

	for(size_t i = 1; i < f; ++i){
		for(size_t j = i + 1; j < s; ++j){
			std::swap(sol[i], sol[j]);
			if(!(*fn)(sol)) return;
			std::swap(sol[j], sol[i]);
		}
	}
}


}
}

#endif // _PFSP_NEIGHBORHOOD_EXCHANGE_HPP