#ifndef _PFSP_IG_TYPES_HPP
#define _PFSP_IG_TYPES_HPP

#include "pfsp_commons/types.hpp"

//
// MEANING OF THOSES TYPES ARE SELF-EVIDENT
// IF NOT: CHECK PFSP AND LIB DOCUMENTATION
// 


typedef double real;
typedef std::uniform_real_distribution<real> uniform_real_distribution;

typedef pfsp::eval::insert<addr_t, val_t, priority_t, S, M, DD, PR, PMP, PM, DD, PMP> PIE;


#endif // _PFSP_IG_TYPES_HPP