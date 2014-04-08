#ifndef _PFSP_IO_PARSE_HEADER_HPP
#define _PFSP_IO_PARSE_HEADER_HPP


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
 * 
 * @param stream The stream to read from
 * @param nbJob Vertical size of the instance
 * @param nbMac Horizontal size of the instance
 *
 */

template<typename S, typename T>
void header(S& stream, T& nbJob, T& nbMac){
	stream >> nbJob;
	stream >> nbMac;
}

} // parse
} // io
} // pfsp


#endif // _PFSP_IO_PARSE_HEADER_HPP