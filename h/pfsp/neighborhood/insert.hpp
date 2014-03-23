#ifndef _PFSP_NEIGHBORHOOD_INSERT_HPP
#define _PFSP_NEIGHBORHOOD_INSERT_HPP

namespace pfsp{
namespace neighborhood{


// 	void shift(const size_t i, size_t j){
// 		typename S::value_type tmp = (*src)[i];
// 		src->erase(src->begin() + i);
// 		src->insert(src->begin() + j, tmp);
// 	}

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

// template<typename S>
// class insert{
// protected:
// 	const S* src = nullptr;
// 	S  sol;
// 	size_t i = 0, j = 1;

// public:
// 	insert(const insert& it):src(it.src), sol(it.sol), i(it.i), j(it.j){}

// 	insert(const S& src):src(&src), sol(src){
// 		std::swap(sol[0], sol[1]);
// 	}

// 	insert(const S& src, const size_t i, const size_t j):src(&src), i(i), j(j){
// 		if(i < f(*this->src)){
// 			sol = src;
// 			shift(i, j);
// 		}
// 	}

// 	insert& operator ++(){
// 		shift(j, i);
// 		if(++j == i) ++j;
// 		if(j == s(*this->src)){
// 			++i;
// 			j = 0;
// 			if(i == f(*this->src)) return *this;
// 		}
// 		shift(i, j);
// 		return *this;
// 	}

// 	void shift(const size_t i, size_t j){
// 		typename S::value_type tmp = sol[i];
// 		sol.erase(sol.begin() + i);
// 		sol.insert(sol.begin() + j, tmp);
// 	}
	
// 	S& operator *(){
// 		return sol;
// 	}

// 	S* operator->() const{
// 		return &sol;
// 	}

// 	bool operator !=(const insert& it) const{
// 		return this->i != it.i || this->j != it.j;
// 	}

// 	bool operator ==(const insert& it) const{
// 		return this->i == it.i && this->j == it.j;
// 	}

// 	static insert begin(const S& src){
// 		return insert(src);
// 	}

// 	static insert end(const S& src){
// 		return insert(src, f(src), s(src));
// 	}

// 	static size_t f(const S& src){
// 		return src.size();
// 	}

// 	static size_t s(const S& src){
// 		return src.size();
// 	}
// };

}
}

#endif // _PFSP_NEIGHBORHOOD_INSERT_HPP