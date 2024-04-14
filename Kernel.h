#pragma once
class Kernel
{
private:

	double* weights;
	int weightSize;
	double bias;
	double* weightUpdates;
	double biasUpdate = 0;
public:
	void setWeightsSize(int size);

	double calcOneWeightSum(int weightID, double activation);

	void generateRandomWeights();

	double generateBias();
	
	void setBias(double newBias);

	void addToUpdates(double weightUpdate,int weightID);

	void updateWeights(int avgFactor,double LEARNING_RATES); 

	void addToBias(double biasValue);

	double getWeightAtIndex(int weightID); 

	void updateBias(int avgFactor,double LEARNING_RATES); 
	

};

