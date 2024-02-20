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

    node*** networkStructure;
    double sigmoid(double x);//function taken from https://hackaday.io/page/5331-sigmoid-function

    double derivativeSigmoid(double x);

    double cost(double activation, double desiredOutcome);
public:

    network();

    void populateNetworkStruct();
    
    void displayNetwork();

    void forwardPropagate(); 

   


      

   


};

