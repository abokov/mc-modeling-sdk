#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>

#include <core/PositionProcessor.h>
#include <core/simulation.h>


//#define DBG_FILE 1

#undef DBG_FILE

void init_job_data(std::string &ss, PositionJobData &job_data);

void init_position(std::string &s, PositionData &position);

#ifdef DBG_FILE
	std::ofstream dbgFile;
#endif

int main(void) {
try { 

#ifdef DBG_FILE
	char buffer[1024];
	tmpnam(buffer);

	dbgFile.open(buffer, std::ios::out);
 	dbgFile<<buffer<<std::endl;
#endif

	std::string my_str;
	PositionJobData jobData;


// get "5000 365 10000"
// it means "[horizon=5000, iters=365, portfolio.size()=10000"
	getline(std::cin, my_str, '\n');

#ifdef DBG_FILE
   	dbgFile << my_str << std::endl;
   	dbgFile.flush();
#endif

	init_job_data(my_str, jobData);

#ifdef DBG_FILE
   	dbgFile << jobData.PrintToString() << std::endl;
   	dbgFile.flush();
#endif


	PositionVector &vec = jobData.GetPortfolioPtr();
	for (int i=0; i<vec.size(); i++) {
		getline(std::cin, my_str, '\n');
		init_position(my_str, vec[i]);
#ifdef DBG_FILE
   	dbgFile << my_str << std::endl;
   	dbgFile << vec[i].PrintToString() << std::endl;
   	dbgFile.flush();
#endif
	}

	runMonteCarlo(jobData);


 	vec = jobData.GetPortfolioPtr();
	for (int i=0; i<vec.size(); i++) 
		std::cout<<vec[i].GetSimulatedValue()<<std::endl;
} catch (std::bad_alloc &mem )  {
	printf("Run time error ( bad_alloc ) :  exception : %s\n", mem.what());
} catch (std::exception& exc) {
	printf("Run time error : calculateCreditRiskMonteCarlo exception : %s\n", exc.what());
} catch (...) {
	printf("Run time error : calculateCreditRiskMonteCarlo unknown exception\n");
};

return 0;
}


void init_job_data(std::string &s, PositionJobData &jobData) {
	std::stringstream ss (s);
	ss.precision(20);

// get "5000 365 10000"
// it means "[horizon=5000, iters=365, portfolio.size()=10000"

	int horizon, iters, size;

	ss >> horizon >> iters >> size;

	jobData.SetHorizon(horizon);
	jobData.SetIters(iters);

	PositionVector &vec = jobData.GetPortfolioPtr();
	//!! sic
	vec.resize(size);
}

void init_position(std::string &s, PositionData &position) {
	std::stringstream ss(s);
	ss.precision(20);

// java wrote :
//        buf.append(getName()).append(" ");
//        buf.append(getType()).append(" ");
//        buf.append(getUnits()).append(" ");
//        buf.append(getAmount()).append(" ");
//        buf.append(getSimulatedValue()).append(" ");

	std::string name, type;
	// its because java prints all int as "049494.0"
	double d_units, d_amount, d_simulated_value;
	
	ss >> name >> type >> d_units >> d_amount >> d_simulated_value;

	position.SetName(name);
	position.SetType(type);
	position.SetUnits(d_units);
	position.SetAmount(d_amount);
	position.SetSimulatedValue(d_simulated_value);


};





