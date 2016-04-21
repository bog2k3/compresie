/*
 * Decompressor.h
 *
 *  Created on: Apr 20, 2016
 *      Author: bog
 */

#ifndef DECOMPRESSOR_H_
#define DECOMPRESSOR_H_

#include <vector>
#include <istream>
#include <string>

class Decompressor {
public:
	Decompressor() = default;
	virtual ~Decompressor() = default;

	void decompressToFile(std::istream &input, std::string const& outFileName);

private:
	std::string makeBitSequence(std::vector<unsigned char> const& bytes, int numBits);
};

#endif /* DECOMPRESSOR_H_ */
