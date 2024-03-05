#pragma once
#include <math.h>
#include <iostream>
#include "node.h"

class network
{
private:
    int inputNeurons = 0;
    int outputNeurons = 0;
    int hiddenNeurons = 0;
    int hiddenLayers = 0;
    int totalLayers = 0; 
    double* biases; 
    std::vector<double> costDerivativeVector;

    node*** networkStructure;
    double sigmoid(double x);//function taken from https://hackaday.io/page/5331-sigmoid-function

    double derivativeSigmoid(double x);

    double derivativecost(double activation, double desiredOutcome);
public:

    network();

    void populateNetworkStruct();
    
    void displayNetwork();

    void forwardPropagate(); 

    void backPropOutput(double DesiredOutput);

    void biasInit();

    void clearDerivativeCosts();

    void addToDerivativeCosts(double derivativeCostInstance); 

    void fullBackPropogation(double DesiredOutput); 
    
    double calcBackDerivToCost(int layer, int costToBootstrap, int neuronCount);

      

   


};

