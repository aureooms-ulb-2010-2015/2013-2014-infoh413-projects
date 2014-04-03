#ifndef _PFSP_INSTANCE_HPP
#define _PFSP_INSTANCE_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

namespace pfsp{

template<typename addr_t, typename val_t, typename priority_t, typename DD, typename PR, typename PM>
class instance{
public:
	typedef val_t val;

	addr_t nbJob;
	addr_t nbMac;

	DD dueDates;
	PR priority;
	PM processing;
};

}

#endif
