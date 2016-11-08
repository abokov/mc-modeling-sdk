#ifndef ___BASE_EXPONENT__INC___
#define ___BASE_EXPONENT__INC___  1

#include "ModelCommon.h"
#include "BrownMotionCommon.h"

namespace MonteCarloModel {


class BaseExponentModel: public ModelCommonDouble  {
	// core method of model
	virtual void Calculate(const double &entry,double &ret);

	static const double DefaultMua;
	static const long DefaultBetaA = 1;

	BrownMotionCommonDouble & brown_motion;

	long mua;
	long beta_a;

public:

 	// StartValue - value of simulated function in the beginning of simulation period
	BaseExponentModel(BrownMotionCommonDouble &brown_motion, long mua = BaseExponentModel::DefaultMua, long beta_a =  BaseExponentModel::DefaultBetaA);

	virtual ~BaseExponentModel();


	inline long GetMua(void) const {
		return mua;
	}

	inline long GetBetaA(void) const {
		return beta_a;
	}
};

}

#endif
