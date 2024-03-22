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

void irisDataClass::setSepalLength(double newSepalLength)
{
	sepalLength = newSepalLength;
}

void irisDataClass::setSepalWidth(double newSepalWidth)
{
	sepalWidth = newSepalWidth;
}

void irisDataClass::setPetalLength(double newPetalLength)
{
	petalLength = newPetalLength;
}

void irisDataClass::setPetalWidth(double newPetalWidth)
{
	petalWidth = newPetalWidth; 
}

void irisDataClass::setClass(std::string Class)
{
	this->Class =Class;
}

void irisDataClass::copyObjArg(double newSepalLength, double newSepalWidth, double newPetalLength, double newPetalWidth)
{
	setPetalLength(newPetalLength);
	setPetalWidth(newPetalWidth);
	setSepalLength(newSepalLength);
	setSepalWidth(newSepalWidth);
}

void irisDataClass::displayAttributes()
{
	std::cout << "displaying attributes" << std::endl; 
	std::cout << petalLength << std::endl;
	std::cout << petalWidth << std::endl;
	std::cout << sepalLength << std::endl;
	std::cout << sepalWidth << std::endl; 
}




