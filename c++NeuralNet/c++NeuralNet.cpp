// c++NeuralNet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "network.h"
#include "fileReader.h"
#include "C:\Users\Miles\source\repos\neuralNetC-4\convluation.h"
#include "C:\Users\Miles\source\repos\neuralNetC-4\MNIST.h"
#include "C:\Users\Miles\source\repos\neuralNetC-4\MNISTreader.h"

int main()
{
    srand(time(0));
    
   
    int hiddenLayer[3] = { 50,50,50 };
   
    network* myNetwork = new network(784,hiddenLayer,10,3);
    myNetwork->setConvulationSize(2);
    myNetwork->populateConvulationLayers(28,28);
  
    MNIST* normSample= new MNIST();
    MNIST* exactCopy ; 
    MNISTreader* myMNISTReader = new MNISTreader();

    myMNISTReader->populateStorageTemplate();

    myMNISTReader->readFile("do nought");
    myMNISTReader->normliseAll();
    myNetwork->populateNetworkStructFixed();

    
    myMNISTReader->generateSampleSet();
    for (int sampleSetID = 0; sampleSetID < 5000; sampleSetID++)
    {
        exactCopy = myMNISTReader->takeSampleFromSet(3);
        normSample->copyData(exactCopy->getInput(), exactCopy->getClass());
        myNetwork->performAllConvulation(normSample->getInput());
        myNetwork->setDesiredOutcomes(normSample->getClass());
        double* feedNetworkInput = myNetwork->inputOnLastConv();

        myNetwork->inputOnLastConv();

        //pass
        myNetwork->forwardPropagateFixed();
        myNetwork->calcBackPropagationFixed();
        myNetwork->calcBackDerivOnInput();
        myNetwork->backPropConvNets();


        myNetwork->updateAllWeights();
        myNetwork->updateAllBiases();
        myNetwork->updateConvNets();
    }
    
   
       
   

    
   

}
