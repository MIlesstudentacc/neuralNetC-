#include "network.h"

network::network()
{
    std::cout << "how many neurons will be in the input layer" << std::endl;
    std::cin >> inputNeurons;
    std::cout << "how many neurons will be in the hidden layers" << std::endl;
    std::cin >> hiddenNeurons;
    std::cout << "how many neurons will be in the output layer" << std::endl;
    std::cin >> outputNeurons;
    std::cout << "how many hidden layers will be in the network" << std::endl;
    std::cin >> hiddenLayers;
    int layerCount = hiddenLayers + 2;
    biases = new double(layerCount-1); 

}

double network::sigmoid(double x)
{
    double result;
    result = 1 / (1 + exp(-x));
    return result;
}

void network::populateNetworkStruct()
{
    srand(time(0));

    for (int nodeId = 0; nodeId < inputNeurons; nodeId++)
    {
        node* inputNode= new node();
        inputNode->setWeightsSize(inputNeurons);
        for (int nodeWeightId = 0; nodeWeightId < inputNeurons; nodeWeightId++)
        {
            double weight = rand() / RAND_MAX;
            inputNode->updateWeights(weight,nodeWeightId);
        }
    }
    
    
}
