#include <sstream>
#include <iostream>

#include "mc-common/mc-base-types.h"


#include "PositionProcessor.h"
#include "simulation.h"
#include "data/hist_prices.h"


PositionJobData::PositionJobData(BaseTypes::SimulationTask &task) {
	BaseTypes::SimulationTask::map_portfolio::const_iterator iter = task.elements.begin(),
		end = task.elements.end();

	horizon = task.horizon;
// TODO
	iters = 100;

	while (iter != end) {
		PositionData position_data;
		double last_price = 0;
		if (iter->second.history.size() != 0 )
			last_price = iter->second.history[iter->second.history.size()-1];
		position_data.Init(iter->first, "bond", iter->second.amount, 0,
			last_price, false, 0, 0 );
		portfolio.push_back(position_data);

		++iter;
	}

}


void PositionData::CopyObject(const PositionData& val) {
	name = val.name;
	type = val.type;
	units = val.units;
	amount =  val.amount;
	simulatedValue = val.simulatedValue;
        is_bank_account = val.is_bank_account;
        perc_accumulated = val.perc_accumulated;
        perc_accumulated_sum = val.perc_accumulated_sum;
}

std::string PositionData::PrintToString(void) {
	std::stringstream ss;
	ss.precision(20);
	ss.setf(std::ios::fixed,std::ios::floatfield); 

	ss << " name : " << name << ", type : "<<  type << ", units : " << units << " amount : " << amount << 
                " simulatedValue : " << simulatedValue <<
                " is_bank_account : "<< is_bank_account <<
                " perc_accumulated : "<<perc_accumulated <<
                " perc_accumulated_sum : "<<perc_accumulated_sum;

	std::string s;
	getline(ss, s,'\n');
	return s;
}

//----------------------------------------------------------------------------------------------------------------------------------



void PositionJobData::CopyObject(const PositionJobData& val) {
	portfolio = val.portfolio;
	horizon = val.horizon;
	iters = val.iters;
}

std::string PositionJobData::PrintToString(void) {
	std::stringstream ss;
	ss.precision(20);
	ss.setf(std::ios::fixed,std::ios::floatfield); 

	ss << "horizon : " << horizon << ", iters : " << iters << " portfolio.size() : " << portfolio.size();

	std::string s;
	getline(ss, s,'\n');
	return s;
}


//---------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------




PositionProcessor::PositionProcessor(PositionJobData &val):job_data(val) {

}



PositionProcessor::~PositionProcessor() {
}


// this is all because we do a = (a+a1)/2 recursively!
double not_really_arithmetic_mean(BaseTypes::double_vector &vec) {
    BaseTypes::double_vector::const_iterator iter = vec.begin(), end = vec.end();
    double val = *iter;
    ++iter;
    while (iter != end) {
        val =  (val + (*iter))/2;
        ++iter;
    }
    return val;
}

