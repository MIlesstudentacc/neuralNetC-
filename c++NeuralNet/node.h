#pragma once
#include <vector>
class node
{
private:
	double bias; 
	std::vector<double> weights;
	std::vector<std::vector<double>> weightUpdates; 
	double* gradient;
	double activation = 0;
	double rawForwardSum; 
	std::vector<double> biasUpdates; 
	std::vector<double> localWeightUpdates;

public:
	
	void updateWeights(double weight);

	

	void displayWeights();

	void setActivation(double newActivation); 

	double getActivation(); 

	double getWeight(int weightID);

	void setRawForwardSum(double rawForwardSum);

	double getRawForwardSum();



	void setBias(double newBias);

	double getBias();

	void addToUpdateBiases(double newUpdate);

	void updateThisNeuronsWeights(double LEARNING_RATE);

	void updateThisNeuronsBias(double LEARNING_RATE); 

	void pushToLocalUpdates(double newWeight);

	void pushToMainUpdates();

};

