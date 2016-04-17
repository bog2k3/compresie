/*
 * main.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#include "IStatisticsProvider.h"
#include "TreeBuilder.h"
#include "TextStatistics.h"
#include <iostream>
#include <fstream>


IStatisticsProvider* createStatsProvider() {
	return new TextStatistics();
}

std::string getInputFromStream(std::istream &stream) {
	std::string buffer;
	std::string line;
	while (std::getline(stream, line))
		buffer += line + "\n";
	return buffer;
}

int main(int argc, char* argv[]) {
	std::string buffer;

	if (argc < 2)
		buffer = getInputFromStream(std::cin);
	else {
		std::ifstream fs(argv[1]);
		buffer = getInputFromStream(fs);
	}

	IStatisticsProvider* pStatsProvider = createStatsProvider();

	std::map<char, double> stats = pStatsProvider->getTextStatistics(buffer);
	TreeNode* pTree = TreeBuilder::buildHuffmanTree(stats);

	// ...

	delete pStatsProvider;
	delete pTree;
}

