#ifndef _PFSP_EVAL_FUNCTOR_HPP
#define _PFSP_EVAL_FUNCTOR_HPP

namespace pfsp{
namespace eval{

template<typename V, typename S, typename M>
struct functor{
	virtual V operator()(const S& sol, const M& mutation) = 0;
};

}
}

#endif // _PFSP_EVAL_FUNCTOR_HPP