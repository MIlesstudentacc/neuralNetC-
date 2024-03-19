#pragma once
#include "iostream"

#include <vector>
#include "sstream"
#include "fstream"
#include "IrisDataClass.h"
class fileReader
{
private:
	std::vector<IrisDataClass> irisRows; 
public:
	
	void readFile(std::string csvFile);

};

