#ifndef _PFSP_PIVOTING_FUNCTOR_HPP
#define _PFSP_PIVOTING_FUNCTOR_HPP

namespace pfsp{
namespace pivoting{

template<typename S>
struct functor{
	virtual bool operator()(const S& sol) = 0;
};

}
}

#endif // _PFSP_PIVOTING_FUNCTOR_HPP