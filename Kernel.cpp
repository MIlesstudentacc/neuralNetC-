#include "Kernel.h"
#include <stdlib.h>
#include <iostream>

void Kernel::setWeightsSize(int size)
{
    weights = new double[size]; 
    weightUpdates = new double[size];
    this->weightSize = size; 
    std::fill_n(weightUpdates, size, 0);
    
}

double Kernel::calcOneWeightSum(int weightID, double activation)
{
    return weights[weightID]*activation;
}

void Kernel::generateRandomWeights()
{
    for (int i = 0; i < weightSize; i++)
    {
        double weight = (double)rand() / RAND_MAX;
        int flip = rand() % 2;
        if (flip)
        {
            weight = weight * -1;
        }
        weights[i] = weight;
    }
}

double Kernel::generateBias()
{
    double bias = (double)rand() / RAND_MAX;
    int flip = rand() % 2;
    if (flip)
    {
        bias = bias * -1;
    }
    return bias;
}

void Kernel::setBias(double newBias)
{
    this->bias = newBias;
}

void Kernel::addToUpdates(double weightUpdate,int weightID)
{
    weightUpdates[weightID] = weightUpdates[weightID] + weightUpdate;

}

void Kernel::updateWeights(int avgFactor,double LEARNING_RATES)
{
    for (int i = 0; i < weightSize; i++)
    {
        double update = weightUpdates[i];
        weightUpdates[i] = LEARNING_RATES * (weightUpdates[i] / avgFactor);
        double newUpdate = weightUpdates[i];
        weightUpdates[i] = 0;
    }
    
}

void Kernel::addToBias(double biasValue)
{
    biasUpdate = biasUpdate + biasValue;
}

double Kernel::getWeightAtIndex(int weightID)
{
    std::cout << "error happens here" << std::endl;
    std::cout << weightID << std::endl;
    return weights[weightID];
}

void Kernel::updateBias(int avgFactor, double LEARNING_RATES)
{
    bias = bias + LEARNING_RATES * (biasUpdate / avgFactor);
    biasUpdate = 0;
    
}
