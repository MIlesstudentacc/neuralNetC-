#pragma once
#include "iostream"

#include <vector>
#include "sstream"
#include "fstream"
#include "IrisDataClass.h"
#include <map>
class fileReader
{
private:
	std::vector<irisDataClass*> irisRows; 
	std::vector<int> classID;
	std::map<std::string, int> numericalFormClass;

	std::vector<irisDataClass*> SampleSet; 
public:
	
	std::vector<int> getClassID(); 
	void readFile(std::string csvFile);
	
	std::vector<irisDataClass*> getSampleSet();

	void generateSampleSet(); 

	irisDataClass* takeSampleFromSet();

	int getNumberFromClass(std::string Class); 
};

					