void PositionProcessor::Process(void) {
	// do something...
	PositionVector &portfolio = job_data.GetPortfolioPtr();

	int port_size = portfolio.size();
	int iters_size = job_data.GetIters();
	MonteCarlo * monte_carlo = getMonteCarlo();


	long horizon_in_days = job_data.GetHorizon() * 365;

	// little optimization
	// do pre-set value fo Bank Accounts
	for (int i=0; i < port_size ; i++) {
		if (monte_carlo->IsPositionBankAccount(portfolio[i].GetType())) {
			// note: it might be not always correct assumpution to use TreasureBond type (and hist data) for Bank Accounts
				BaseTypes::double_vector & hist = StockOptions::GetHistory(StockOptions::TreasureBond);
				double val = hist[hist.size()-1];
				portfolio[i].SetIsBankAccount(true);
				portfolio[i].SetPercentAccumulated(val);
		}; // if (monte_carlo->IsPositionBankAccount(portfolio[i].GetType())) {
		if (portfolio[i].GetUnits())
			portfolio[i].SetPrice (portfolio[i].GetAmount()/portfolio[i].GetUnits());
		else
			portfolio[i].SetPrice(portfolio[i].GetAmount());
	}// for (int i=0; i < port_size ; i++) {


// First cycle
// make modeling 'iters_size'' times for each portfolio element
	for (int j=0; j<iters_size; j++) {
        	for (int i=0; i < port_size ; i++) 
			if (portfolio[i].GetIsBankAccount() == false) { // so do it for Bonds!
						//price = amount/units
           				MonteCarloModel::ModelCommonDouble * monte_carlo_model = monte_carlo->GetModel(portfolio[i].GetType());
						double price =  portfolio[i].GetPrice();

						monte_carlo_model->SetInitValue(price);
						double val = monte_carlo_model->GetModelValue(horizon_in_days);
						double sim_value = portfolio[i].GetSimulatedValue();
                        if ( j != 0 )
                            sim_value = (val+sim_value)/2;
                        else
                            sim_value = val; // first pass
                        portfolio[i].SetSimulatedValue(sim_value);
			} // for (int i=0; i < port_size ; i++) 
			monte_carlo->UpdateBrownMotionValues(); // You can change your model inside that method, by BrownMotion looks very logical here
	} // for (int j=0; j<iters_size; j++) {


// Second cycle 
#ifdef _DBG_OUTPUT_
	std::cout<<" job_data.GetHorizon() : " << job_data.GetHorizon()<<"\n";
#endif
	for (int year = 1 ; year <= job_data.GetHorizon(); year ++ ) {
                for (int j=0; j<iters_size; j++) {
                    for (int i=0; i < port_size ; i++)  
						if (portfolio[i].GetIsBankAccount()) { 
                            MonteCarloModel::ModelCommonDouble * monte_carlo_model = monte_carlo->GetModel(portfolio[i].GetType());
                            double price =  portfolio[i].GetPercentAccumulated();
                            monte_carlo_model->SetInitValue(price);
                            double val = monte_carlo_model->GetModelValue(365);
                            double sim_value = portfolio[i].GetSimulatedValue();
                            if ( j != 0 )
                                sim_value = (val+sim_value)/2;
                            else
                                sim_value = val; // first pass
                            portfolio[i].SetSimulatedValue(sim_value);
                    	} // if (portfolio[i].GetIsBankAccount()) {
                    monte_carlo->UpdateBrownMotionValues();
                } // for (int j=0; j<iters_size; j++) {

                // we got percent for one year.
                for (int i=0; i < port_size ; i++)  //  for Bank account we do simulate for year percent
					 if (portfolio[i].GetIsBankAccount()) {
                    	double perc_sim = portfolio[i].GetSimulatedValue();
                    	//or this one? too simple! =>   portfolio[i].SetPercentAccumulated(perc_sim);
                    	if (year == 1) {
                            portfolio[i].SetPercentAccumulatedSum(1 + (perc_sim/100) );
                    	} else {
                            double val = portfolio[i].GetPercentAccumulatedSum();
                            portfolio[i].SetPercentAccumulatedSum(val * (1+ (perc_sim/100) )) ;
                    	}
#ifdef _DBG_OUTPUT_					
                    	std::cout<< "portfolio[i].GetPercentAccumulatedSum() :" <<portfolio[i].GetPercentAccumulatedSum()<<"\n";
                    	std::cout<< " perc_sim:" <<perc_sim<<"\n";
#endif
                	}// if (portfolio[i].GetIsBankAccount()) {
#ifdef _DBG_OUTPUT_					
               std::cout<< "\n-------------------\n";
#endif			   

        }; // for (int year = 1 ; year < job_data.GetHorizon(); year ++ ) {


// third cycle
	for (int i=0; i < port_size ; i++) // for Bank Accounts get grand total overall of all money on each account 
	 	if (portfolio[i].GetIsBankAccount()) {
			double price =  portfolio[i].GetPrice();
			double perc =  portfolio[i].GetPercentAccumulatedSum();
#ifdef _DBG_OUTPUT_					
			std::cout<<" price before : "<<price<<", perc : "<<perc;
#endif		
			price = price * perc;
			portfolio[i].SetSimulatedValue(price);
#ifdef _DBG_OUTPUT_					
			std::cout<<", after : "<<price<<"\n";
#endif		
		} // if (portfolio[i].GetIsBankAccount()) {
		

// fourth cycle
	for (int i=0; i < port_size ; i++) {
		double val2 = portfolio[i].GetSimulatedValue() * portfolio[i].GetUnits();
		portfolio[i].SetSimulatedValue(val2);
	} 
}






