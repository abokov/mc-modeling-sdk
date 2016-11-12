
#include <iostream>


#include <mc-kernel/PositionProcessor.h>
#include <mc-azure/mc-azure.h>

#include "xml_tools/xml_config.h"


void usage(void);

int main( int argc, const char* argv[] ) {
    if (argc != 4) {
        usage();
        return 1;
    }

	// get configuration from config file
    BaseTypes::SimulationTask task;
	XmlConfigFile xml_config(argv[1], task);
	xml_config.Read();

    PositionJobData jobData(task);

	if (argv[2] ==  "-azure") {
#ifdef AZURE_BUILD
		getDataAzureBlob(argv[3],argv[4],jobData);
#else
		std::cout<<" error: Wrong build of binary - AZURE_BUILD should be defined on build time!"<<std::endl;
#endif		
	} else if (argv[2] == "--local") {
		get_azure_data(jobData,argv[3],argv[4])
		// get data from CSV
	} else {
		usage();
		return 1;
	}
	if (argv[3] == "--iterations") {
		int num = std::stoi( argv[4] );
		jobData.SetIters(num);
	} else {
		usage();
		return 1;
	};

	if (argv[5] == "--horizon") {
		int num = std::stoi( argv[6] );
		jobData.SetHorizon(num);
	} else {
		usage();
		return 1;
	};

    // put data into processing class
	PositionProcessor processor(jobData);
	// do run simulation
	processor.Process();


	// Run simulation and print to std::out
	PositionVector &my_portfolio = jobData.GetPortfolioPtr();

	for (int i=0; i < my_portfolio.size() ; i++) 
		std::cout << my_portfolio[i].PrintToString() << std::endl;
	
};


void usage(void) {
    std::cout<<
	"Usage: mc-modeling-cmd config_file.xml [-azure storage_account blob_name]|[-local input_file] -iterations number\n"
	" Azure mode: upload historical data from azure storage account, output will be in stdout\n"
	" Please use params in order from below, change order not supported yet\n"
	"   example:  mc-modeling-cmd config_file.xml -azure TestAccount  NASDAQ_DATA  -iterations 10000000 -horizon 20\n"
	" Local (standalone) mode: upload date from local file ( run locally ), output will be in stdout\n"
	"   example:  mc-modeling-cmd config_file.xml -local /home/user/my_data.csv -iterations 10000000 -horizon 10" 
	<<std::endl;
}
