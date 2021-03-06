/*
 * TextStatistics.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: xergi_000
 */

#include "TextStatistics.h"

std::map<char, double>  TextStatistics::getTextStatistics(std::string const& input) {
	std::map<char, double> LetterStatistic;
	for(int i=0; i<input.length(); i++){
		LetterStatistic[input[i]]++;
	}

	for(auto &j:LetterStatistic) {
		j.second /= input.length();
	}

	return LetterStatistic;
}

