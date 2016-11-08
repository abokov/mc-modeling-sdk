#include <iostream>
#include <sstream>
#include <math.h>

#include "ModelBaseHistory.h"

namespace MonteCarloModel {

//BaseHistoryModel::BaseHistoryModel(BrownMotionCommonDouble & val_brown_motion, double param, double param2): brown_motion(val_brown_motion),
BaseHistoryModel::BaseHistoryModel(double brown_motion, double param, double param2): brown_motion_value(brown_motion),
 math_param(param),delta_x(param2) {
    if (delta_x == 0 )
        delta_x = 0.0001;
}


BaseHistoryModel::~BaseHistoryModel() {
}


// core method of model
void BaseHistoryModel::Calculate(const double &entry, double &ret) {
	double brown_val = brown_motion_value;//brown_motion.GetMovementValue(); // from 0 onto 1

	double val =   GetInitValue()* math_param * brown_val;
        double percent_sum = GetInitValue();
//        if (brown_val<0)
            for (int i=0; i<(entry/365); i++)
                percent_sum  += percent_sum * 0.06;
       	ret  = percent_sum + val + entry * 0.0001 * delta_x;
        /*std::cout<<"entry*0.0001*delta_x:" <<entry * 0.0001 * delta_x<<";"<<
        ",percent_sum:"<<percent_sum<<",val:"<<val << "\n";*/

}


std::string BaseHistoryModel::Print(void) {
	std::stringstream ss;
	ss.precision(20);
	ss.setf(std::ios::fixed,std::ios::floatfield);

	ss << " brown_motion_value : "<< brown_motion_value<<", math_param : "<<math_param<<", delta_x : "<<delta_x;


	std::string s;
	getline(ss, s,'\n');
	return s;
};

}


