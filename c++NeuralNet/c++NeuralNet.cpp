// c++NeuralNet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "network.h"
int main()
{
    srand(time(0));
    network* myNetwork = new network(); 
    myNetwork->populateNetworkStruct();
    myNetwork->displayNetwork();



}
