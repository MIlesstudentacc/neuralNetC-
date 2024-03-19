#include "fileReader.h"
#include "fileReader.h"
#include "c++NeuralNet/fileReader.h"


std::vector<int> fileReader::getClassID()
{
	return classID;
}

void fileReader::readFile(std::string csvFile)
{
	std::ifstream reader;
	int rowNum = -1; 
	int classFoundNo = 0;
	reader.open("C:/Users/Miles/source/repos/neuralNetC2-/iris.csv");
	std::string line = "";
	std::getline(reader, line);
	std::cout << line << std::endl;
	std::string current_Class = "NONE";
	while (std::getline(reader, line))
	{
		rowNum = rowNum++; 
		std::stringstream row(line);
		std::string strSepalLength;
		std::getline(row, strSepalLength,',');
		double sepalLength = std::stod(strSepalLength);

		std::string strSepalWidth;
		std::getline(row, strSepalWidth, ',');
		double sepalWidth = std::stod(strSepalLength);


		std::string strPetalLength;
		std::getline(row, strPetalLength, ',');
		double petalLength = std::stod(strPetalLength);

		std::string strPetalWidth;
		std::getline(row, strPetalWidth, ',');
		double petalWidth = std::stod(strPetalWidth);

		std::string species;
		std::getline(row, species, ',');
		
		if (current_Class != species)
		{
			classFoundNo++;
			classID.push_back(rowNum);
			numericalFormClass[current_Class] = classFoundNo;
		}
		current_Class = species;
		

		irisDataClass* parsedRow = new irisDataClass(sepalLength, sepalWidth, petalLength, petalWidth, species);
		irisRows.push_back(parsedRow);
	}

}

void fileReader::generateSampleSet()
{
	int start = 0; 
	int maxClasses = 3;
	classID.push_back(irisRows.size());
	for (int classPos = 0; classPos < classID.size()-1;classPos++)
	{
		for (int sampleID = 0; sampleID < 10; sampleID++)
		{
			int start = classID[classPos];
			int randRange = classID[classPos + 1] - start;
			int random = rand() % randRange;
			int sample = start + random; 
			SampleSet.push_back(irisRows[sample]);
		}
	}
}

std::vector<irisDataClass*> fileReader::getSampleSet()
{
	return SampleSet;
}

irisDataClass* fileReader::takeSampleFromSet()
{
	int random = rand() % SampleSet.size();
	return SampleSet[random];
}

int fileReader::getNumberFromClass(std::string Class)
{
	return numericalFormClass[Class];
}
