#ifndef _PFSP_SA_TYPES_HPP
#define _PFSP_SA_TYPES_HPP

#include "pfsp_commons/types.hpp"

//
// MEANING OF THOSES TYPES ARE SELF-EVIDENT
// IF NOT: CHECK PFSP AND LIB DOCUMENTATION
// 

typedef M (*RS)(random_engine&, const S&);
typedef addr_t (*SI)(const S&);


typedef struct{
	W walk;
	X apply;
	ME eval;
	RS random;
	SI size;
} EN;


typedef double real;
typedef std::uniform_real_distribution<real> uniform_real_distribution;

typedef void (*RW)(random_engine&, RS, const S&, H);


#endif // _PFSP_SA_TYPES_HPP