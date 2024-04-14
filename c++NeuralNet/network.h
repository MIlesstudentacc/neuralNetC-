#pragma once
#include <math.h>
#include <iostream>
#include "node.h"
#include "C:\Users\Miles\source\repos\neuralNetC-4\convluation.h"
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
    convluation** convulationLayers;
    int convulationSize;
    double* convulationDerivatives;

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
    
    double calcBackBiasDeriv(int layer,int nextLayerCount);

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

    void setDesiredDataSetInputs(double petalWidth, double petalLength, double sepalLength, double sepalWidth);

    bool CheckAccuracy(int classNumber); 

    double sqaureRootCost(double activation, double DesiredActivation); 

    void setConvulationSize(int size); 

    void passConvForward(int layer);
    
    convluation* getConvulationLayer(int layer);

    void populateConvulationLayers(int dimensionX,int dimensionY); 
    
    void performConvulation(int layer);

    void performAllConvulation(double* input); 

    std::vector<double> getCostDerivativeVector();

    void backPropConvulation();
   
    void activateAllInLayer(convluation* layer);

    network(int inputNeurons,int* hiddenLayers,int outputNeurons,int hiddenLayerCount);

    void setAllInputs(double* doubleInputs);

    double* inputOnLastConv();

    void backPropConvNets();

    void calcBackDerivOnInput();

    void updateConvNets(); 
};


