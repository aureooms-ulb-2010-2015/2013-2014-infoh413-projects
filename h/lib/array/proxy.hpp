#ifndef _LIB_ARRAY_PROXY_HPP
#define _LIB_ARRAY_PROXY_HPP



namespace lib{
namespace array{
	
template<typename T>
class proxy{
public:

	T* pt;
	T** addr = nullptr;
	size_t h, w;


	proxy(){}

	proxy(T* pt, const size_t h, const size_t w) : pt(pt), h(h), w(w){
		alloc();
	}

	void resize(T* pt, const size_t h, const size_t w){
		this->pt = pt;
		this->h = h;
		this->w = w;
		delete[] addr;
		alloc();
	}

	void alloc(){
		addr = new T*[h];
		for(size_t i = 0; i < h; ++i) addr[i] = pt + i * w;
	}

	inline T* operator[](const size_t i){
		return addr[i];
	}

	inline const T* operator[](const size_t i) const{
		return addr[i];
	}

	~proxy(){
		delete[] addr;
	}



};



}
}



#endif // _LIB_ARRAY_PROXY_HPP