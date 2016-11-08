#ifndef __RANDOM_GENERATOR_COMMON_INC__
#define __RANDOM_GENERATOR_COMMON_INC__ 1

class RandomGeneratorCommon {
protected:
/* i'm not sure that this class should have copy operator
	virtual void CopyObject(const RandomGeneratorCommon &) = 0;
*/
		
public:
	virtual ~RandomGeneratorCommon() {
	}


	// returns double in range [0..value]
	virtual double GetDoubleNorm(double value) = 0;

	// returns int in range [0..INTMAX]
	virtual int GetInt(void) = 0;

	// returns int in range [0..value]
	inline int GetInt(int value) {
		return value? (GetInt() % value) : 0; // in case of value == 0 returns 0
	};

	// returns long in range [0..LONGMAX]
	virtual long GetLong(void) = 0;

	// returns long in range [0..value]
	long GetLong(long value) {
		return value? (GetLong() % value) : 0; // in case of value == 0 returns 0
	};



// type conversion operators
	inline operator const int () {
		return GetInt();
	};

	inline operator const long () {
		return GetLong();
	};

};



#endif

