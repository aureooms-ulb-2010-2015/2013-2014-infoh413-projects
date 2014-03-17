#ifndef _PFSPINSTANCEWT_H_
#define _PFSPINSTANCEWT_H_

#include <string>
#include <vector>

class PfspInstance{
public:
	int nbJob;
	int nbMac;
	std::vector<long int> dueDates;
	std::vector<long int> priority;

	std::vector<std::vector<long int>> processingTimesMatrix;

	PfspInstance();
	~PfspInstance();

	/* Read write privates attributs : */
	int getNbJob();
	int getNbMac();

	/* Allow the memory for the processing times matrix : */
	void allowMatrixMemory(const int nbJ, const int nbM);

	/* Read\Write values in the matrix : */
	long int getTime(int job, int machine);
	void setTime(int job, int machine, long int processTime);

	long int getDueDate(int job);
	void setDueDate(int job, int value);

	long int getPriority(int job);
	void setPriority(int job, int value);

	/* Read Data from a file : */
	bool readDataFromFile(char* fileName);

	long int computeWT(std::vector<int>& sol);
};

#endif
