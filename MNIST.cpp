#include "MNIST.h"
#include <corecrt_malloc.h>
#include <vcruntime_string.h>
#include "algorithm"
#include <iostream>

MNIST::MNIST()
{

}

MNIST::MNIST(double* pixelInputs, int Class)
{
  
    memcpy(input, pixelInputs, sizeof(double) * 784);
    this->Class = Class;
}

double* MNIST::getInput()
{
    return input;
}

int MNIST::getClass()
{
    return Class;
}

void MNIST::setInputIndexValue(int index, double value)
{
    input[index] = value; 
}

void MNIST::allInputZero()
{
    std::fill(input, input + 748, 0);
}

double MNIST::getValueAtIndex(int index)
{
    return input[index];
}

void MNIST::copyData(double* input, int Class)
{
    this->input = input;
    this->Class = Class;
}

void MNIST::displayPixels()
{
    for (int i = 0; i < 748; i++)
    {
        std::cout << input[i] << std::endl;
    }
}
