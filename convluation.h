#pragma once
#include "Kernel.h"
#include "vector"
#include "C:\Users\Miles\source\repos\neuralNetC-4\c++neuralnet\node.h"
class convluation
{
private:

	int dimensionX = 0; 
	int dimensionY = 0; 
	Kernel* myKernel;
	double* inputMap; 
	double* oldMap;
	double* newMap;
	
	double* compareMap;
	double LEARNING_RATE = 0.001;
public:
	void setDimensions(int x, int y);

	void setInputMap();

	void setKernel(Kernel* myKernal); 

	void populateInputMap(double* inputs);

	void sendToOld();

	void outputMap(); 

	void tempOutputNewMap();

	void restoreMap();

	void fixKernelUpdate();

	void setInputMap(double* inputMap);

	double* getNewMap();

	void copyPrevLayerData(double* inputMap, int x, int y);
	
	int getDimensionX();

	int getDimensionY();

	void setCompareMap(double* toCompare); 

	void localBackProp(double* convDerivative,double* compareMap);

	void setInputMapValue(int index, double value);

	void setNewMapValue(int index, double value);

	double GetValueAtIndex(int index);

	void updateAttachedKernel();

	double sigmoid(double x);//function taken from https://hackaday.io/page/5331-sigmoid-function

	double derivativeSigmoid(double x);

	void setLearningRate(double newLearningRate); 

	void localBackPropToFF(double* convDerivative,std::vector<double> costDerivativeVector, node*** FFInpLayer);

	double* getOldMap();

};

