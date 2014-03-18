#ifndef _PFSP_IO_PARSE_HEADER_HPP
#define _PFSP_IO_PARSE_HEADER_HPP


namespace pfsp{
namespace io{
namespace parse{

template<typename S, typename INT>
void header(S& stream, INT& nbJob, INT& nbMac){

	stream >> nbJob;
	std::cout << "Number of jobs : " << nbJob << std::endl;

	stream >> nbMac;
	std::cout << "Number of machines : " << nbMac << std::endl;

}

}
}
}


#endif // _PFSP_IO_PARSE_HEADER_HPP