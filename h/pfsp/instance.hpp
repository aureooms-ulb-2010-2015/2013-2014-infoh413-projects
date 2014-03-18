#ifndef _PFSP_INSTANCE_HPP
#define _PFSP_INSTANCE_HPP

#include <string>
#include <vector>

namespace pfsp{

class Instance{
public:
	int nbJob;
	int nbMac;
	std::vector<long int> dueDates;
	std::vector<long int> priority;

	std::vector<std::vector<long int>> processingTimesMatrix;

	Instance();
	~Instance();

	/* Read write privates attributs : */
	int getNbJob();
	int getNbMac();

	/* Read\Write values in the matrix : */
	long int getTime(int job, int machine);
	void setTime(int job, int machine, long int processTime);

	long int getDueDate(int job);
	void setDueDate(int job, int value);

	long int getPriority(int job);
	void setPriority(int job, int value);

	long int computeWT(std::vector<int>& sol);
};

}

#endif
