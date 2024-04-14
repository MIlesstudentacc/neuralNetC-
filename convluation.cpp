#include "convluation.h"
#include <iostream>
#include <vector>

void convluation::setDimensions(int x, int y)
{
	dimensionX = x;
	dimensionY = y; 
}

void convluation::setInputMap()
{
	dimensionX = dimensionX + 2;
	dimensionY = dimensionY + 2; 
	inputMap = new double[dimensionX * dimensionY];
	newMap= new double[dimensionX * dimensionY];
	oldMap = new double[dimensionX * dimensionY];
	for (int i = 0; i < dimensionX; i++)
	{
		inputMap[i] = 0; 
		inputMap[i +((dimensionY-1)*dimensionX)] =0;

	}
	for (int i = 0; i < dimensionY; i++)
	{
		int index = (i* dimensionY);
		inputMap[index] = 0;
		inputMap[index+(dimensionX-1)]=0;

	}
	memcpy(newMap, inputMap, sizeof(double)* (dimensionX * dimensionY));
	
}

void convluation::setKernel(Kernel* myKernal)
{
	this->myKernel = myKernal;
}

void convluation::populateInputMap(double* inputs)
{
	
	int origStart = (1 * dimensionY)+1;
	int start = 1;
	int end = (dimensionY - 1) * (dimensionX);
	for (int y = 1; y < dimensionY-1; y = y + 1)
	{
		start = start + dimensionY;
		
		for (int i= start; i < ((start+dimensionX)-2); i++)
		{
			int inputIndex = i - origStart;
			double mapVal = inputs[i - origStart];
			inputMap[i] = inputs[i - origStart];

		}
		origStart = origStart + 2;
	}
}

void convluation::outputMap()
{
	int size = (dimensionY * dimensionX);
	for (int i = 0; i < size; i++)
	{
		std::cout << "id : "<< i << "value" << inputMap[i] << std::endl;
		if (i % 5 == 0)
		{
			std::cout << "______" << std::endl;
		}
	}

}

void convluation::sendToOld()
{
	memcpy(oldMap, newMap, sizeof(double) * dimensionX * dimensionY);
}




void convluation::restoreMap()
{
	if (oldMap != nullptr)
	{
		inputMap = oldMap;
	}
}

void convluation::fixKernelUpdate()
{
	int size = (dimensionY * dimensionX);
	int paddingBias = (1 * dimensionX) + 1;
	double nextMapValue = 0;
	for (int y = 0; y < dimensionY - 2; y++)
	{

		for (int x = 0; x < dimensionX - 2; x++)
		{
			int i = (y * dimensionX) + x;
			for (int kernalY = 0; kernalY < 3; kernalY++)
			{
				for (int kernalX = 0; kernalX < 3; kernalX++)
				{
					double toAdd;
					int multiplier = (dimensionY * kernalY);
					int index = i + kernalX;
					index = index + multiplier;
					toAdd = myKernel->calcOneWeightSum((kernalY * 3) + kernalX, inputMap[index]);
					nextMapValue = nextMapValue + toAdd;


				}
			
				
			}
			int bpTest = i + paddingBias;
			newMap[i + paddingBias] = nextMapValue;
			nextMapValue = 0;
		}
		//paddingBias = paddingBias + 1;
	}
}

void convluation::setInputMap(double* inputMap)
{
	this->inputMap = inputMap;
}
double* convluation::getNewMap()
{
	return newMap;
}

int convluation::getDimensionX()
{
	return dimensionX;
}

int convluation::getDimensionY()
{
	return dimensionX;
}

void convluation::setCompareMap(double* toCompare)
{
	this->compareMap = toCompare;
}

void convluation::setInputMapValue(int index, double value)
{
	inputMap[index] = value;
}

double convluation::GetValueAtIndex(int index)
{
	return inputMap[index];
}

double convluation::sigmoid(double x)
{
	double result;
	result = 1 / (1 + exp(-x));
	return result;
}

void convluation::updateAttachedKernel()
{
	int avgFactor = (dimensionX * dimensionY) / 9;
	myKernel->updateWeights(avgFactor, LEARNING_RATE);
	myKernel->updateBias(avgFactor, LEARNING_RATE);
}

double convluation::derivativeSigmoid(double x)
{
	return(1 - sigmoid(x));
}

