#ifndef ___BASE_HISTORY___
#define ___BASE_HISTORY___  1

#include "ModelCommon.h"
#include "BrownMotionCommon.h"

namespace MonteCarloModel {


class BaseHistoryModel: public ModelCommonDouble  {
	// core method of model
	virtual void Calculate(const double &entry,double &ret);

	//BrownMotionCommonDouble & brown_motion;
        // we don't use brown_motion but have only it's value
        // so we have all components in formulae to calculate when we call constructor

        double brown_motion_value;
	double math_param;
	double delta_x; // big trend

public:
 	// StartValue - value of simulated function in the beginning of simulation period
	//BaseHistoryModel(BrownMotionCommonDouble &brown_motion, double param, double delta_x);
	BaseHistoryModel(double brown_motion, double param, double delta_x);

	virtual ~BaseHistoryModel();


        virtual void UpdateBrownMotion(const double & brown_motion) {
            brown_motion_value = brown_motion;
        }
/*	inline long GetMathExpectation(void) const {
		return math_expectation;
	}*/
        
        virtual std::string Print(void);

};

}

#endif
