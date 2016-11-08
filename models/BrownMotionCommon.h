
#ifndef __BROWN_MOTION_COMMON_INC___
#define __BROWN_MOTION_COMMON_INC___ 1

template <class MotionValueClass> class BrownMotionCommomTemplate {
public:
	virtual ~BrownMotionCommomTemplate() {
	}
	
	virtual MotionValueClass GetMovementValue(void) = 0;
};

typedef BrownMotionCommomTemplate<double> BrownMotionCommonDouble;



#endif

