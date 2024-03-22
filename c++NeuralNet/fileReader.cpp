#include "fileReader.h"



std::vector<int> fileReader::getClassID()
{
	return classID;
}

void fileReader::readFile(std::string csvFile)
{
	std::ifstream reader;
	int rowNum = -1; 
	int classFoundNo = 0;
	reader.open("C:/Users/c3622855/source/repos/iris.csv");
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
		double sepalWidth = std::stod(strSepalWidth);


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
			current_Class = species;
			classFoundNo++;
			classID.push_back(rowNum);
			
			numericalFormClass[current_Class] = classFoundNo;
		}
		

		irisDataClass* parsedRow = new irisDataClass(sepalLength, sepalWidth, petalLength, petalWidth, species);
		irisRows.push_back(parsedRow);
		if (rowNum == 0)
		{
			maxAttribute->copyObjArg(sepalLength, sepalWidth, petalLength, petalWidth);
			minAttribute->copyObjArg(sepalLength, sepalWidth, petalLength, petalWidth);
		}
		else
		{
			updateMax(parsedRow);
			updateMin(parsedRow);
		}
	}
	classID.push_back(irisRows.size());
	//standardDeviation();

}

void fileReader::generateSampleSet()
{
	SampleSet.clear();
	int start = 0; 
	int maxClasses = 3;
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

void fileReader::updateMax(irisDataClass* row)
{
	if (row->getPetalLength() > maxAttribute->getPetalLength())
	{
		maxAttribute->setPetalLength(row->getPetalLength());
	}
	if (row->getPetalWidth() > maxAttribute->getPetalWidth())
	{
		maxAttribute->setPetalWidth(row->getPetalWidth());
	}
	if (row->getSepalLength() > maxAttribute->getSepalLength())
	{
		maxAttribute->setSepalLength(row->getSepalLength());
	}
	if (row->getSepalWidth() > maxAttribute->getSepalWidth())
	{
		maxAttribute->setSepalWidth(row->getSepalWidth()); 
	}
}

void fileReader::updateMin(irisDataClass* row)
{

	if (row->getPetalLength() < minAttribute->getPetalLength())
	{
		minAttribute->setPetalLength(row->getPetalLength());
	}
	if (row->getPetalWidth() < minAttribute->getPetalWidth())
	{
		minAttribute->setPetalWidth(row->getPetalWidth());
	}
	if (row->getSepalLength() < minAttribute->getSepalLength())
	{
		minAttribute->setSepalLength(row->getSepalLength());
	}
	if (row->getSepalWidth() < minAttribute->getSepalWidth())
	{
		minAttribute->setSepalWidth(row->getSepalWidth());
	}
}

irisDataClass* fileReader::normalise(irisDataClass* Sample)
{
	double sampleAtt = Sample->getPetalLength();
	double minAtt = minAttribute->getPetalLength();
	double maxAtt = maxAttribute->getPetalLength(); 
	Sample->setPetalLength((sampleAtt-minAtt)/(maxAtt-minAtt));

	sampleAtt = Sample->getPetalWidth();
	minAtt = minAttribute->getPetalWidth();
	maxAtt = maxAttribute->getPetalWidth();
	Sample->setPetalWidth((sampleAtt - minAtt) / (maxAtt - minAtt));

	sampleAtt = Sample->getSepalLength();
	minAtt = minAttribute->getSepalLength();
	maxAtt = maxAttribute->getSepalLength();
	Sample->setSepalLength((sampleAtt - minAtt) / (maxAtt - minAtt));

	sampleAtt = Sample->getSepalWidth();
	minAtt = minAttribute->getSepalWidth();
	maxAtt = maxAttribute->getSepalWidth();
	Sample->setSepalWidth((sampleAtt - minAtt) / (maxAtt - minAtt));
	return Sample; 

}

void fileReader::standardDeviation()
{
	double petalLengthMean = 0;
	double petalWidthMean = 0;
	double sepalLengthMean = 0;
	double sepalWidthMean = 0; 
	for (int rows = 0; rows < irisRows.size(); rows++)
	{
		irisDataClass* row = irisRows.at(rows); 
		petalLengthMean = petalLengthMean + row->getPetalLength();
		petalWidthMean = petalWidthMean + row->getPetalWidth();
		sepalLengthMean = sepalLengthMean + row->getSepalLength();
		sepalWidthMean = sepalWidthMean + row->getSepalWidth();

	}
	int fullRowCount = irisRows.size();
	petalLengthMean = petalLengthMean / fullRowCount;
	petalWidthMean = petalWidthMean / fullRowCount;
	sepalLengthMean = sepalLengthMean / fullRowCount;
	sepalWidthMean = sepalWidthMean / fullRowCount;
	for (int rows = 0; rows < irisRows.size(); rows++)
	{
		irisDataClass* row = irisRows.at(rows);
		row->setPetalLength((pow(row->getPetalLength() - petalLengthMean, 2)) / (fullRowCount - 1));
		row->setPetalWidth((pow(row->getPetalWidth() - petalWidthMean, 2)) / (fullRowCount - 1));
		row->setSepalLength((pow(row->getSepalLength() - sepalLengthMean, 2)) / (fullRowCount - 1));
		row->setSepalWidth((pow(row->getSepalWidth() - sepalWidthMean, 2)) / (fullRowCount - 1));
	}
}

void fileReader::calcMeans()
{
	for (int rows = 0; rows < irisRows.size(); rows++)
	{
		irisDataClass* row = irisRows.at(rows);
		petalLengthMean = petalLengthMean + row->getPetalLength();
		petalWidthMean = petalWidthMean + row->getPetalWidth();
		sepalLengthMean = sepalLengthMean + row->getSepalLength();
		sepalWidthMean = sepalWidthMean + row->getSepalWidth();

	}
	int fullRowCount = irisRows.size();
	petalLengthMean = petalLengthMean / fullRowCount;
	petalWidthMean = petalWidthMean / fullRowCount;
	sepalLengthMean = sepalLengthMean / fullRowCount;
	sepalWidthMean = sepalWidthMean / fullRowCount;
}

irisDataClass* fileReader::standardDeviationOne(irisDataClass* sample)
{
	double fullRowCount = SampleSet.size(); 
	sample->setPetalLength(sqrt(((pow(sample->getPetalLength() - petalLengthMean, 2)) / (fullRowCount - 1))));
	sample->setPetalWidth(sqrt(((pow(sample->getPetalWidth() - petalWidthMean, 2)) / (fullRowCount - 1))));
	sample->setSepalLength(sqrt(((pow(sample->getSepalLength() - sepalLengthMean, 2)) / (fullRowCount - 1))));
	sample->setSepalWidth(sqrt(((pow(sample->getSepalWidth() - sepalWidthMean, 2)) / (fullRowCount - 1))));
	return sample;
}

irisDataClass* fileReader::takeSampleFromSet()
{
	int random = rand() % ((SampleSet.size())-1);
	irisDataClass* sample = SampleSet[random];
	SampleSet[random] = SampleSet[SampleSet.size() - 1];
	SampleSet.pop_back(); 
	return sample;
}

int fileReader::getNumberFromClass(std::string Class)
{
	return numericalFormClass[Class];
}

int fileReader::getSampleSetSize()
{
	return SampleSet.size();
}
