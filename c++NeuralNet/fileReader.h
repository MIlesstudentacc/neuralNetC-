#pragma once
#include "iostream"

#include <vector>
#include "sstream"
#include "fstream"
#include "irisDataClass.h"
#include <map>
class fileReader
{
private:
	std::vector<irisDataClass*> irisRows;
	std::vector<int> classID;
	std::vector<irisDataClass*> SampleSet;
	std::map<std::string, int> numericalFormClass;
	irisDataClass* maxAttribute = new irisDataClass(); 
	irisDataClass* minAttribute = new irisDataClass();
	double petalLengthMean;
	double petalWidthMean;
	double sepalLengthMean;
	double sepalWidthMean;


public:


	std::vector<int> getClassID();
	void readFile(std::string csvFile);

	void generateSampleSet();

	irisDataClass* takeSampleFromSet();

	int getNumberFromClass(std::string Class);
	
	int getSampleSetSize();

	std::vector<irisDataClass*>  getSampleSet();

	void updateMax(irisDataClass* row);

	void updateMin(irisDataClass* row);

	irisDataClass* normalise(irisDataClass* Sample);

	void standardDeviation(); 

	void calcMeans();

	irisDataClass* standardDeviationOne(irisDataClass* sample);
};
