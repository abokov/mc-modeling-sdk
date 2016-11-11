#include <iostream>
#include <map>

#include <string.h>

#include "mc-common/mc-base-types.h"
#include <RandomGeneratorSimple.h>
#include <ModelBaseHistory.h>
#include <BrownMotionGeometric.h>
#include "data/hist_prices.h"

#include "simulation.h"


static MonteCarlo monte_carlo;

void runMonteCarlo(PositionJobData &job) {
	monte_carlo.runMonteCarlo(job);
};

MonteCarlo * getMonteCarlo(void) {
	return &monte_carlo;
};



MonteCarlo::MonteCarlo(void):random_generator(), brown_motion(random_generator) {
	init_models();
};


MonteCarlo::~MonteCarlo() {
	// memory cleanup
	ModelMappingMap::iterator iter = model_mapping.begin(), end = model_mapping.end();
	while (iter != end) {
		MonteCarloModel::ModelCommonDouble * model = iter->second;
		delete model;
 		++iter;
	}

}



void MonteCarlo::UpdateBrownMotionValues(void) {
	ModelMappingMap::iterator iter = model_mapping.begin(), end = model_mapping.end();
	while (iter != end) {
		MonteCarloModel::ModelCommonDouble * model = iter->second;
                model->UpdateBrownMotion(brown_motion.GetMovementValue());
 		++iter;
	}
}



void MonteCarlo::runMonteCarlo(PositionJobData &jobData) {
try {

#ifdef _DBG_OUTPUT_
	std::cout<<"\n\n\n\n. c++ lib : entry data - before simulation\n";

	std::string s = jobData.PrintToString();
	std::cout << s << std::endl;
	PositionVector & vec = jobData.GetPortfolioPtr();
	for (int i=0; i < vec.size(); i++) {
		s = vec[i].PrintToString();
		std::cout << s << std::endl;
	};
#endif	



	PositionProcessor processor(jobData);

	processor.Process();

#ifdef _DBG_OUTPUT_
	std::cout<<"\n\n c++ - after simulation\n";
	vec = jobData.GetPortfolioPtr();
	for (int i=0; i < vec.size(); i++) {
		s = vec[i].PrintToString();
		std::cout << s << std::endl;
	};
	std::cout<<"\n\n";
#endif


} catch (std::bad_alloc &mem )  {
	printf("Run time error ( bad_alloc ) : runMonteCarlo exception : %s\n", mem.what());
} catch (std::exception& exc) {
	printf("Run time error : runMonteCarlo exception : %s\n", exc.what());
} catch (...) {
	printf("Run time error : runMonteCarlo unknown exception\n");
}
}



void MonteCarlo::init_models(void) {
    for (int val = StockOptions::TreasureBond; val <= StockOptions::JPMorganChase; ++val) {
		BaseTypes::double_vector & hist = StockOptions::GetHistory((StockOptions::FondTypes)val);
		AddModel(GetTypeName((StockOptions::FondTypes)val), hist);
    }

};
 
void MonteCarlo::AddModel(const char *stock_name,BaseTypes::double_vector &history) {
	double param, delta_x, brown_val;
	get_params(history, param, delta_x);
	brown_val = brown_motion.GetMovementValue();
	MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_val, param, delta_x);
	model_mapping[stock_name] = monte_carlo_model;
};




// param = arith_mean/sqrt(dispersion)
void MonteCarlo::get_delta_x(BaseTypes::double_vector&hist, double & delta_x) {
	const long Days= 130; // 100 positions in history corresponds ~130 days 
	delta_x = BaseTypes::get_differencial(hist)/Days;
}


// param = arith_mean/sqrt(dispersion)
void MonteCarlo::get_params(BaseTypes::double_vector&hist, double & param, double &delta_x) {
	double arith_mean = BaseTemplates::arithmeticMean<double>(hist);
	double dispersion = BaseTypes::dispersion(hist, arith_mean);
	dispersion = sqrt(dispersion);
	param = dispersion / arith_mean;

// try to calculate delta_x
	get_delta_x(hist, delta_x);
}



// model depends on position's name
MonteCarloModel::ModelCommonDouble * MonteCarlo::GetModel(const char *s) {
	ModelMappingMap::iterator iter, end = model_mapping.end();
	iter = model_mapping.find(s);

	if (iter == end)
             iter = model_mapping.find(std::string(GetTypeName(StockOptions::TreasureBond)));

	return iter->second;
};



void MonteCarlo::PrintAll(void) {
	ModelMappingMap::iterator iter = model_mapping.begin(), end = model_mapping.end();
	while (iter != end) {
		MonteCarloModel::ModelCommonDouble * model = iter->second;
                std::cout<<" type : "<<iter->first<<": "<<model->Print()<<std::endl;
 		++iter;
	}
}


// use perc_accumulated
bool MonteCarlo::IsPositionBankAccount(const char *s) {
    //bool b = std::string(s) == Model_TreasuryBond30;
    bool b = (strcmp(s, GetTypeName(StockOptions::TreasureBond))==0);
    return b;

}






