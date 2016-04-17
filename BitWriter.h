/*
 * BitWriter.h
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#ifndef BITWRITER_H_
#define BITWRITER_H_

#include <fstream>
#include <vector>

class BitWriter {
public:
	BitWriter(std::ostream &str);
	virtual ~BitWriter() = default;

	void addBits(std::vector<bool> const& bits);
	void finish();

private:
	std::ostream &str;
	unsigned char c = 0;
	unsigned char count = 0;
};

#endif /* BITWRITER_H_ */
