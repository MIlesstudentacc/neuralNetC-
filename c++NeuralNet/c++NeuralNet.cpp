// c++NeuralNet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "network.h"
#include "fileReader.h"


int main()
{
    srand(time(0));
    
    network* myNetwork = new network(); 
    /*
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
    int random = rand() % 10;
    myNetwork->populateNetworkStructFixed();
    myReader->readFile("does not matter");
    myReader->calcMeans();
    irisDataClass* sample = new irisDataClass();
    std::vector<int> classIDS = myReader->getClassID(); 
    for (int sampleSetID = 0; sampleSetID < 5000; sampleSetID++)
    {
        if (sampleSetID == 1)
        {
            myNetwork->displayNetworkActivation();
        }
        myReader->generateSampleSet();
        int iterations = myReader->getSampleSetSize();
        for (int sampleID = 0; sampleID < (iterations-1); sampleID++)
        {

            irisDataClass* refSample = myReader->takeSampleFromSet();
            sample->copyObjArg(refSample->getSepalLength(), refSample->getSepalWidth(),
                refSample->getPetalLength(), refSample->getPetalWidth());
            sample->setClass(refSample->getClass());
            //sample = myReader->standardDeviationOne(sample);
            sample = myReader->normalise(sample);
          
            //sample->displayAttributes(); 

            myNetwork->setDesiredOutcomes(myReader->getNumberFromClass(sample->getClass()));
            myNetwork->setDesiredDataSetInputs(sample->getPetalWidth(), sample->getPetalLength()
                , sample->getSepalLength(), sample->getSepalWidth());
            myNetwork->forwardPropagateFixed();
            myNetwork->calcBackPropagationFixed();
            
            /*(random == sampleID)
            {
                int random = rand() % 10;
                random = random + sampleID;
         

            }*/
            myNetwork->updateAllBiases();
            myNetwork->updateAllWeights();


        }
        
    }
    myReader->generateSampleSet();
    int iterations = myReader->getSampleSetSize();
    int trueGeuss = 0;
    for (int sampleID = 0; sampleID < (iterations-1); sampleID++)
    {
        
       
        irisDataClass* refSample = myReader->takeSampleFromSet();
        sample->copyObjArg(refSample->getSepalLength(), refSample->getSepalWidth(),
            refSample->getPetalLength(), refSample->getPetalWidth());
        sample->setClass(refSample->getClass());
        //sample = myReader->standardDeviationOne(sample);
        sample = myReader->normalise(sample);
        //sample = myReader->standardDeviationOne(sample);
        myNetwork->setDesiredOutcomes(myReader->getNumberFromClass(sample->getClass()));
        myNetwork->setDesiredDataSetInputs(sample->getPetalWidth(), sample->getPetalLength()
            , sample->getSepalLength(), sample->getSepalWidth());
        myNetwork->forwardPropagateFixed();
        int classNum = myReader->getNumberFromClass(sample->getClass());
        bool correct = myNetwork->CheckAccuracy(classNum-1);
        if (correct)
        {
            trueGeuss = trueGeuss++;
        }
        correct = false; 
    }

    
    //myNetwork->displayNetworkActivation();

    


}
