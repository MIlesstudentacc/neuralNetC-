#include "node.h"
#include <iostream>

void node::updateWeights(double weight,int weightID)
{
	weights[weightID] = weight;
}

void node::setWeightsSize(int size)
{
	weights = new double[size];
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

