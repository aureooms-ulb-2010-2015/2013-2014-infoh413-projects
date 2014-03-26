#ifndef _PFSP_EVAL_EXCHANGE_HPP
#define _PFSP_EVAL_EXCHANGE_HPP

namespace pfsp{
namespace eval{

template<typename S, typename M>
void exchange(const S& src, const M& m){
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

#endif // _PFSP_EVAL_EXCHANGE_HPP