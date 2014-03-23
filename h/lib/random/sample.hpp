#ifndef _LIB_RANDOM_SAMPLE_HPP
#define _LIB_RANDOM_SAMPLE_HPP

namespace lib{
namespace random{

template<typename G, typename D, typename A, typename T = size_t>
void sample(G& generator, const T n, A& a, const T i, const T j){


	T t = i - 1;
	const T x = i + n;
	
	while(++t < x){
		D randint(t, j - 1);
		const T k = randint(generator);
		std::swap(a[t], a[k]);
	}

}

}
}

#endif // _LIB_RANDOM_SAMPLE_HPP