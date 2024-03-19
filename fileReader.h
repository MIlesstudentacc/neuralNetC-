#pragma once
#include "iostream"

#include <vector>
#include "sstream"
#include "fstream"
#include "irisDataClass.h"
class fileReader
{
private:
	std::vector<irisDataClass*> irisRows;
public:

	void readFile(std::string csvFile);

};
