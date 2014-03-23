#ifndef _PFSP_INSTANCE_HPP
#define _PFSP_INSTANCE_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

namespace pfsp{

template<typename addr_t, typename val_t, typename priority_t>
class instance{
public:
	typedef val_t val;

	addr_t nbJob;
	addr_t nbMac;
	std::vector<val_t> dueDates;
	std::vector<priority_t> priority;

	std::vector<std::vector<val_t>> processingTimesMatrix;
};

}

#endif
