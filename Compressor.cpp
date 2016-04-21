/*
 * Compressor.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#include "Compressor.h"
#include "BitWriter.h"
#include "dictionaryMapElement.h"
#include <fstream>
#include <iostream>

std::vector<unsigned char> Compressor::assembleBits(std::vector<bool> const& seq) {
	std::vector<unsigned char> vec;
	vec.push_back(0);
	unsigned char *c = &vec.back();
	int bit = 7;
	for (unsigned i=0; i<seq.size(); i++) {
		if (bit < 0) {
			vec.push_back(0);
			c = &vec.back();
			bit = 7;
		}
		*c = *c | ((seq[i] ? 1 : 0) << bit);
		bit--;
	}
	return vec;
}

void Compressor::compressToFile(std::string const& input,
			std::map<char, std::vector<bool>> & seqMap,
			std::string const& filename) {

	std::ofstream f(filename, std::ios::binary);

	// scriem dictionarul:
	std::cout << "scriem dict...\n";
	unsigned int mapSize = seqMap.size();
	f.write((char*)&mapSize, sizeof(mapSize));
	for (auto x : seqMap) {
		mapElement e;
		e.ch = x.first;
		e.bytes = assembleBits(x.second);
		e.numBits = x.second.size();

		e.writeTo(f);
	}
	std::cout << "scriem text...\n";
	BitWriter bw(f);
	for (char c : input) {
		bw.addBits(seqMap[c]);
	}
	bw.finish();
	std::cout << "terminat!\n";
}

void Compressor::compressToScreen(std::string const& input,
			std::map<char, std::vector<bool>> & seqMap) {
	int bitCount = 0;
	for (char c : input) {
		for (bool b : seqMap[c]) {
			std::cout << (b?"1":"0");
			bitCount++;
		}
	}
	std::cout << "\n\nCompressed bit count: " << bitCount << "\n";
}
