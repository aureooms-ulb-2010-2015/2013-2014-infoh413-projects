#ifndef _PFSP_INIT_FUNCTOR_HPP
#define _PFSP_INIT_FUNCTOR_HPP


namespace pfsp{
namespace init{

template<typename S>
struct functor{
	virtual void operator()(S& sol) = 0;
};

}
}



#endif // _PFSP_INIT_FUNCTOR_HPP