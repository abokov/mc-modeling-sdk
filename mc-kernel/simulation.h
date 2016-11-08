
#ifndef ___SIMULATION__INC___
#define ___SIMULATION__INC___  1

#include <string>
#include <map>

#include <RandomGeneratorSimple.h>
#include <ModelBaseHistory.h>
#include <BrownMotionGeometric.h>
#include <ModelCommon.h>

#include "mc-common/mc-base-types.h"

#include "PositionProcessor.h"


class MonteCarlo {
        RandomGeneratorSimple random_generator;
        BrownMotionGeometric brown_motion;

	typedef std::map<std::string, MonteCarloModel::ModelCommonDouble*> ModelMappingMap;
	ModelMappingMap model_mapping;

	void get_params(BaseTypes::double_vector&, double & param, double &delta_x);
	void get_delta_x(BaseTypes::double_vector&hist, double & delta_x);

	void init_models();

public:
	MonteCarlo(void);
	~MonteCarlo();

	void runMonteCarlo(PositionJobData &job);

    void UpdateBrownMotionValues(void);

	// model depends on position's name
	MonteCarloModel::ModelCommonDouble * GetModel(const char *);

	void PrintAll(void);

	// use perc_accumulated
	bool IsPositionBankAccount(const char *);

	void AddModel(const char *stock_name,BaseTypes::double_vector &history);
};

void runMonteCarlo(PositionJobData &job);// just run 	monte_carlo.runMonteCarlo(job);

MonteCarlo * getMonteCarlo(void);


#endif


