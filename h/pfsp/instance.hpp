#ifndef _PFSP_INSTANCE_HPP
#define _PFSP_INSTANCE_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

namespace pfsp{

/**
 * Class template for storing instance data.
 *
 * @author Ooms Aurélien
 * 
 * @param <addr_t> array index type
 * @param <val_t> weighted tardiness type
 * @param <priority_t> priority type
 * @param <DD> due dates array type
 * @param <PR> priority array type
 * @param <PM> processing matrix type
 *
 */

template<
	typename addr_t,
	typename val_t,
	typename priority_t,
	typename DD,
	typename PR,
	typename PM
>
class instance{
public:

	/**
	 * Number of jobs
	 */
	
	addr_t nbJob;


	/**
	 * Number of machines
	 */
	
	addr_t nbMac;


	/**
	 * Due dates array (1-based)
	 */

	DD dueDates;


	/**
	 * Priority array (1-based)
	 */
	
	PR priority;


	/**
	 * Processing matrix (1-based)
	 */
	
	PM processing;
};

} // pfsp

#endif
