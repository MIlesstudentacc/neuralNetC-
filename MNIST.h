#pragma once
class MNIST
{
private:
	double* input = new double[784];

	int Class; 
public:

	MNIST();

	MNIST(double* pixelInputs,int Class);

	

	double* getInput();

	int getClass(); 

	void setInputIndexValue(int index, double value); 

	void allInputZero(); 

	double getValueAtIndex(int index);

	void copyData(double* input, int Class);

	void displayPixels();
};

