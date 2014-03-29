#ifndef _PFSP_PIVOTING_FUNCTOR_HPP
#define _PFSP_PIVOTING_FUNCTOR_HPP

namespace pfsp{
namespace pivoting{

template<typename M>
struct functor{
	virtual bool operator()(const M& mutation) = 0;
};

}
}

#endif // _PFSP_PIVOTING_FUNCTOR_HPP