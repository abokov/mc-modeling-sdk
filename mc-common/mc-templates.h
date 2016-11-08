#ifndef __MC_TEMPLATES_INC__
#define __MC_TEMPLATES_INC__  1

namespace BaseTemplates {


template<class T> double arithmeticMean(const std::vector<T> &arr) {
	if (arr.size() == 0 )
		return 0;

	double	sum = std::accumulate(arr.begin(), arr.end(), 0.0 );
	return sum / arr.size();
}

template<class T> T product(T & val1, T & val2) {
	return val1 * val2;	
}

template<class T> double geometricMean(const std::vector<T> &arr) {
	if (arr.size() == 0 )
		return 0;

	double	mult = std::accumulate(arr.begin(), arr.end(), 1, product<T> );
	return pow(mult, 1.0/ arr.size() );
}


template<class T> T deviation_square(T & val1,T & val2) {
	T val = (val1 - val2);
	val *= val;
	return val;
}

} 

#endif
