#include <iostream>
#include <map>

#include "mc-common/mc-base-types.h"
#include <RandomGeneratorSimple.h>
#include <ModelBaseHistory.h>
#include <BrownMotionGeometric.h>
#include "data/hist_prices.h"

#include "simulation_new.h"

#include "simulation.h"

#include "HistoryDatabase.h"
#if 0


MonteCarloNew::MonteCarloNew(void):random_generator(), brown_motion(random_generator) {
//	init_models();
};


MonteCarloNew::~MonteCarloNew() {

}




void MonteCarloNew::runMonteCarlo(BaseTypes::SimulationTask &task, BaseTypes::SimulationTaskResult &result) {
try {

	HistoryDatabase history;
	// try to resolve history for predefined values


	for (BaseTypes::SimulationTask::map_portfolio::iterator iter = task.elements.begin(), end = task.elements.end(); iter != end; ++iter) {
		history.Add(iter->first.c_str(), iter->second);
	}

/*	PositionProcessor processor(jobData);

	processor.Process();*/

/*	std::cout<<"\n\n c++ - after simulation\n";
	vec = jobData.GetPortfolioPtr();
	for (int i=0; i < vec.size(); i++) {
		s = vec[i].PrintToString();
		std::cout << s << std::endl;
	};
	std::cout<<"\n\n";*/

} catch (std::bad_alloc &mem )  {
	printf("Run time error ( bad_alloc ) : runMonteCarlo exception : %s\n", mem.what());
} catch (std::exception& exc) {
	printf("Run time error : runMonteCarlo exception : %s\n", exc.what());
} catch (...) {
	printf("Run time error : runMonteCarlo unknown exception\n");
}
}
#endif


#if 0
void MonteCarlo::init_models(void) {

//#define  Model_TreasuryBond30 "TreasuryBond30"
	{	CommonTypes::double_vector & hist = Get30TreasureBondHistory(); double param, delta_x, brown_val;
		get_params(hist, param, delta_x);
                brown_val = brown_motion.GetMovementValue();
//		MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_motion, param, delta_x);
		MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_val, param, delta_x);
		model_mapping[Model_TreasuryBond30] = monte_carlo_model;
	//	std::cout<<" Model_TreasuryBond30]=" << monte_carlo_model->Print()<<"\n";
	};
//#define  Model_S_and_P_100  "S&P-100"
	{	CommonTypes::double_vector & hist = GetSAndP100(); double param, delta_x, brown_val;
		get_params(hist, param, delta_x);
                brown_val = brown_motion.GetMovementValue();
		//MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_motion, param, delta_x);
		MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_val, param, delta_x);
		model_mapping[Model_S_and_P_100] = monte_carlo_model;
	//	std::cout<<"Model_S_and_P_100]="<< monte_carlo_model->Print()<<"\n";
	};

//#define  Model_S_and_P_500 "S&P-500"
	{	CommonTypes::double_vector & hist = GetSAndP500(); double param, delta_x, brown_val;
		get_params(hist, param, delta_x);
                brown_val = brown_motion.GetMovementValue();
//		MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_motion, param, delta_x);
		MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_val, param, delta_x);
		model_mapping[Model_S_and_P_500] = monte_carlo_model;
	//	std::cout<<"[Model_S_and_P_500]="<<monte_carlo_model->Print()<<"\n";
	};


//#define  Model_Russel_2000 "Russel2000"
	{	CommonTypes::double_vector & hist = GetRussel2000(); double param, delta_x, brown_val;
		get_params(hist, param, delta_x);
                brown_val = brown_motion.GetMovementValue();
		//MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_motion, param, delta_x);
		MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_val, param, delta_x);
		model_mapping[Model_Russel_2000] = monte_carlo_model;
	//	std::cout<<"[Model_Russel_2000]="<<monte_carlo_model->Print()<<"\n";
	};

//#define  Model_Defaul "ModelDefault"
	{	double param = 2;
                double brown_val = brown_motion.GetMovementValue();
		//MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_motion, param, 0);
		MonteCarloModel::BaseHistoryModel * monte_carlo_model = new MonteCarloModel::BaseHistoryModel(brown_val, param, 0);
		model_mapping["Default"] = monte_carlo_model;
	//	std::cout<<"[Model_Default]="<<monte_carlo_model->Print()<<"\n";
	};
};
 


// param = arith_mean/sqrt(dispersion)
void MonteCarlo::get_delta_x(CommonTypes::double_vector&hist, double & delta_x) {
	const long Days= 130; // 100 positions in history corresponds ~130 days 
	delta_x = CommonTypes::get_differencial(hist)/Days;
}


// param = arith_mean/sqrt(dispersion)
void MonteCarlo::get_params(CommonTypes::double_vector&hist, double & param, double &delta_x) {
	double arith_mean = CommonTypes::arithmeticMean<double>(hist);
	double dispersion = CommonTypes::dispersion(hist, arith_mean);
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
		iter = model_mapping.find(std::string(Model_Default));

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
    bool b = std::string(s) == Model_TreasuryBond30;
    return b;

}


#endif



