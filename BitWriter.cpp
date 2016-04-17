/*
 * BitWriter.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#include "BitWriter.h"

BitWriter::BitWriter(std::ostream &str)
	: str(str)
{
	// TODO Auto-generated constructor stub
}

void BitWriter::addBits(std::vector<bool> const& bits) {
	for (bool b : bits) {
		c = (c << 1) | (b ? 1 : 0);
		count++;
		if (count == 8) {
			str << c;
			count = 0;
			c = 0;
		}
	}
}
void BitWriter::finish() {
	if (count == 0)
		return;
	while (count++ < 8) {
		c = (c << 1) | 1;
	}
	str << c;
}

