#pragma once
#include <string>
class IrisDataClass
{
	double sepalLength;
	double sepalWidth;
	double petalLength;
	double petalWidth;
	std::string Class;
public:
	IrisDataClass(double sepalLength,double sepalWidth,double petalLength,double petalWidth,std::string Class); 

	double getSepalLength();
	double getSepalWidth();
	double getPetalLength();
	double getPetalWidth();
	std::string getClass(); 
	 
};

