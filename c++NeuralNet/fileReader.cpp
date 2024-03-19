#include "fileReader.h"

void fileReader::readFile(std::string csvFile)
{
	std::ifstream reader;
	reader.open("C:/Users/Miles/source/repos/neuralNetC-2/iris.csv");
	std::string line = "";
	std::getline(reader, line);
	std::cout << line << std::endl; 

}
