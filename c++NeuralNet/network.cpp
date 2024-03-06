#include "network.h"

network::network()
{
    //cutting out for ease of testing
    /*
    std::cout << "how many neurons will be in the input layer" << std::endl;
    std::cin >> inputNeurons;
    std::cout << "how many neurons will be in the hidden layers" << std::endl;
    std::cin >> hiddenNeurons;
    std::cout << "how many neurons will be in the output layer" << std::endl;
    std::cin >> outputNeurons;
    std::cout << "how many hidden layers will be in the network" << std::endl;
    std::cin >> hiddenLayers;
    */
    inputNeurons = 5;
    hiddenNeurons = 8;
    hiddenLayers = 3;
    outputNeurons = 5;
    totalLayers = hiddenLayers + 2;
 
    networkStructure = new node**[totalLayers];

}

double network::sigmoid(double x)
{
    double result;
    result = 1 / (1 + exp(-x));
    return result;
}

void network::populateNetworkStruct() //big function so might try and condense it down into sub funcs 
{
    int layers = 1;
    int nextLayerNeurons = hiddenNeurons;
    double weight = 0;
    node** nodeList = new node*[inputNeurons];
    for (int nodeId = 0; nodeId < inputNeurons; nodeId++)
    {
        node* inputNode = new node();

        for (int nodeWeightId = 0; nodeWeightId < nextLayerNeurons; nodeWeightId++)
        {
        
            weight = (double)rand() / RAND_MAX;
            inputNode->updateWeights(weight);
        }
        nodeList[nodeId] = inputNode;
    }
    networkStructure[0] = nodeList;
    
    for (layers = 1; layers < hiddenLayers+1; layers++)
    {
        nodeList = new node*[hiddenLayers];
        if (layers == hiddenLayers)
        {
            nextLayerNeurons = outputNeurons;
        }
        for (int nodeId = 0; nodeId < hiddenNeurons; nodeId++)
        {
            node* hiddenNode = new node(); 
            hiddenNode->setBias((double)rand() / RAND_MAX);
    
            for (int nodeWeightId = 0; nodeWeightId < nextLayerNeurons; nodeWeightId++)
            {
           
                weight = (double)rand() / RAND_MAX;
                hiddenNode->updateWeights(weight);
            }
            nodeList[nodeId] = hiddenNode;
        }
        networkStructure[layers] = nodeList;
    }
    nodeList = new node *[outputNeurons];
    for (int nodeId = 0; nodeId < outputNeurons; nodeId++)
    {
        node* outputNode = new node();
        
        nodeList[nodeId] = outputNode;

        
    }
    networkStructure[layers+1] = nodeList;
    
    
    
}

void network::displayNetwork()
{
    for (int i = 0; i < inputNeurons; i++)
    {
        networkStructure[0][i]->displayWeights();
    }
}

void network::forwardPropagate()
{

    int neuronCount = 0;
    double rawForwardPassSum = 0;
    double SigmoidedSum = 0; 
    int nextLayerNeuronCount = 0;
    for (int layers = 0; layers < totalLayers-1; layers++)
    {
        if (layers == 0)
        {
            neuronCount = inputNeurons;
            nextLayerNeuronCount = hiddenNeurons;
        }
        else if (layers == totalLayers-2)//think ive fixed this! 
        {
            neuronCount = outputNeurons;
            nextLayerNeuronCount = hiddenNeurons;
        }
        else
        {
            neuronCount = hiddenNeurons;
            nextLayerNeuronCount = outputNeurons;
        }
        
        for (int layerTwoNodeId = 0; layerTwoNodeId < nextLayerNeuronCount; layerTwoNodeId++)
        {
            for (int nodeId = 0; nodeId < neuronCount; nodeId++)
            {
                node* neuron = networkStructure[layers][nodeId];
                
                rawForwardPassSum = neuron->getWeight(layerTwoNodeId) + neuron->getActivation();
            }
            node* nextNeuron = networkStructure[layers + 1][layerTwoNodeId];
            rawForwardPassSum = rawForwardPassSum + nextNeuron->getBias();
            
            if (layers < 3)
            {
                networkStructure[layers + 1][layerTwoNodeId]->setActivation(sigmoid(rawForwardPassSum));
                networkStructure[layers + 1][layerTwoNodeId]->setRawForwardSum(rawForwardPassSum);
            }
            else
            {
                networkStructure[layers + 1][layerTwoNodeId]->setActivation(rawForwardPassSum);
                networkStructure[layers + 1][layerTwoNodeId]->setRawForwardSum(rawForwardPassSum);
            }
        }
   
    }
}

