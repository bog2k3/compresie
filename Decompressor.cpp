/*
 * Decompressor.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: bog
 */

#include "Decompressor.h"
#include "dictionaryMapElement.h"
#include <map>

void Decompressor::decompressToFile(std::istream &input, std::string const& outFileName) {
	// 1. citim dictionarul
	unsigned int dictSize;
	input.read((char*)&dictSize, sizeof(dictSize));
	std::map<std::vector<bool>, char> dict;
	for (unsigned i=0; i<dictSize; i++) {
		mapElement e;
		e.readFrom(input);
		dict[makeBitSequence(e.bytes, e.numBits)] = e.ch;
	}

	return;

	// 2. citim continutul
}

std::vector<bool> Decompressor::makeBitSequence(std::vector<unsigned char> bytes, int numBits) {
	std::vector<bool> bits;
	int crtByte = 0, crtBit = 0;
	for (int i=0; i<numBits; i++) {
		bits.push_back((bytes[crtByte] & (1 << (7-crtBit)) >> (7-crtBit)) != 0);
		crtBit += 1;
		if (crtBit == 8) {
			crtByte++;
			crtBit = 0;
		}
	}
	return bits;
}

