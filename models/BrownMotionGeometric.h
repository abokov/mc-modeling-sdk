
#ifndef __BROWN_MOTION_GEOMETRIC_INC___
#define __BROWN_MOTION_GEOMETRIC_INC___ 1

#include "BrownMotionCommon.h"
#include "RandomGeneratorCommon.h"

const double DEFAULT_NORM_COEFF = 2.0 ;
const double DEFAULT_DISTR_WIDE = 0.5;


// actually implements  :  norm_coeff*( norm_rand() -  dist_wide());
// where norm_rand() returns randomise in range [0..dist_wide]
class BrownMotionGeometric: public BrownMotionCommonDouble {
	RandomGeneratorCommon & random_generator;

	double norm_coeff;
       	double dist_wide;
public:
	// constructor takes RandomGenerator and coeff for calculations, 
	BrownMotionGeometric(RandomGeneratorCommon & random_generator, double norm_coeff = DEFAULT_NORM_COEFF, double dist_wide = DEFAULT_DISTR_WIDE);
	
	virtual	~BrownMotionGeometric();

	virtual double GetMovementValue(void);
};

#endif

