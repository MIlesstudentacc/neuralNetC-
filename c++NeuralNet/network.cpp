#include "network.h"

network::network()
{
    //cutting out for ease of testing
    /*
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
    */
    /*
    inputNeurons = 5;
    hiddenNeurons = 8;
    hiddenLayers = 3;
    outputNeurons = 5;*/
    //totalLayers = hiddenLayers + 2;


 
    //networkStructure = new node**[totalLayers];

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
    for (int outputs = 0; outputs < neuronCounts[totalLayers - 1]; outputs++)
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
        node** nodeList = new node*[currentLayerCount]; 
     
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
        double range = sqrt(weightCount);
        for (int nodeWeightID = 0; nodeWeightID < weightCount; nodeWeightID++)
        {

            double weight = (double)rand() / RAND_MAX;
       
            weight = std::fmod(weight,range);
            int flip = rand() % 2;
            if (flip)
            {
                weight = weight * -1;
            }
            nodeToPopulate->updateWeights(weight);
        }
    }
        if (layers > 0)
        {
            int biasCount = neuronCounts[layers];
            double range = sqrt(biasCount);
            double bias = (double)rand() / RAND_MAX;
            bias = std::fmod(bias, range);
            int flip = rand() % 2;
            if (flip)
            {
                bias = bias * -1;
            }


            nodeToPopulate->setBias(bias);
        }
    
    return nodeToPopulate;
}