void network::backPropOutput(double desiredOutput)
{
    // need zl for each neuron
    double* weightUpdates = new double[outputNeurons];
    int neuronCount = hiddenNeurons;
    int NextLayerNeuronCount = outputNeurons;
    double derivativeCostInstance;
    node* neuron;
   
    node* nextNeuron;
        
    for (int nodeID = 0; nodeID < neuronCount; nodeID++)
    {
        weightUpdates = new double[outputNeurons];
        neuron = networkStructure[totalLayers-2][nodeID];
        
        for (int weightID = 0; weightID < NextLayerNeuronCount; weightID++)
        {
            nextNeuron = networkStructure[totalLayers - 1][weightID];
            derivativeCostInstance = derivativecost(nextNeuron->getActivation(), desiredOutput); //(-- this also needs fixing 
            addToDerivativeCosts(derivativeCostInstance);
            weightUpdates[weightID] = neuron->getActivation() * derivativeSigmoid(nextNeuron->getRawForwardSum()) * derivativeCostInstance;
                   
        }
        double current_bias = neuron->getBias();
        double bias_change = 1 * derivativeSigmoid(neuron->getRawForwardSum()) * derivativeCostInstance;
        neuron->addToUpdateBiases(bias_change);
        //nextNeuron->setBias(1* derivativeSigmoid(nextNeuron->getRawForwardSum()) * derivativeCostInstance)
        //neuron->addToWeightUpdates(weightUpdates);
        
            
                
    }
    

    
}


void network::clearDerivativeCosts()
{
    costDerivativeVector.clear(); 
}

void network::addToDerivativeCosts(double derivativeCostInstance)
{
    costDerivativeVector.push_back(derivativeCostInstance);
}

void network::fullBackPropogation(double desiredOutput)
{
    double nextLayerCount = hiddenNeurons;
    double neuronCount = hiddenNeurons;
    double* weightUpdates = new double[outputNeurons];
    std::vector<double> newDCosts;
    node* neuron;
    double newDeriv;
    backPropOutput(desiredOutput);
    for (int layer = hiddenLayers - 1; layer > 0; layer--)
    {

          
            for (int nodeID = 0; nodeID < neuronCount; nodeID++)
            {

                neuron = networkStructure[layer][nodeID];
                weightUpdates = new double[nextLayerCount];
                for (int weightID = 0; weightID < nextLayerCount; weightID++)
                {
                    newDeriv = calcBackDerivToCost(layer, weightID, neuron);
                    newDCosts.push_back(newDeriv);
               
                    node* nextNeuron = networkStructure[layer + 1][weightID];
                    weightUpdates[weightID] = neuron->getActivation() * derivativeSigmoid(nextNeuron->getRawForwardSum()) * newDeriv;
                    


                
                }

                neuron->addToWeightUpdates(weightUpdates);
               
            }
            double current_bias = neuron->getBias();
            double bias_change = 1 * derivativeSigmoid(neuron->getRawForwardSum()) * newDeriv;
            neuron->addToUpdateBiases(bias_change);
            
        
        costDerivativeVector = newDCosts;

        
    }

}


double network::derivativeSigmoid(double x)
{
    return(1 - sigmoid(x));

}

double network::derivativecost(double activation, double desiredOutcome)
{
    return(2 * (activation - desiredOutcome));
}

double network::calcBackDerivToCost(int layer,int nextLayerCount,node* neuron)
{
    double sumCost;

    
    for (int weightID = 0; weightID < nextLayerCount; weightID++)
    {
        node* nextNeuron = networkStructure[layer + 1][weightID];

        sumCost = sumCost + neuron->getWeight(weightID) * derivativeSigmoid(nextNeuron->getRawForwardSum()) * costDerivativeVector.at(weightID);
    }
    
}

double network::updateAllWeights()
{
    
}


