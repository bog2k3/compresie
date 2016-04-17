/*
 * IStatisticsProvider.h
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#ifndef ISTATISTICSPROVIDER_H_
#define ISTATISTICSPROVIDER_H_

#include <map>
#include <string>

class IStatisticsProvider {
public:
	IStatisticsProvider() = default;
	virtual ~IStatisticsProvider() = default;

	virtual std::map<char, double> getTextStatistics(std::string const& input) = 0;
};

#endif /* ISTATISTICSPROVIDER_H_ */
