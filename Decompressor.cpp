/*
 * Decompressor.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: bog
 */

#include "Decompressor.h"
#include "dictionaryMapElement.h"
#include <map>
#include <fstream>

void Decompressor::decompressToFile(std::istream &input, std::string const& outFileName) {
	// 1. citim dictionarul
	unsigned int dictSize;
	input.read((char*)&dictSize, sizeof(dictSize));
	std::map<std::string, char> dict;
	for (unsigned i=0; i<dictSize; i++) {
		mapElement e;
		e.readFrom(input);
		dict[makeBitSequence(e.bytes, e.numBits)] = e.ch;
	}

	// 2. citim continutul
	std::vector<unsigned char> buffer;
	while (!input.eof()) {
		unsigned char c;
		input.read((char*)&c, sizeof(c));
		buffer.push_back(c);
	}

	// transformam in secventa de biti:
	std::string bits = makeBitSequence(buffer, buffer.size() * 8);

	// interpretam cuvintele de cod si scriem caracterele asociate in fisierul de iesire:
	std::ofstream out(outFileName);

	std::string cuvantulCurent;
	auto it = bits.begin();
	while (it != bits.end()) {
		cuvantulCurent.push_back(*it);
		it++;
		if (dict.find(cuvantulCurent) != dict.end()) {
			// cuvantul este complet
			out << dict[cuvantulCurent];
			cuvantulCurent.clear();
		}
	}
}

std::string Decompressor::makeBitSequence(std::vector<unsigned char> const& bytes, int numBits) {
	std::string bits;
	int crtByte = 0, crtBit = 7;
	for (int i=0; i<numBits; i++) {
		if (crtBit < 0) {
			crtByte++;
			crtBit = 7;
		}
		bits.push_back((bytes[crtByte] & (1 << crtBit)) != 0 ? '1' : '0');
		crtBit--;
	}
	return bits;
}

