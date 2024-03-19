#pragma once
#include <string>
#include <vector>
class irisDataClass
{
	double sepalLength;
	double sepalWidth;
	double petalLength;
	double petalWidth;
	std::string Class;
	std::vector<irisDataClass*> sampleSet;
public:

	irisDataClass(); 

	irisDataClass(double sepalLength, double sepalWidth, double petalLength, double petalWidth, std::string Class);

	double getSepalLength();
	double getSepalWidth();
	double getPetalLength();
	double getPetalWidth();
	std::string getClass();




};


