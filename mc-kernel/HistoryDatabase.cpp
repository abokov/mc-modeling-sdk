#include "HistoryDatabase.h"



// read PortfolioElement and init PortfolioElementData
void HistoryDatabase::ProcessHistory(HistoryParams &val) {
	double arith_mean = BaseTemplates::arithmeticMean<double>(val.element.history);
	double dispersion = BaseTypes::dispersion(val.element.history, arith_mean);
	dispersion = sqrt(dispersion);

	val.data.relative_shift = dispersion / arith_mean;
	val.data.differential_x = BaseTypes::get_differencial(val.element.history);
}



// history and calculate data for PortfolioElementData
void HistoryDatabase::Add(const char *name, BaseTypes::PortfolioElement &element) {
	HistoryParams param;
	param.element = element;
	ProcessHistory(param);
	database[name] = param;
}



bool HistoryDatabase::GetData(const char *name, HistoryParams &param) {
	history_map::const_iterator iter = database.find(name);
	if ( iter == database.end() )
		return false;
	param.data = iter->second.data;
	return true;
}
