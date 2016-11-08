#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#ifdef _MSC_VER
	#include <process.h>
#else
	#include <unistd.h>
#endif

#include "RandomGeneratorSimple.h"

// good mix for create random init value, ref to  http://www.concentric.net/~Ttwang/tech/inthash.htm
inline unsigned long mix(unsigned long a, unsigned long b, unsigned long c)  // ;-) for inlines )
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}


RandomGeneratorSimple::RandomGeneratorSimple(long initial_value) {
#ifdef _MSC_VER
	int pid = _getpid();
#else
	int pid = getpid();
#endif
	start_seed = mix(clock(), (unsigned long)time(NULL), pid ^ initial_value );
 	srand(start_seed);
}

RandomGeneratorSimple::~RandomGeneratorSimple() {
}

void RandomGeneratorSimple::CopyObject(const RandomGeneratorCommon & val)  {
	const RandomGeneratorSimple & simple = dynamic_cast<const RandomGeneratorSimple &> (val);
	start_seed = simple.start_seed;
	srand(start_seed);
}




// returns double in range [0..val]
double RandomGeneratorSimple::GetDoubleNorm(double val) {
	if (val == 0 ) // little optimization
		return 0;
	double dbl = GetLong();
	return (double) val * ( dbl / RAND_MAX); 
	return dbl;
}


// returns int in range [0..MAXINT]
int RandomGeneratorSimple::GetInt(void)  {
#ifdef _MSC_VER
	return rand();
#else
	return random();
#endif
}

// returns long in range [0..MAXLONG]
long RandomGeneratorSimple::GetLong(void) {
#ifdef _MSC_VER
	return rand();
#else
	return random();
#endif
}


