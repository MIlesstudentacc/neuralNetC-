#pragma once
#include <vector>
class node
{
private:
	double* weights;
	std::vector<double*> weightUpdates; 
	double* gradient;
	double activation = 0;
	double rawForwardSum; 
public:
	void updateWeights(double weight,int weightID);

	void setWeightsSize(int size);

	void displayWeights();

	void setActivation(double newActivation); 

	double getActivation(); 

	double getWeight(int weightID);

	void setRawForwardSum(double rawForwardSum);

	double getRawForwardSum();

	void addToWeightUpdates(double* weightUpdate);

};

