#ifndef _PFSP_IO_PARSE_HEADER_HPP
#define _PFSP_IO_PARSE_HEADER_HPP


namespace pfsp{
namespace io{
namespace parse{

template<typename S, typename INT>
void header(S& stream, INT& nbJob, INT& nbMac){
	stream >> nbJob;
	stream >> nbMac;
}

}
}
}


#endif // _PFSP_IO_PARSE_HEADER_HPP