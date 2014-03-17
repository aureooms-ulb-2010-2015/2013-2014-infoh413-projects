#ifndef _INFOH413_IO_PARSE_BODY_H
#define _INFOH413_IO_PARSE_BODY_H


namespace infoh413{
namespace io{
namespace parse{

template<typename S, typename T, typename A1, typename A2, typename A3>
void body(S& stream, const T nbJob, const T nbMac, A1& processingTimesMatrix, A2& dueDates, A3& priority){


	long int readValue;
	int not_used_i;
	std::string not_used_s;

	for(T j = 1; j <= nbJob; ++j){
		for(T m = 1; m <= nbMac; ++m){
			stream >> not_used_i; // The number of each machine, not important !
			stream >> readValue; // Process Time

			processingTimesMatrix[j][m] = readValue;
		}
	}

	stream >> not_used_s; // this is not read

	for(T j = 1; j <= nbJob; ++j){
		stream >> not_used_i; // -1
		stream >> readValue;
		dueDates[j] = readValue;
		stream >> not_used_i; // -1
		stream >> readValue;
		priority[j] = readValue;
	}
}

}
}
}


#endif // _INFOH413_IO_PARSE_BODY_H