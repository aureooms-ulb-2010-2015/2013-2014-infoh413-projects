#ifndef _PFSP_NEIGHBORHOOD_INSERT_HPP
#define _PFSP_NEIGHBORHOOD_INSERT_HPP

namespace pfsp{
namespace neighborhood{

template<typename S, typename FN, typename M>
void insert(const S& src, FN fn){
	if(src.size() < 2) return;


	const size_t n = src.size();

	for(size_t i = 1; i < n; ++i){
		for(size_t j = 1; j < i; ++j){
			if(!(*fn)(M(i, j))) return;
		}
		for(size_t j = i + 1; j < n; ++j){
			if(!(*fn)(M(i, j))) return;
		}
	}
}

}
}

#endif // _PFSP_NEIGHBORHOOD_INSERT_HPP