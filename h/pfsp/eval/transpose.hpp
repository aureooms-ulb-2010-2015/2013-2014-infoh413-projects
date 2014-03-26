#ifndef _PFSP_EVAL_TRANSPOSE_HPP
#define _PFSP_EVAL_TRANSPOSE_HPP

namespace pfsp{
namespace eval{

template<typename S, typename M>
void transpose(const S& src, const M& m){
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

#endif // _PFSP_EVAL_TRANSPOSE_HPP