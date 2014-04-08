#ifndef _PFSP_MEM_ALLOCATE_HPP
#define _PFSP_MEM_ALLOCATE_HPP


namespace pfsp{
namespace mem{


/**
 * Function template for instance memory allocation.
 * 
 * @author Ooms Aurélien
 * 
 * @param <A1> dueDates array type
 * @param <A2> priority array type
 * @param <A3> processing array type
 * @param <T> array index type
 * 
 * @param processing Processing times job x machine matrix
 * @param dueDates Jobs due dates array
 * @param priority Jobs priorities array
 * @param nbJob Vertical size of the instance
 * @param nbMac Horizontal size of the instance
 *
 */

template<typename A1, typename A2, typename A3, typename T>
void allocate(A1& processing, A2& dueDates, A3& priority, const T nbJob, const T nbMac){

	processing.resize((nbJob + 1) * (nbMac + 1));
	dueDates.resize(nbJob + 1);
	priority.resize(nbJob + 1);

}

} // mem
} // pfsp


#endif // _PFSP_MEM_ALLOCATE_HPP