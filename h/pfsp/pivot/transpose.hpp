#ifndef _PFSP_PIVOT_TRANSPOSE_HPP
#define _PFSP_PIVOT_TRANSPOSE_HPP

namespace pfsp{
namespace pivot{

template<typename S>
class transpose{
public:

	S* src = nullptr;
	S  p;

	transpose(S& src):src(src){
		p.resize(src.size());
	}

	S& operator ++(){
		pt = pt->next;
		return *this;
	}

	S operator ++(int){
		arc_iterator it = *this;
		pt = pt->next;
		return it;
	}
};

}
}

#endif // _PFSP_PIVOT_TRANSPOSE_HPP