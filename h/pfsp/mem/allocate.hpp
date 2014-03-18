#ifndef _PFSP_MEM_ALLOCATE_HPP
#define _PFSP_MEM_ALLOCATE_HPP


namespace pfsp{
namespace mem{

template<typename A1, typename A2, typename A3, typename T>
void allocate(A1& processingTimesMatrix, A2& dueDates, A3& priority, const T nbJ, const T nbM){
	processingTimesMatrix.resize(nbJ + 1);

	for(T i = 0; i < nbJ + 1; ++i) processingTimesMatrix[i].resize(nbM + 1);

	dueDates.resize(nbJ + 1);
	priority.resize(nbJ + 1);
}

}
}


#endif // _PFSP_MEM_ALLOCATE_HPP