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
    int layerCount = hiddenLayers + 2;
    biases = new double(layerCount-1); 
    networkStructure = new node**[layerCount];

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
        inputNode->setWeightsSize(nextLayerNeurons);
        for (int nodeWeightId = 0; nodeWeightId < nextLayerNeurons; nodeWeightId++)
        {
        
            weight = (double)rand() / RAND_MAX;
            inputNode->updateWeights(weight, nodeWeightId);
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
            hiddenNode->setWeightsSize(nextLayerNeurons);
            for (int nodeWeightId = 0; nodeWeightId < nextLayerNeurons; nodeWeightId++)
            {
           
                weight = (double)rand() / RAND_MAX;
                hiddenNode->updateWeights(weight, nodeWeightId);
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
