#ifndef _PFSP_APPLY_INSERT_HPP
#define _PFSP_APPLY_INSERT_HPP

#include <tuple>
namespace pfsp{
namespace apply{

template<typename S, typename M>
void insert(S& sol, const M& mutation){

	typename S::value_type tmp = sol[std::get<0>(mutation)];
	sol.erase(sol.begin() + std::get<0>(mutation));
	sol.insert(sol.begin() + std::get<1>(mutation), tmp);
	
}

}
}

#endif // _PFSP_APPLY_INSERT_HPP