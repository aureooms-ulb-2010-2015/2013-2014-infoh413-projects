#ifndef _PFSP_TABU_TYPES_HPP
#define _PFSP_TABU_TYPES_HPP

#include "pfsp_commons/types.hpp"

//
// MEANING OF THOSES TYPES ARE SELF-EVIDENT
// IF NOT: CHECK PFSP AND LIB DOCUMENTATION
// 

typedef M (*RS)(random_engine&, const S&);

typedef size_t K;
typedef std::vector<K> A7;

typedef bool (*TABU)(const M& m, const A7& tabu, const K k);


typedef struct{
	W walk;
	X apply;
	ME eval;
	RS random;
	TABU tabu;
} EN;


typedef double real;
typedef std::uniform_real_distribution<real> uniform_real_distribution;

typedef void (*RW)(random_engine&, RS, const S&, H);


#endif // _PFSP_TABU_TYPES_HPP