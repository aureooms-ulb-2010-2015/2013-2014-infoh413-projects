#ifndef _PFSP_NEIGHBORHOOD_INSERT2_HPP
#define _PFSP_NEIGHBORHOOD_INSERT2_HPP

namespace pfsp{
namespace neighborhood{

template<typename S, typename FN, typename M>
void insert2(const S& src, FN fn){
	if(src.size() < 2) return;



	const size_t s = src.size(), f = s - 1;

	for(size_t i = 1; i < f; ++i){
		for(size_t j = i + 1; j < s; ++j){
			if(!(*fn)(M(i, j))) return;
			if(!(*fn)(M(j, i))) return;
		}
	}
}

}
}

#endif // _PFSP_NEIGHBORHOOD_INSERT2_HPP