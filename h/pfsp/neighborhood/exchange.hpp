#ifndef _PFSP_NEIGHBORHOOD_EXCHANGE_HPP
#define _PFSP_NEIGHBORHOOD_EXCHANGE_HPP

namespace pfsp{
namespace neighborhood{

template<typename S, typename FN>
void exchange(const S& src, FN fn){
	if(src.size() < 2) return;

	S sol(src);

	const size_t s = src.size(), f = s - 1;

	for(size_t i = 0; i < f; ++i){
		for(size_t j = i + 1; j < s; ++j){
			std::swap(sol[i], sol[j]);
			if(!(*fn)(sol)) return;
			std::swap(sol[j], sol[i]);
		}
	}
}

// template<typename S>
// class exchange{
// protected:
// 	const S* src = nullptr;
// 	S  sol;
// 	size_t i = 0, j = 1;

// public:
// 	exchange(const exchange& it):src(it.src), sol(it.sol), i(it.i), j(it.j){}

// 	exchange(const S& src):src(&src), sol(src){
// 		std::swap(sol[0], sol[1]);
// 	}

// 	exchange(const S& src, const size_t i, const size_t j):src(&src), i(i), j(j){
// 		if(i < f(*this->src)){
// 			sol = src;
// 			std::swap(sol[i], sol[j]);
// 		}
// 	}

// 	exchange& operator ++(){
// 		std::swap(sol[i], sol[j++]);
// 		if(j == s(*this->src)){
// 			++i;
// 			j = i + 1;
// 			if(i == f(*this->src)) return *this;
// 		}
// 		std::swap(sol[i], sol[j]);
// 		return *this;
// 	}
	
// 	S& operator *(){
// 		return sol;
// 	}

// 	S* operator->() const{
// 		return &sol;
// 	}

// 	bool operator !=(const exchange& it) const{
// 		return this->i != it.i || this->j != it.j;
// 	}

// 	bool operator ==(const exchange& it) const{
// 		return this->i == it.i && this->j == it.j;
// 	}

// 	static exchange begin(const S& src){
// 		return exchange(src);
// 	}

// 	static exchange end(const S& src){
// 		return exchange(src, f(src), s(src));
// 	}

// 	static size_t f(const S& src){
// 		return src.size() - 1;
// 	}

// 	static size_t s(const S& src){
// 		return src.size();
// 	}
// };


}
}

#endif // _PFSP_NEIGHBORHOOD_EXCHANGE_HPP