void convluation::setLearningRate(double newLearningRate)
{
	LEARNING_RATE = newLearningRate;
}

double* convluation::getOldMap()
{
	return oldMap;
}

void convluation::localBackPropToFF(double* convDerivative,std::vector<double> costDerivativeVector, node*** FFInpLayer)
{
	int paddingBias = (1 * dimensionX) + 1;
	int kernalCount = -1;
	for (int y = 0; y < dimensionY - 2; y++)
	{
		for (int x = 0; x < dimensionX - 2; x++)
		{
			int i = (y * dimensionX) + x;
			kernalCount = kernalCount + 1;
			double biasUpdate = 1 * derivativeSigmoid(oldMap[kernalCount + paddingBias]) * costDerivativeVector[kernalCount];
			myKernel->addToBias(biasUpdate);
			for (int kernalY = 0; kernalY < 3; kernalY++)
			{
				for (int kernalX = 0; kernalX < 3; kernalX++)
				{
					double toAdd;
					int multiplier = (dimensionY * kernalY);
					int index = i + kernalX;
					index = index + multiplier;
					std::cout << kernalCount << "THIS IS problem " << std::endl;
					double weight = myKernel->getWeightAtIndex((kernalY * 3) + kernalX);
					//for FF TO CONV use kernal count as for deriv indexing
					double finishedDeriv = weight * oldMap[kernalCount+paddingBias] * costDerivativeVector.at(kernalCount);
					//compare map = oldmap or inputs
					convDerivative[kernalCount] = convDerivative[kernalCount] + finishedDeriv;//atomciadd
					double weightUpdate = newMap[index] * derivativeSigmoid(oldMap[kernalCount]) * costDerivativeVector[kernalCount];
					
					myKernel->addToUpdates(weightUpdate, (kernalY * 3) + kernalX);
					
				}

			}
			
		}
		//paddingBias = paddingBias + 2;
	}
}


void convluation::copyPrevLayerData(double* inputMap, int x, int y)
{
	this->inputMap = new double[dimensionX * dimensionY];
	memcpy(this->inputMap, inputMap, sizeof(double) * (dimensionX * dimensionX));
	this->inputMap = inputMap;
	this->dimensionX = x;
	this->dimensionY = y; 
	newMap = new double[dimensionX * dimensionY];
	oldMap = new double[dimensionX * dimensionY];
	memcpy(newMap, inputMap, sizeof(double) * (dimensionX * dimensionY));


}

void convluation::setNewMapValue(int index, double value)
{
	newMap[index] = value;
}


void convluation::tempOutputNewMap()
{
	int size = (dimensionY * dimensionX);
	for (int i = 0; i < size; i++)
	{
		std::cout << "id : " << i << "value" << newMap[i] << std::endl;
		if (i % 5 == 0)
		{
			std::cout << "______" << std::endl;
		}
	}
}
void convluation::localBackProp(double* convDerivative,double* comparZLs)
{

	int paddingBias = (1 * dimensionX) + 1;
	int kernalCount = -1; 
	for (int y = 0; y < dimensionY - 2; y++)
	{

		for (int x = 0; x < dimensionX - 2; x++)
		{
			int i = (y * dimensionX) + x;
			kernalCount = kernalCount + 1;
			double biasUpdate = 1 * derivativeSigmoid(comparZLs[kernalCount + paddingBias]) * convDerivative[kernalCount];
			myKernel->addToBias(biasUpdate);
			for (int kernalY = 0; kernalY < 3; kernalY++)
			{
				for (int kernalX = 0; kernalX < 3; kernalX++)
				{
					double toAdd;
					int multiplier = (dimensionY * kernalY);
					int index = i + kernalX;
					index = index + multiplier;
					double weight = myKernel->getWeightAtIndex((kernalY * 3) + kernalX);
					//for FF TO CONV use kernal count as for deriv indexing
					double finishedDeriv = weight* comparZLs[kernalCount]*convDerivative[kernalCount];
					//compare map = oldmap or inputs
					convDerivative[kernalCount] = convDerivative[kernalCount] + finishedDeriv;//atomciadd
					double weightUpdate = newMap[index] * derivativeSigmoid(comparZLs[kernalCount+paddingBias]) * convDerivative[kernalCount];
				
					myKernel->addToUpdates(weightUpdate, (kernalY * 3) + kernalX);
				

				}

			}
		
		}
	}
}
