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
    double* biases; 

    node*** networkStructure;
public:

    network();

    double sigmoid(double x);//function taken from https://hackaday.io/page/5331-sigmoid-function

    void populateNetworkStruct();
    
    void displayNetwork();


      

   


};

