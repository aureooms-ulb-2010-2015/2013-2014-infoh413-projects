#ifndef _INFOH413_IO_PARSE_HEADER_H
#define _INFOH413_IO_PARSE_HEADER_H


namespace infoh413{
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


#endif // _INFOH413_IO_PARSE_HEADER_H