/*
 * Compressor.h
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

#include <string>
#include <vector>
#include <map>

class Compressor {
public:
	Compressor() = default;
	virtual ~Compressor() = default;

	void compressToFile(std::string const& input,
			std::map<char, std::vector<bool>> seqMap,
			std::string const& filename);

private:
	std::vector<unsigned char> assembleBits(std::vector<bool> seq);
};

#endif /* COMPRESSOR_H_ */
