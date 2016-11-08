#include <iostream>
#include <math.h>

#include "ModelBaseExponent.h"

namespace MonteCarloModel {

const double BaseExponentModel::DefaultMua = 0.501;


BaseExponentModel::BaseExponentModel(BrownMotionCommonDouble & val_brown_motion, 
	long val_mua, long val_beta_a): brown_motion(val_brown_motion), mua(val_mua), beta_a(val_beta_a) {
}


BaseExponentModel::~BaseExponentModel() {
}


// core method of model
void BaseExponentModel::Calculate(const double &entry, double &ret) {
// f(t) = f(0) * exp( (mua- beta_a^2/2)*t  + beta_a * BROWN_MOTION(t) )
	double brown_val = brown_motion.GetMovementValue();
	double val =  (mua - (beta_a *beta_a/2) ) * entry + beta_a * brown_val;
	double val2 =  exp( val);
	ret  = GetInitValue() * val2;
}



};


