/*
 * Compressor.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#include "Compressor.h"
#include "BitWriter.h"
#include <fstream>
#include <iostream>

std::vector<unsigned char> Compressor::assembleBits(std::vector<bool> seq) {
	std::vector<unsigned char> vec;
	vec.push_back(0);
	unsigned char &c = vec.back();
	unsigned char count = 0;
	for (unsigned i=0; i<seq.size(); i++) {
		c = (c << 1) | (seq[i] ? 1 : 0);
		count++;
		if (count == 8) {
			vec.push_back(0);
			c = vec.back();
		}
	}
	return vec;
}

struct mapElement {
	char ch;
	unsigned char size;
	std::vector<unsigned char> bytes;
};

void Compressor::compressToFile(std::string const& input,
			std::map<char, std::vector<bool>> seqMap,
			std::string const& filename) {

	std::ofstream f(filename, std::ios::binary);

	// scriem dictionarul:
	std::cout << "scriem dict...\n";
	f << seqMap.size();
	for (auto x : seqMap) {
		mapElement e;
		e.ch = x.first;
		e.bytes = assembleBits(x.second);
		e.size = x.second.size();

		f << e.ch << e.size;
		for (auto b : e.bytes)
			f << b;
	}
	std::cout << "scriem text...\n";
	BitWriter bw(f);
	for (char c : input) {
		bw.addBits(seqMap[c]);
	}
	bw.finish();
}

void Compressor::compressToScreen(std::string const& input,
			std::map<char, std::vector<bool>> seqMap) {
	int bitCount = 0;
	for (char c : input) {
		for (bool b : seqMap[c]) {
			std::cout << (b?"1":"0");
			bitCount++;
		}
	}
	std::cout << "\n\nCompressed bit count: " << bitCount << "\n";
}
