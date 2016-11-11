

#ifndef ___POSITION_PROCESSOR__INC___
#define ___POSITION_PROCESSOR__INC___  1

#include <string>
#include <vector>

#include <ModelCommon.h>

#include "xml_tools/xml_config.h"


class PositionData {
	std::string name, type;
	double units, amount, simulatedValue;

	double price;

	double perc_accumulated;
	double perc_accumulated_sum;
	bool is_bank_account;

	void CopyObject(const PositionData&);
public:
	PositionData(void) {
		Init("", "", 1, 2, 3, false, 0, 0);
	}

	PositionData(std::string val_name, std::string val_type, double val_units, double val_amount, double val_simulatedValue,
                bool val_is_bank_account, double val_perc, double val_perc_sum) {
		Init(val_name, val_type, val_units, val_amount, val_simulatedValue, val_is_bank_account, val_perc, val_perc_sum);
	}

	PositionData(const PositionData &obj) {
		CopyObject(obj);
	}

	~PositionData() {
	}

	PositionData& operator=(const PositionData& obj) {
		CopyObject(obj);
		return *this;
	}

//---------------------------------------------------------------------------


	inline void Init(std::string val_name, std::string val_type,	double val_units, double val_amount, double val_simulatedValue,
                bool val_is_bank_account, double val_perc, double val_perc_sum) {
		name = val_name;
		type = val_type;
		units = val_units;
		amount = val_amount;
		simulatedValue = val_simulatedValue;
                is_bank_account = val_is_bank_account;
                perc_accumulated = val_perc;
                perc_accumulated_sum = val_perc_sum;
	}



	inline const char * GetName(void) const {
		return name.c_str();
	}
	inline void SetName(std::string &s) {
		name = s;
	}
	inline void SetName(const char *s) {
		name = s;
	}


	inline const char* GetType(void) const {
		return type.c_str();
	}
	inline void SetType(std::string &s) {
		type = s;
	}
	inline void SetType(const char *s) {
		type = s;
	}



	inline double GetUnits(void) const {
		return units;
	}
	inline void SetUnits(double val) {
		units = val;
	}


	inline double GetAmount(void) const {
		return amount;
	}
	inline void SetAmount(double val) {
		amount = val;
	}

	inline double GetSimulatedValue(void) const {
		return simulatedValue;
	}
	inline void SetSimulatedValue(double val) {
		simulatedValue = val;
	}


        inline void SetPrice(double val) {
            price = val;
        }

        inline double GetPrice(void) const {
            return price;
        }


        inline void SetIsBankAccount(bool val) {
            is_bank_account = val;
        }

        inline bool GetIsBankAccount(void) const {
            return is_bank_account;
        }

        inline void SetPercentAccumulated(double val) {
            perc_accumulated = val;
        }

        inline double GetPercentAccumulated(void) const {
            return perc_accumulated;
        }


        inline void SetPercentAccumulatedSum(double val) {
            perc_accumulated_sum = val;
        }

        inline double GetPercentAccumulatedSum(void) const {
            return perc_accumulated_sum;
        }


// -- read/write methods


	std::string PrintToString(void); //more for debug purposes

	bool ReadFromFile(std::string &s);
};


typedef std::vector<PositionData> PositionVector;

class PositionJobData {
	PositionVector portfolio;
	// Forecast horizon in days.
	int horizon;
	// Number of Monte-Carlo iterations.
	int iters;

	void CopyObject(const PositionJobData&);
public:
	PositionJobData(void) {
        	horizon = iters = 0;
	}

	PositionJobData(BaseTypes::SimulationTask &task);

	PositionJobData(const PositionJobData &obj) {
		CopyObject(obj);
	}

	~PositionJobData() {
	}

	PositionJobData& operator=(const PositionJobData& obj) {
		CopyObject(obj);
		return *this;
	}


	inline PositionVector GetPortfolio(void) const {
		return portfolio;
	}

	inline PositionVector & GetPortfolioPtr(void) {
		return portfolio;
	}

	inline void SetHorizon(int i) {
		horizon = i;
	}

	inline int GetHorizon(void) const {
		return horizon;
	}

	inline void SetIters(int i) {
		iters = i;
	}

	inline int GetIters(void) const {
		return iters;
	}

	std::string PrintToString(void);
};





class PositionProcessor {
	PositionJobData & job_data;
public:
	PositionProcessor(PositionJobData &val);
	~PositionProcessor();
	
	void Process(void);
};



#endif
