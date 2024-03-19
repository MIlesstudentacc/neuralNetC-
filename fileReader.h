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

	std::map<std::string, int> numericalFormIdentifier;
	std::vector<irisDataClass*> SampleSet;
public:


	std::vector<int> getClassID();
	void readFile(std::string csvFile);

	void generateSampleSet();

	irisDataClass* takeSampleFromSet();

	std::vector<irisDataClass*> getSampleSet();
	
	



};
