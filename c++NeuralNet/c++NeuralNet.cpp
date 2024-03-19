// c++NeuralNet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "network.h"
#include "fileReader.h";

int main()
{
    srand(time(0));
    /*
    network* myNetwork = new network(); 
    
    myNetwork->populateNetworkStructFixed();
    myNetwork->setTestInputs(); 
    myNetwork->forwardPropagateFixed();
    myNetwork->displayNetworkBias();
    myNetwork->displayNetworkActivation();
    //myNetwork->getDesiredOutcomes();
    
    myNetwork->calcBackPropagationFixed();
    myNetwork->updateAllBiases();
    myNetwork->updateAllWeights();

    myNetwork->forwardPropagateFixed();
    std::cout << "____________--NEW ACTIVATIONS____________" << std::endl;
    myNetwork->displayNetworkActivation();
    */
    
    fileReader* myReader = new fileReader();

    myReader->readFile("does not matter");


}
