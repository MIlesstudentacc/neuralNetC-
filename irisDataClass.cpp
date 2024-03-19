#include "irisDataClass.h"

irisDataClass::irisDataClass()
{

}

irisDataClass::irisDataClass(double sepalLength, double sepalWidth, double petalLength, double petalWidth, std::string Class)
{
	this->sepalLength = sepalLength;
	this->sepalWidth = sepalWidth;
	this->petalLength = petalLength;
	this->petalWidth = petalWidth;
	this->Class = Class;
}

double irisDataClass::getSepalLength()
{
	return sepalLength;
}

double irisDataClass::getSepalWidth()
{
	return sepalWidth;
}

double irisDataClass::getPetalLength()
{
	return petalLength;
}

double irisDataClass::getPetalWidth()
{
	return petalWidth;
}

std::string irisDataClass::getClass()
{
	return Class;
}



