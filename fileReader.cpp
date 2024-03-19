#include "fileReader.h"

void fileReader::readFile(std::string csvFile)
{
	std::ifstream reader;
	reader.open("C:/Users/Miles/source/repos/neuralNetC2-/iris.csv");
	std::string line = "";
	std::getline(reader, line);
	std::cout << line << std::endl;
	
	while (std::getline(reader, line))
	{
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
		
		irisDataClass* parsedRow = new irisDataClass(sepalLength, sepalWidth, petalLength, petalWidth, species);
		irisRows.push_back(parsedRow);
	}

}
