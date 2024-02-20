#include "node.h"

void node::updateWeights(double weight,int weightID)
{
	weights[weightID] == weight;
}

void node::setWeightsSize(int size)
{
	weights = new double[size];
}
