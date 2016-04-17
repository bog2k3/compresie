/*
 * TextStatistics.h
 *
 *  Created on: Apr 17, 2016
 *      Author: xergi_000
 */

#ifndef TEXTSTATISTICS_H_
#define TEXTSTATISTICS_H_

#include "IStatisticsProvider.h"

class TextStatistics: public IStatisticsProvider {
public:
	TextStatistics() = default;
	virtual ~TextStatistics() = default;

	std::map<char, double> getTextStatistics(std::string const& input) override;
};

#endif /* TEXTSTATISTICS_H_ */
