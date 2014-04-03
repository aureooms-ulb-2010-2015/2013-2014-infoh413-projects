#ifndef _PFSP_MEM_ALLOCATE_HPP
#define _PFSP_MEM_ALLOCATE_HPP


namespace pfsp{
namespace mem{

template<typename A1, typename A2, typename A3, typename T>
void allocate(A1& processing, A2& dueDates, A3& priority, const T nbJ, const T nbM){

	processing.resize((nbJ + 1) * (nbM + 1));
	dueDates.resize(nbJ + 1);
	priority.resize(nbJ + 1);

}

}
}


#endif // _PFSP_MEM_ALLOCATE_HPP