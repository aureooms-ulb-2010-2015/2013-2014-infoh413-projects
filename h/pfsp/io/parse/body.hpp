#ifndef _PFSP_IO_PARSE_BODY_HPP
#define _PFSP_IO_PARSE_BODY_HPP

#include <string>

namespace pfsp{
namespace io{
namespace parse{

/**
 * Function template for instance files body parsing.
 * 
 * @author Ooms Aurélien
 * 
 * @param <S> input stream type
 * @param <T> array index type
 * @param <A1> dueDates array type
 * @param <A2> priority array type
 * @param <A3> processing array type
 * 
 * @param stream The stream to read from
 * @param nbJob Vertical size of the instance
 * @param nbMac Horizontal size of the instance
 * @param processing Processing times job x machine matrix
 * @param dueDates Jobs due dates array
 * @param priority Jobs priorities array
 *
 */

template<typename S, typename T, typename A1, typename A2, typename A3>
void body(S& stream, const T nbJob, const T nbMac, A1& processing, A2& dueDates, A3& priority){


	T not_used_addr_t;
	std::string not_used_string;

	for(T j = 1; j <= nbJob; ++j){
		for(T m = 1; m <= nbMac; ++m){
			stream >> not_used_addr_t;
			stream >> processing[j][m];
		}
	}

	stream >> not_used_string;

	for(T j = 1; j <= nbJob; ++j){
		stream >> not_used_addr_t;
		stream >> dueDates[j];

		stream >> not_used_addr_t;
		stream >> priority[j];
	}
}

} // parse
} // io
} // pfsp


#endif // _PFSP_IO_PARSE_BODY_HPP