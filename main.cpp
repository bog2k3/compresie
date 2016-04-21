/*
 * main.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#include "IStatisticsProvider.h"
#include "TreeBuilder.h"
#include "TextStatistics.h"
#include "Compressor.h"
#include "Decompressor.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>


IStatisticsProvider* createStatsProvider() {
	return new TextStatistics();
}

// citeste text dintr-un stream:
std::string getInputFromStream(std::istream &stream) {
	std::string buffer;
	std::string line;
	while (std::getline(stream, line))
		buffer += line + "\n";
	return buffer;
}

// construieste secventa de biti pentru toate caracterele din arbore:
void buildCharSeq(std::map<char, std::vector<bool>> &map, TreeNode* pNode) {
	if (pNode->isLeaf())
		pNode->getBitSequence(map[pNode->ch[0].first]);
	if (pNode->pLeft)
		buildCharSeq(map, pNode->pLeft);
	if (pNode->pRight)
		buildCharSeq(map, pNode->pRight);
}

void prettyPrintCharSeq(std::map<char, std::vector<bool>> sq, std::map<char, double> stats) {
	using mapPair = std::pair<char, std::vector<bool>>;
	std::vector<mapPair> lista;

	for (auto x : sq)
		lista.push_back(x);
	std::sort(lista.begin(), lista.end(), [](mapPair &l, mapPair &r) {
		return l.second.size() < r.second.size();
	});
	for (auto x : lista) {
		std::cout << x.first << "(" << std::fixed << std::setprecision(4) << stats[x.first] << "): ";
		for (bool b : x.second)
			std::cout << (b?"1":"0");
		std::cout << "\n";
	}
}

double avgEntropy(std::map<char, double> &seq, int length) {
	double ent = 0;
	for (auto p : seq) {
		ent += log2(1.0 / p.second) * p.second;
	}
	return ent;
}

int main(int argc, char* argv[]) {
	std::string buffer;
	std::string outFileName;

	bool interactive = false;
	bool decompress = false;

	if (argc < 2) {
		buffer = getInputFromStream(std::cin);
		interactive = true;
	} else {
		decompress = std::string("-d") == argv[1];
		if (!decompress) {
			std::ifstream fs(argv[2]);
			buffer = getInputFromStream(fs);
		}
		outFileName = argv[3];
	}

	if (!decompress) {
		IStatisticsProvider* pStatsProvider = createStatsProvider();

		std::map<char, double> stats = pStatsProvider->getTextStatistics(buffer);
		TreeNode* pTree = TreeBuilder::buildHuffmanTree(stats);

		std::map<char, std::vector<bool>> charSeq;
		buildCharSeq(charSeq, pTree);

		if (interactive)
		{
			std::cout << "-----------------------------------------------------------------------\n";
			int inputBits = buffer.size() * 8;
			std::cout << "Numar biti intrare: " << inputBits << "\n";
			double avgEntropInput = avgEntropy(stats, buffer.size());
			std::cout << "Entropia medie pe caracter in text: " << avgEntropInput << " bit/caracter\n";
			double redundanta = buffer.size() * (8 -  avgEntropInput);
			std::cout << "Redundanta in text: " << redundanta << " biti\n";
			std::cout << "Informatia din text: " << avgEntropInput * buffer.size() << " biti\n";
			std::cout << "-----------------------------------------------------------------------\n";
			std::cout << "[DICTIONAR:]\n";
			std::cout << "-----------------------------------------------------------------------\n";
			prettyPrintCharSeq(charSeq, stats);
			std::cout << "-----------------------------------------------------------------------\n";
			std::cout << "[TEXTUL CODIFICAT:]\n";
			std::cout << "-----------------------------------------------------------------------\n";
			Compressor c;
			c.compressToScreen(buffer, charSeq);
		}
		else {	// neinteractiv
			Compressor c;
			c.compressToFile(buffer, charSeq, outFileName);
		}

		delete pStatsProvider;
		delete pTree;

	} else { // decompresie
		Decompressor d;
		std::ifstream input(argv[2], std::ios::binary);
		d.decompressToFile(input, outFileName);
	}
}

