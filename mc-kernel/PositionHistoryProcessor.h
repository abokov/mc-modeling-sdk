#ifndef ___POSITION_HISTORY_PROCESSOR__INC___
#define ___POSITION_HISTORY_PROCESSOR__INC___  1

#include <ModelCommon.h>
#include "mc-common/mc-base-types.h"

const long UNDEFINED_VALUE = -1;

class PositionHistoryData {
	BaseTypes::long_vector history;

	void CopyObject(const PositionHistoryData&);

protected:
	friend class PositionHistoryProcessor;

	inline BaseTypes::long_vector & GetHistoryPtr(void) {
		return history;
	}
public:
	PositionHistoryData(void) {
	}


	PositionHistoryData(const PositionHistoryData &obj) {
		CopyObject(obj);
	}

	~PositionHistoryData() {
	}

	PositionHistoryData& operator=(const PositionHistoryData& obj) {
		CopyObject(obj);
		return *this;
	}

	//---------------------------------------------------------------------------
	inline long GetValue(unsigned pos) const {
		if ((pos<0 ) || (pos >history.size()) )
			return UNDEFINED_VALUE;
		return history[pos];
	}
	inline void SetValue(unsigned pos, long value) {
		history[pos] = value;

	}

	inline void PushValue(long value) {
		history.push_back(value);
	}

	std::string PrintToString(void);
};


class PositionHistoryProcessor {
	PositionHistoryData &history_data;

public:

	PositionHistoryProcessor(PositionHistoryData &val):history_data(val) {
	}

	~PositionHistoryProcessor() {
	}
	
	// calculate parameter for MonteCarlo simulation
	// beta_a - it's dispersion 
	void Process(double &mua, double &beta_a);
};



#endif
