/*
 * dictionaryMapElement.h
 *
 *  Created on: Apr 20, 2016
 *      Author: bog
 */

#ifndef DICTIONARYMAPELEMENT_H_
#define DICTIONARYMAPELEMENT_H_

#include <vector>
#include <iostream>

struct mapElement {
	char ch;
	unsigned char numBits;
	std::vector<unsigned char> bytes;

	void writeTo(std::ostream &str) {
		str.write(&ch, sizeof(ch));
		str.write((char*)&numBits, sizeof(numBits));
		for (auto b : bytes)
			str.write((char*)&b, sizeof(b));
	}

	void readFrom(std::istream &str) {
		str.read(&ch, sizeof(ch));
		str.read((char*)&numBits, sizeof(numBits));
		int numBytes = (numBits-1)/8 + 1;
		for (int j=0; j<numBytes; j++) {
			unsigned char b;
			str.read((char*)&b, sizeof(b));
			bytes.push_back(b);
		}
	}
};

#endif /* DICTIONARYMAPELEMENT_H_ */
