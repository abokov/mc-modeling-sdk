#ifndef ___BASE_TYPES_INCLUDE___
#define ___BASE_TYPES_INCLUDE___ 1

#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <math.h>
#include <cstdio>

#include "mc-common/mc-templates.h"

namespace BaseTypes {

// embedd some fields into simple structs...

struct SimulationTaskResult {
	std::map<std::string, double> result;
};

struct PortfolioElement {
	enum Type  { bond = 1, stock } poftfolio_type;
	unsigned amount;
	std::vector<double> history;
};


struct SimulationTask {
	typedef std::map<std::string, PortfolioElement> map_portfolio;
	unsigned horizon;
	enum HorizonType { days=1, months, years } horizon_type;

	map_portfolio elements;
};





typedef std::vector<long> long_vector;
typedef std::vector<double> double_vector;

// keep this functions inline from performance perspective, don't rely on compiler
inline double dispersion(double_vector &arr, double arithmetic_mean) {
	if (arr.size() == 0 )
		return 0;

	double sum = 0;
	double_vector::const_iterator iter = arr.begin(), end = arr.end();
	while (iter != end ) {
		double val = *iter;
		sum += BaseTemplates::deviation_square<double> ( val, arithmetic_mean);
		++iter;
	}
	return sum / arr.size();
}

inline double dispersion(long_vector &arr, double arithmetic_mean) {
	if (arr.size() == 0 )
		return 0;

	double sum = 0;
	long_vector::const_iterator iter = arr.begin(), end = arr.end();
	while (iter != end ) {
		double val = *iter;
		sum += BaseTemplates::deviation_square<double> ( val, arithmetic_mean);
		++iter;
	}
	return sum / arr.size();
}

inline double get_differencial(double_vector &arr) {
	if (arr.size() < 2 )
		return 0;

	double diff = 0;
	double_vector::const_iterator iter = arr.begin(), end = arr.end();
	double prev = *iter;
	while (iter != end ) {
		diff += (*iter - prev);
		prev = * iter;
		++iter;
	}
	return diff;
}


}


#endif

