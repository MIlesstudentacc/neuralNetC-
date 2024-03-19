#include "network.h"

network::network()
{
    //cutting out for ease of testing
    
    std::cout << "how many neurons will be in the input layer" << std::endl;
    std::cin >> inputNeurons;
    neuronCounts.push_back(inputNeurons);
    std::cout << "how many layers will be hidden layers" << std::endl;
    std::cin >> hiddenLayers;
    for (int i = 0; i < hiddenLayers; i++)
    {
        std::cout << "how many neurons will be in the hidden layers" << std::endl;
        std::cin >> hiddenNeurons;
        neuronCounts.push_back(hiddenNeurons);
    }
    std::cout << "how many neurons will be in the output layer" << std::endl;
    std::cin >> outputNeurons;
    neuronCounts.push_back(outputNeurons);
 
    /*
    inputNeurons = 5;
    hiddenNeurons = 8;
    hiddenLayers = 3;
    outputNeurons = 5;*/
    totalLayers = hiddenLayers + 2;


 
    networkStructure = new node**[totalLayers];

}

double network::sigmoid(double x)
{
    double result;
    result = 1 / (1 + exp(-x));
    return result;
}
double network::allExpOutput()
{
    double expOutput = 0;
    for (int outputs = 0; neuronCounts[totalLayers - 1]; outputs++)
    {
        double activation = networkStructure[totalLayers - 1][outputs]->getActivation();
        expOutput = expOutput + exp(activation);
    }
    return expOutput; 
}
double network::softMaxSingle(double allExp,int numeriator)
{
    return exp(networkStructure[totalLayers - 1][numeriator]->getActivation())/allExp;
}

void network::populateNetworkStructFixed()
{
    for (int layers = 0; layers < totalLayers; layers++)
    {
        int currentLayerCount = neuronCounts[layers];
        node** nodeList = new node*[inputNeurons]; 
     
        for (int nodeID = 0; nodeID < currentLayerCount; nodeID++)
        {
            node* toAdd = new node(); 
            toAdd = generateWeights(toAdd, layers);
            nodeList[nodeID] = toAdd;
        }

        networkStructure[layers] = nodeList; 
    }
}

node* network::generateWeights(node* nodeToPopulate,int layers)
{
    if (layers < totalLayers - 1)
    {
        int weightCount = neuronCounts[layers + 1];
        for (int nodeWeightID = 0; nodeWeightID < weightCount; nodeWeightID++)
        {

            double weight = (double)rand() / RAND_MAX;
            nodeToPopulate->updateWeights(weight);
        }
    }
        if (layers > 1)
        {
            nodeToPopulate->setBias((double)rand() / RAND_MAX);
        }
    
    return nodeToPopulate;
}

void network::calculateNextNeuronActivation(int neuronCount, int layerTwoNodeId,int layers)
{
    double rawForwardPassSum = 0;
    for (int nodeID = 0; nodeID < neuronCount; nodeID++)
    {
        node* neuron = networkStructure[layers][nodeID];
        rawForwardPassSum = rawForwardPassSum + neuron->getWeight(layerTwoNodeId) * neuron->getActivation();
    }
    node* nextNeuron = networkStructure[layers + 1][layerTwoNodeId];
    rawForwardPassSum = rawForwardPassSum + nextNeuron->getBias();
    nextNeuron->setRawForwardSum(rawForwardPassSum);
    if (layers < totalLayers - 2)
    {
        networkStructure[layers + 1][layerTwoNodeId]->setActivation(sigmoid(rawForwardPassSum));
    }
    else
    {
        networkStructure[layers + 1][layerTwoNodeId]->setActivation(rawForwardPassSum);
    }
}

void network::displayNetworkBias()
{
    for (int layers = 0; layers < neuronCounts.size(); layers++)
    {
        int count = neuronCounts[layers];
        std::cout << "___________________________" << std::endl;
        for (int countID = 0; countID < count; countID++)
        {
            std::cout << networkStructure[layers][countID]->getBias() << std::endl;
        }

    }
}

void network::displayNetworkActivation()
{
    for (int layers = 0; layers < neuronCounts.size(); layers++)
    {
        int count = neuronCounts[layers];
        std::cout << "___________________________" << std::endl;
        for (int countID = 0; countID < count; countID++)
        {
            std::cout << networkStructure[layers][countID]->getActivation() << std::endl;
        }

    }
}

void network::displayNetworkWeights()
{
    for (int layers = 0; layers < neuronCounts.size()-1; layers++)
    {
        int count = neuronCounts[layers];
        std::cout << "___________________________" << std::endl;
        for (int countID = 0; countID < count; countID++)
        {
            std::cout << "neuron" << countID << "weights" << std::endl;
            for (int weightID = 0; weightID < neuronCounts[layers + 1]; weightID++)
            {
                std::cout << networkStructure[layers][countID]->getWeight(weightID) << std::endl;
            }
        }
    }
}




void network::displayAllNetworkParameters()
{
    std::cout << "displaying bias" << std::endl; 
    std::cout << "_______________________________" << std::endl; 
    displayNetworkBias();
    std::cout << "displaying activation" << std::endl;
    std::cout << "_______________________________" << std::endl;
    displayNetworkActivation(); 
    std::cout << "displaying weights" << std::endl;
    std::cout << "_______________________________" << std::endl;
    displayNetworkWeights();
  
}

