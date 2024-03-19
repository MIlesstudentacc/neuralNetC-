#pragma once
#include <string>
class irisDataClass
{
	double sepalLength;
	double sepalWidth;
	double petalLength;
	double petalWidth;
	std::string Class;
public:
	irisDataClass(double sepalLength, double sepalWidth, double petalLength, double petalWidth, std::string Class);

	double getSepalLength();
	double getSepalWidth();
	double getPetalLength();
	double getPetalWidth();
	std::string getClass();

};


