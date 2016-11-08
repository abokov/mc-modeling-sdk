#include <iostream>
#include "BrownMotionGeometric.h"

// constructor takes RandomGenerator and coeff for calculations, 
BrownMotionGeometric::BrownMotionGeometric(RandomGeneratorCommon & val_random_generator, double val_norm_coeff, double val_dist_wide) :
		random_generator(val_random_generator), norm_coeff (val_norm_coeff), dist_wide (val_dist_wide) { 

}

BrownMotionGeometric::~BrownMotionGeometric() {

}

// actually implements  :  norm_coeff*( norm_rand() -  dist_wide());
double BrownMotionGeometric::GetMovementValue(void) {
	double rnd_val = random_generator.GetDoubleNorm(dist_wide*2);
	double ret = norm_coeff * (rnd_val -dist_wide);
	return ret;

}