void network::forwardPropagateFixed()
{
    for (int layers = 0; layers < totalLayers - 1; layers++)
    {
        int neuronCount = neuronCounts[layers];
        int nextNeuronCount = neuronCounts[layers + 1];
        for (int layerTwoNodeId = 0; layerTwoNodeId < nextNeuronCount; layerTwoNodeId++)
        {
            calculateNextNeuronActivation(neuronCount, layerTwoNodeId, layers);
        }
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

void network::populateDefaultCosts()
{
    double derivCost;
    for (int nodeID=0; nodeID < neuronCounts[totalLayers - 1]; nodeID++)
    {
        node* neuron = networkStructure[totalLayers-1][nodeID];
        if (classification == true)
        {
            double allExp = allExpOutput();
            derivCost = derivativecost(softMaxSingle(allExp, neuron->getActivation()), desiredOutcome[nodeID]);
        }
        derivCost = derivativecost(neuron->getActivation(), desiredOutcome[nodeID]);
        costDerivativeVector.push_back(derivCost);
    }
}

void network::getDesiredOutcomes()
{
    desiredOutcome.clear(); 
    for (int outcomes = 0; outcomes < neuronCounts[totalLayers - 1]; outcomes++)
    {
        double singleDesireOutcome = 0;
        std::cout << "what desired outcome do you want for neuron " << outcomes<< std::endl;
        std::cin >> singleDesireOutcome;
        desiredOutcome.push_back(singleDesireOutcome);

    }
}



void network::calcBackPropagationFixed()
{
    populateDefaultCosts();
    std::vector<double> newDCosts;
    int nextNeuronCount = 0;
    int neuronCount = 0;
    for(int layers = totalLayers - 1; layers > 0; layers--)
    {
        nextNeuronCount = neuronCounts[layers];
        neuronCount = neuronCounts[layers - 1];
        newDCosts = backPropOneLayer(layers, neuronCount, nextNeuronCount, newDCosts);
        if (newDCosts.size() > 0)
        {
            costDerivativeVector = newDCosts;
        }
        newDCosts.clear();
    }
    for (int inputNeurons = 0; inputNeurons < neuronCount; inputNeurons++)
    {
       networkStructure[0][inputNeurons]->pushToMainUpdates();

    }

}

void network::setTestInputs()
{
    double start = 10;
    for (int inputs = 0; inputs < neuronCounts[0]; inputs++)
    {
        networkStructure[0][inputs]->setActivation(start);
        start = start + 10;
    }
}
std::vector<double> network::backPropOneLayer(int layers, int neuronCount, int nextNeuronCount,std::vector<double> newDCosts)
{
    double* weightUpdates = new double[nextNeuronCount];
   
    double newDeriv = 0;
    for (int weightID = 0; weightID < nextNeuronCount; weightID++)
    {
        node* nextNeuron = networkStructure[layers][weightID];
        if (layers < totalLayers - 1)
        {
            newDeriv = calcBackDerivToCost(layers, neuronCounts[layers + 1], nextNeuron);
            newDCosts.push_back(newDeriv);
        }
        else
        {
            newDeriv = costDerivativeVector.at(weightID);
        }

        for (int nodeID = 0; nodeID < neuronCount; nodeID++)
        {
            node* neuron = networkStructure[layers - 1][nodeID];
            double weightAdd = neuron->getActivation() * derivativeSigmoid(nextNeuron->getRawForwardSum()) * newDeriv;
            neuron->pushToLocalUpdates(weightAdd);
           
            networkStructure[layers - 1][nodeID] = neuron;

        } 
        if (layers > 2)
        {
            double newBias = 1 * derivativeSigmoid(nextNeuron->getRawForwardSum()) * newDeriv;
            nextNeuron->addToUpdateBiases(newBias);
        }
        if (layers < totalLayers - 1)
        {
            nextNeuron->pushToMainUpdates();
            networkStructure[layers][weightID] = nextNeuron;
        }
    }
    
    return newDCosts;
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
    double sumCost =0;

    
    for (int weightID = 0; weightID < nextLayerCount; weightID++)
    {
        node* nextNeuron = networkStructure[layer + 1][weightID];

        sumCost = sumCost + neuron->getWeight(weightID) * derivativeSigmoid(nextNeuron->getRawForwardSum()) * costDerivativeVector.at(weightID);
    }
    return sumCost;
}

void network::updateAllWeights()
{
    int neuronCount = 0; 
    for (int layers = 0; layers < totalLayers-1; layers++)
    {
        if (layers == 0)
        {
            neuronCount = inputNeurons;
        }
        if (layers == totalLayers - 2)
        {
            neuronCount = hiddenLayers;
        }
        for (int nodeID = 0; nodeID < neuronCount; nodeID++)
        {
            networkStructure[layers][nodeID]->updateThisNeuronsWeights(LEARNING_RATE);

        }
    }
}

void network::updateAllBiases()
{
    int neuronCount = 0;
    for (int layers = 1; layers < totalLayers - 1; layers++)
    {
        if (layers < totalLayers - 1)
        {
            neuronCount = hiddenLayers;
        }
        else
        {
            neuronCount = outputNeurons;
        }
        for (int nodeID = 0; nodeID < neuronCount; nodeID++)
        {
            networkStructure[layers][nodeID]->updateThisNeuronsBias(LEARNING_RATE);

        }
    }
}


