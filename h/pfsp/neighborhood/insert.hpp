#ifndef _PFSP_NEIGHBORHOOD_INSERT_HPP
#define _PFSP_NEIGHBORHOOD_INSERT_HPP

namespace pfsp{
namespace neighborhood{

template<typename S, typename FN>
void insert(const S& src, FN fn){
	if(src.size() < 2) return;

	S sol(src);

	const size_t n = src.size();

	for(size_t i = 1; i < n; ++i){
		for(size_t j = 1; j < i; ++j){
			typename S::value_type tmp = sol[i];
			sol.erase(sol.begin() + i);
			sol.insert(sol.begin() + j, tmp);
			if(!(*fn)(sol)) return;
			sol.erase(sol.begin() + j);
			sol.insert(sol.begin() + i, tmp);
		}
		for(size_t j = i + 1; j < n; ++j){
			typename S::value_type tmp = sol[i];
			sol.erase(sol.begin() + i);
			sol.insert(sol.begin() + j, tmp);
			if(!(*fn)(sol)) return;
			sol.erase(sol.begin() + j);
			sol.insert(sol.begin() + i, tmp);
		}
	}
}

}
}

#endif // _PFSP_NEIGHBORHOOD_INSERT_HPP