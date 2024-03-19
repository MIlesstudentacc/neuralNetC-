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
    std::vector<int> neuronCounts;
    int hiddenLayers = 0;
    int totalLayers = 0; 
    double* biases; 
    std::vector<double> costDerivativeVector;
    const double LEARNING_RATE = 0.001;
    std::vector<double> desiredOutcome;

 

    bool classification = true; 
    node*** networkStructure;
    double sigmoid(double x);//function taken from https://hackaday.io/page/5331-sigmoid-function

    double derivativeSigmoid(double x);

    double derivativecost(double activation, double desiredOutcome);

    double softMaxSingle(double allExp,int numeriator);

    double allExpOutput(); 
public:

    network();
    
    void displayAllNetworkParameters();


    void forwardPropagateFixed();

    void clearDerivativeCosts();

    void addToDerivativeCosts(double derivativeCostInstance); 
    
    double calcBackDerivToCost(int layer, int nextLayerCount, node* neuron);

    void updateAllWeights();

    void updateAllBiases(); 

    void populateNetworkStructFixed();

    node* generateWeights(node* nodeToPopulate,int layer);
    
    void calculateNextNeuronActivation(int neuronCount,int layerTwoNodeId,int layer); 

    void displayNetworkBias();

    void displayNetworkActivation(); 

    void displayNetworkWeights(); 

    void calcBackPropagationFixed();

    void populateDefaultCosts();

    std::vector<double> backPropOneLayer(int layers, int neuronCounts, int nextNeuronCount,std::vector<double> newDerivs);

    void getDesiredOutcomes(); 

    void setTestInputs();
   
    void setDesiredOutcomes(int classPos); 
};

