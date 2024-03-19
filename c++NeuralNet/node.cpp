#include "node.h"
#include <iostream>

void node::updateWeights(double weight)
{
	weights.push_back(weight);
}



void node::displayWeights()
{
	for (int i = 0; i < 8; i++)//8 temporary for testing
	{
		std::cout << weights[i] << std::endl;
	}
}

void node::setActivation(double newActivation)
{
	activation = newActivation;
}

double node::getActivation()
{
	return activation; 
}

double node::getWeight(int weightID)
{
	return weights[weightID];
}

void node::setRawForwardSum(double rawForwardSum)
{
	this->rawForwardSum = rawForwardSum;
}

double node::getRawForwardSum()
{
	return rawForwardSum;
}


void node::setBias(double newBias)
{
	bias = newBias;
}

double node::getBias()
{
	return bias; 
}

void node::addToUpdateBiases(double newUpdate)
{
	biasUpdates.push_back(newUpdate);
}

void node::updateThisNeuronsWeights(double LEARNING_RATE)
{
	std::vector<double> newWeights;
	for (int weightID = 0; weightID < weights.size(); weightID++)
	{
		double avgUpdate = 0;
		for (int updateSet = 0; updateSet < weightUpdates.size(); updateSet++)
		{
			avgUpdate = avgUpdate + weightUpdates.at(updateSet).at(weightID);


		}
		avgUpdate = avgUpdate / weightUpdates.size();
		newWeights.push_back(weights.at(weightID) - (LEARNING_RATE * avgUpdate));
		
	}
	weights = newWeights; 
}

void node::updateThisNeuronsBias(double LEARNING_RATE)
{
	double newBias;
	double avgUpdate = 0; 
	for (int updateSet = 0; updateSet < biasUpdates.size(); updateSet++)
	{
		avgUpdate = avgUpdate + biasUpdates[updateSet];
	}
	newBias = bias - (LEARNING_RATE * avgUpdate); 
	
}

void node::pushToLocalUpdates(double newWeight)
{
	localWeightUpdates.push_back(newWeight);
}

void node::pushToMainUpdates()
{
	weightUpdates.push_back(localWeightUpdates);
	localWeightUpdates.clear(); 
}



