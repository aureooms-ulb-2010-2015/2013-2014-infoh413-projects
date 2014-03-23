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

// template<typename S>
// class transpose{
// protected:
// 	const S* src = nullptr;
// 	S  sol;
// 	size_t i = 0;

// public:
// 	transpose(const transpose& it):src(it.src), sol(it.sol), i(it.i){}

// 	transpose(const S& src):src(&src), sol(src){
// 		std::swap(sol[0], sol[1]);
// 	}

// 	transpose(const S& src, const size_t i):src(&src), i(i){
// 		if(i < n(*this->src)){
// 			sol = src;
// 			std::swap(sol[i], sol[i+1]);
// 		}
// 	}

// 	transpose& operator ++(){
// 		std::swap(sol[i], sol[++i]);
// 		if(i < n(*this->src)) std::swap(sol[i], sol[i+1]);
// 		return *this;
// 	}
	
// 	S& operator *(){
// 		return sol;
// 	}

// 	S* operator->() const{
// 		return &sol;
// 	}

// 	bool operator !=(const transpose& it) const{
// 		return this->i != it.i;
// 	}

// 	bool operator ==(const transpose& it) const{
// 		return this->i == it.i;
// 	}

// 	static transpose begin(const S& src){
// 		return transpose(src);
// 	}

// 	static transpose end(const S& src){
// 		return transpose(src, n(src));
// 	}

// 	static size_t n(const S& src){
// 		return src.size() - 1;
// 	}
// };

}
}

#endif // _PFSP_NEIGHBORHOOD_TRANSPOSE_HPP