#ifndef _PFSP_EVAL_FUNCTOR_HPP
#define _PFSP_EVAL_FUNCTOR_HPP

namespace pfsp{
namespace eval{

template<typename V, typename S, typename M, typename A4, typename A5>
struct functor{
	virtual V operator()(const S& sol, const M& mutation) = 0;
	virtual V operator()(const S& sol, const M& mutation, A4& detail, A5& wt) = 0;
};

}
}

#endif // _PFSP_EVAL_FUNCTOR_HPP