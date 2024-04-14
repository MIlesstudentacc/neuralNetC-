#pragma once
#include <vector>
#include "iostream"

#include "MNIST.h"
#include <map>
#include <string>
#include "sstream"
#include "fstream"
class MNISTreader
{
private:
	std::vector<std::vector<MNIST*>> MNISTRows;
	std::vector<int> classID;
	std::vector<MNIST*> SampleSet;
	std::map<std::string, int> numericalFormClass;
	MNIST* maxAttribute = new MNIST();
	MNIST* minAttribute = new MNIST();
	
public:
	void readFile(std::string csvFile);

	void populateStorageTemplate(); 

	void normalise(int index, double value,MNIST* sample); 

	void upateMaxAndMin(int index,double value); 

	void generateSampleSet(); 

	MNIST* takeSampleFromSet(int label);

	void normliseAll(); 
};

