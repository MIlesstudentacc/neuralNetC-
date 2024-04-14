#include "MNISTreader.h"

void MNISTreader::readFile(std::string csvFile)
{
	double pixelInputs[784]; 
	std::ifstream reader;
	int rowNum = -1;
	int classFoundNo = 0;
	reader.open("C:/Users/Miles/source/repos/neuralNetC-4/mnist_train.csv");
	std::string line = "";
	std::getline(reader, line);
	std::cout << line << std::endl;
	std::string current_Class = "NONE";
	minAttribute->allInputZero();
	maxAttribute->allInputZero(); 
	
	//while (std::getline(reader, line)) 
	
	for(int j = 0; j < 500;j++)
	{
		std::getline(reader, line);
		std::stringstream row(line);
		std::string NumClass;
		std::getline(row, NumClass, ',');
		int intNumClass = std::stoi(NumClass);
		for (int i = 0; i < 784; i++)
		{
			std::string pixel;
			std::getline(row, pixel, ',');
			double pixelNum = std::stod(pixel);
			pixelInputs[i] = pixelNum;
			upateMaxAndMin(i, pixelNum);

		}
		MNIST* myMNISTObj = new MNIST(pixelInputs,intNumClass);
		//myMNISTObj->displayPixels();
		MNISTRows.at(intNumClass).push_back(myMNISTObj);

	}



}

void MNISTreader::populateStorageTemplate()
{
	for (int i = 0; i < 10; i++)
	{
		MNISTRows.push_back(std::vector<MNIST*>());
	}
}

void MNISTreader::normalise(int index, double value,MNIST* sample)
{
	double min = minAttribute->getValueAtIndex(index);
	double max = maxAttribute->getValueAtIndex(index);
	if (min == 0 && value == 0 && max == 0)
	{
		sample->setInputIndexValue(index, 0);
	}
	else
	{
		sample->setInputIndexValue(index, (value - min) / (max - min));
	}


}

void MNISTreader::upateMaxAndMin(int index, double value )
{
	if (minAttribute->getValueAtIndex(index) > value)
	{
		minAttribute->setInputIndexValue(index, value);
	}
	if (maxAttribute->getValueAtIndex(index) < value)
	{
		maxAttribute->setInputIndexValue(index, value); 
	}

}

void MNISTreader::generateSampleSet()
{
	SampleSet.clear();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			int random = rand() % 5;
			//MNISTRows.at(i).at(random)->displayPixels();
			SampleSet.push_back(MNISTRows.at(i).at(random));
		}
	}
}

MNIST* MNISTreader::takeSampleFromSet(int label)
{
	int random = rand() % ((SampleSet.size()) - 1);
	MNIST* sample = SampleSet[random];
	sample->displayPixels();
	SampleSet[random] = SampleSet[SampleSet.size() - 1];
	SampleSet.pop_back();
	return sample;
}

void MNISTreader::normliseAll()
{
	std::vector<MNIST*> vecPointer;
	MNIST* sample;
	for (int i = 0; i < 10; i++)
	{
		vecPointer = MNISTRows[i];
		for (int vecIt = 0; vecIt < vecPointer.size(); vecIt++)
		{
			sample = vecPointer.at(vecIt);
			for (int index = 0; index < 748; index++)
			{
				normalise(index, sample->getValueAtIndex(index),sample);
			}
		}
	}
}
