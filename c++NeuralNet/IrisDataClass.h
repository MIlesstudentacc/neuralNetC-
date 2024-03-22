#pragma once
#include <string>
#include <vector>
#include <iostream>
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
	void setSepalLength(double newSepalLength);
	void setSepalWidth(double newSepalWidth);
	void setPetalLength(double newPetalLength);
	void setPetalWidth(double newPetalWidth); 
	void setClass(std::string Class);
	void copyObjArg(double newSepalLength,double newSepalWidth,
		double newPetalLength,double newPetalWidth);
	void displayAttributes();




};


