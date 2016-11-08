#ifndef ___HISTORY_DATABASE__INC___
#define ___HISTORY_DATABASE__INC___  1

#include <string>
#include <map>

#include "mc-common/mc-base-types.h"

struct PortfolioElementData {
	double relative_shift;
	double differential_x;
};

struct HistoryParams {
	BaseTypes::PortfolioElement element;
	PortfolioElementData data;
};


class HistoryDatabase {
	typedef std::map<std::string, HistoryParams> history_map;
	history_map database;

	// read PortfolioElement and init PortfolioElementData
	void ProcessHistory(HistoryParams &val);

public:

	HistoryDatabase() {
	}
	~HistoryDatabase() {
	}
	
	// history and calculate data for PortfolioElementData, if name already exists - replace it
	void Add(const char *name, BaseTypes::PortfolioElement &element);
	
	bool GetData(const char *name, HistoryParams &param);

	// check name for exists in HistoryDB
	inline bool IsExists(const char*name) const {
		return database.find(name) != database.end();
	};

};


#endif


