#ifndef __RANDOM_GENERATOR_SIMPLE_INC__
#define __RANDOM_GENERATOR_SIMPLE_INC__ 1

#include "RandomGeneratorCommon.h"

class RandomGeneratorSimple: public RandomGeneratorCommon {
	unsigned long start_seed;
protected:
	virtual void CopyObject(const RandomGeneratorCommon &);

public:
 	RandomGeneratorSimple(long initial_value=0); // this value will be mixed xor-ed (^) with clock(), time() and getpid()

	virtual ~RandomGeneratorSimple();
	
	// returns double in range [0..val]
	virtual double GetDoubleNorm(double val);

	// returns int in range [0..MAXINT]
	virtual int GetInt(void);

	// returns long in range [0..MAXLONG]
	virtual long GetLong(void);
};



#endif

