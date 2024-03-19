#include "IrisDataClass.h"

IrisDataClass::IrisDataClass(double sepalLength, double sepalWidth, double petalLength, double petalWidth, std::string Class)
{
	this->sepalLength = sepalLength;
	this->sepalWidth = sepalWidth;
	this->petalLength = petalLength;
	this->petalWidth = petalWidth;
	this->Class = Class; 
}

double IrisDataClass::getSepalLength()
{
	return sepalLength;
}

double IrisDataClass::getSepalWidth()
{
	return sepalWidth;
}

double IrisDataClass::getPetalLength()
{
	return petalLength;
}

double IrisDataClass::getPetalWidth()
{
	return petalWidth;
}

std::string IrisDataClass::getClass()
{
	return Class;
	
}
