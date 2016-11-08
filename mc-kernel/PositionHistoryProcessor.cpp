#include <sstream>
#include "PositionHistoryProcessor.h"



//-------------------------------------------------------------------------------------------------------------------------
void PositionHistoryData::CopyObject(const PositionHistoryData& val) {
	history = val.history;	
}

std::string PositionHistoryData::PrintToString(void) {
	std::stringstream ss;

	BaseTypes::long_vector::const_iterator iter = history.begin(), end = history.end();
	long cnt = 0;
	while (iter != end)  {
		ss << "h[" << (cnt++) << "]=" <<(*iter);
		if ( cnt%10 ) 
			ss << ", ";
		else
			ss << "\n";

		++iter;
	}

	std::string s;
	getline(ss, s,'\n');
	return s;
}

//----------------------------------------------------------------------------------------------------------------------------------


// calculate parameter for MonteCarlo simulation
// beta a - is actually square from dispersion = arithmetic mean of square of deviations
void PositionHistoryProcessor::Process(double &mua, double &beta_a) {
	BaseTypes::long_vector & history = history_data.GetHistoryPtr();
	BaseTypes::long_vector::const_iterator iter = history.begin(), end = history.end();

	double arithmetic_mean = BaseTemplates::arithmeticMean<long>(history);
	beta_a = sqrt (BaseTypes::dispersion(history, arithmetic_mean));
	mua = arithmetic_mean; // not sure about this
};