void network::calculateNextNeuronActivation(int neuronCount, int layerTwoNodeId,int layers)
{
    double rawForwardPassSum = 0;
    for (int nodeID = 0; nodeID < neuronCount; nodeID++)
    {
        node* neuron = networkStructure[layers][nodeID];
        rawForwardPassSum = rawForwardPassSum + (neuron->getWeight(layerTwoNodeId) * neuron->getActivation());
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

double network::calcBackBiasDeriv(int layer, int nextLayerCount)
{
    double sumCost = 0;


    for (int weightID = 0; weightID < nextLayerCount; weightID++)
    {
        node* nextNeuron = networkStructure[layer + 1][weightID];
        double score = nextNeuron->getBias() * derivativeSigmoid(nextNeuron->getRawForwardSum()) * costDerivativeVector.at(weightID);
        sumCost = sumCost + score;
    }
    return sumCost;
}

void network::populateDefaultCosts()
{
    double derivCost;
    costDerivativeVector.clear();
    for (int nodeID=0; nodeID < neuronCounts[totalLayers - 1]; nodeID++)
    {
        node* neuron = networkStructure[totalLayers-1][nodeID];
        if (classification == true)
        {
            double allExp = allExpOutput();
            derivCost = derivativecost(softMaxSingle(allExp,nodeID), desiredOutcome[nodeID]);
        }
        else
        {
            derivCost = derivativecost(neuron->getActivation(), desiredOutcome[nodeID]);
        }
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
    
   
    double newDeriv = 0;
    for (int weightID = 0; weightID < nextNeuronCount; weightID++)
    {
        std::cout << weightID << std::endl;
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
            double weightAdd;
            if (layers < totalLayers - 1)
            {
                weightAdd = neuron->getActivation() * derivativeSigmoid(nextNeuron->getRawForwardSum()) * newDeriv;
            }
            else
            {
                weightAdd = neuron->getActivation() * nextNeuron->getRawForwardSum() * newDeriv;
            }
            neuron->pushToLocalUpdates(weightAdd);
           
            networkStructure[layers - 1][nodeID] = neuron;

        } 
        //here is where bias needs done
        if (layers > 0)
        {
            double newBias;
            if (layers < totalLayers - 1)
            {
                newBias = 1 * derivativeSigmoid(nextNeuron->getRawForwardSum()) * newDeriv;
            }
            else
            {
                newBias = 1 * nextNeuron->getRawForwardSum() * newDeriv;
            }
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
        double score = neuron->getWeight(weightID) * derivativeSigmoid(nextNeuron->getRawForwardSum()) * costDerivativeVector.at(weightID);
        sumCost = sumCost + score;
    }
    return sumCost;
}

void network::updateAllWeights()
{
    int neuronCount = 0; 
    for (int layers = 0; layers < totalLayers-1; layers++)
    {
        neuronCount = neuronCounts[layers];
        for (int nodeID = 0; nodeID < neuronCount; nodeID++)
        {
            networkStructure[layers][nodeID]->updateThisNeuronsWeights(LEARNING_RATE);

        }
    }
}

void network::updateAllBiases()
{
    int neuronCount = 0;
    for (int layers = 1; layers < totalLayers; layers++)
    {


        neuronCount = neuronCounts[layers];
        for (int nodeID = 0; nodeID < neuronCount; nodeID++)
        {
            networkStructure[layers][nodeID]->updateThisNeuronsBias(LEARNING_RATE);

        }
    }
}

void network::setDesiredOutcomes(int classPos) 
{
    desiredOutcome.clear();
    for (int output = 0; output < neuronCounts[totalLayers - 1]; output++)
    {
        desiredOutcome.push_back(0);
    }
    desiredOutcome.at(classPos) = 1; 
}
void network::setDesiredDataSetInputs(double petalWidth, double petalLength, double sepalLength, double sepalWidth)
{
    networkStructure[0][0]->setActivation(petalWidth);
    networkStructure[0][1]->setActivation(petalLength);
    networkStructure[0][2]->setActivation(sepalLength);
    networkStructure[0][3]->setActivation(sepalWidth);
   
}

bool network::CheckAccuracy(int classNumber)
{
    double max = 0;
    int maxID;
    for (int nodeID = 0; nodeID < neuronCounts[totalLayers - 1]; nodeID++)
    {
        double allExp = allExpOutput(); 
        double softmax = softMaxSingle(allExp, nodeID);
       
        if (softmax > max)
        {
            max = softmax;
            maxID = nodeID; 
        }
        
        
    }
    if (maxID == classNumber)
    {
        return true;
    }
    else
    {
        return false; 
    }
    
}

double network::sqaureRootCost(double activation, double DesiredActivation)
{
    return sqrt(pow(activation - DesiredActivation, 2));
}

void network::setConvulationSize(int size)
{
    convulationLayers = new convluation*[size];
    convulationSize = size;
}

void network::passConvForward(int layer)
{
    convluation* oldConv = convulationLayers[layer];
    convluation* newConv = convulationLayers[layer + 1];
    newConv->copyPrevLayerData(oldConv->getNewMap(), oldConv->getDimensionX(), 
        oldConv->getDimensionY());


}

convluation* network::getConvulationLayer(int layer)
{
    return convulationLayers[layer];
}

void network::performConvulation(int layer)
{
    convluation* targetConv = convulationLayers[layer];
    std::cout << "kernel update has just been performed" << std::endl;
    targetConv->fixKernelUpdate();
    targetConv->tempOutputNewMap();
    targetConv->sendToOld();
    activateAllInLayer(targetConv);
    std::cout << "map has just been activated" << std::endl;
    targetConv->tempOutputNewMap();

}

std::vector<double> network::getCostDerivativeVector()
{
    return costDerivativeVector;
}


void network::setAllInputs(double* inputs)
{
    for (int i = 0; i < inputNeurons; i++)
    {
      
            networkStructure[0][i]->setActivation(inputs[i]);
        
    }
}

double* network::inputOnLastConv()
{
    convluation* layer = convulationLayers[convulationSize-1];
    double* inputs = new double[inputNeurons];
    int yValue = 0;
    for (int x = 1; x < layer->getDimensionX()-1; x++)
    {
        yValue = 1 * layer->getDimensionX() + 1;
        for (int y = 0; y < layer->getDimensionY()- 2; y++)
        {
            int index = yValue + x;
            inputs[y * (layer->getDimensionX() - 2)] = layer->GetValueAtIndex(index);
            yValue = yValue + layer->getDimensionX() + 1;

        }
    }
    return inputs;
}

void network::backPropConvNets()
{
    convluation* layerLast = convulationLayers[convulationSize-1]; 
    node*** inpLayer = networkStructure;
    layerLast->localBackPropToFF(convulationDerivatives, costDerivativeVector, inpLayer);
    for (int i = convulationSize - 2; i >= 0; i--)
    {
        convluation* layer = convulationLayers[i];
        
        layer->localBackProp(convulationDerivatives,layerLast->getOldMap());
        layerLast = layer;
    }
}

void network::calcBackDerivOnInput()
{
    std::vector<double> newD;
    for (int i = 0; i < neuronCounts[0]; i++)
    {
        node* myNode = networkStructure[0][i];
        double newDeriv = calcBackDerivToCost(0, neuronCounts[1], myNode);
        newD.push_back(newDeriv);
    }
    costDerivativeVector = newD;
}

void network::updateConvNets()
{
    for (int i = 0; i < convulationSize; i++)
    {
        convluation* layer = convulationLayers[i];
        layer->updateAttachedKernel();
    }
}


network::network(int inputNeurons, int* hiddenLayers,int outputNeurons,int hiddenLayerCount)
{
    this->inputNeurons = inputNeurons;
    neuronCounts.push_back(inputNeurons);
    for (int i = 0; i < hiddenLayerCount; i++)
    {
      
        neuronCounts.push_back(hiddenLayers[i]);
    }
    neuronCounts.push_back(outputNeurons);
    totalLayers = hiddenLayerCount + 2;
    networkStructure = new node **[totalLayers];

}




void network::activateAllInLayer(convluation* layer)
{
    int yValue = 0;
    for (int x = 1; x < layer->getDimensionX()-1; x++)
    {
        yValue = 1 * layer->getDimensionX();
        for (int y = 1; y < layer->getDimensionY()-1; y++)
        {
            int index = yValue + x;
            if (layer->GetValueAtIndex(index) != 0)
            {
                layer->setNewMapValue(index, sigmoid(layer->GetValueAtIndex(index)));
            }
            yValue = yValue + layer->getDimensionX();
        }
    }
}

void network::performAllConvulation(double* input)
{
    int i = 0;
    for (i = 0; i < convulationSize-1; i++)
    {
        convluation* convLayer = convulationLayers[i];
        if (i == 0)
        {
            
            convLayer->populateInputMap(input);
            std::cout << "output shnuffed up" << std::endl;
            convLayer->outputMap();

        }
        performConvulation(i);
        
        passConvForward(i);
    }
    performConvulation(i);
    

}

void network::populateConvulationLayers(int dimensionX,int dimensionY)
{
    convulationDerivatives = new double[dimensionX*dimensionY];
    std::fill_n(convulationDerivatives, dimensionX*dimensionY, 0);

    for (int i = 0; i < convulationSize; i++)
    {
        convluation* newLayer = new convluation(); 
        
        Kernel* myKernel = new Kernel();

        newLayer->setDimensions(dimensionX, dimensionY);
       
       
        if (i == 0)
        {
            newLayer->setInputMap();
        }
        myKernel->setWeightsSize(9);
        myKernel->generateRandomWeights();
        myKernel->setBias(myKernel->generateBias());
        newLayer->setKernel(myKernel);
        convulationLayers[i] = newLayer;
    }

}



