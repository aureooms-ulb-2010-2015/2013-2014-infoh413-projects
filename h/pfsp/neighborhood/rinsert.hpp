#ifndef _PFSP_NEIGHBORHOOD_RINSERT_HPP
#define _PFSP_NEIGHBORHOOD_RINSERT_HPP

namespace pfsp{
namespace neighborhood{

template<typename S, typename FN, typename M>
void rinsert(const S& src, FN fn){
	if(src.size() < 2) return;


	const size_t s = src.size(), f = s - 2;

	for(size_t i = f; i > 0; --i){
		for(size_t j = i + 1; j < s; ++j){
			if(!(*fn)(M(i, j))) return;
			if(!(*fn)(M(j, i))) return;
		}
	}
}

}
}

#endif // _PFSP_NEIGHBORHOOD_RINSERT_HPP