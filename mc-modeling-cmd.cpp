
#include <iostream>


#include <mc-kernel/PositionProcessor.h>
#include <mc-azure/mc-azure.h>

#include "xml_tools/xml_config.h"


void usage(void);

int main( int argc, const char* argv[] ) {
    if (argc != 3 ) {
        usage();
        return 1;
    }

	// get configuration from config file
    BaseTypes::SimulationTask task;
	XmlConfigFile xml_config(argv[1], task);
	xml_config.Read();

    PositionJobData jobData(task);

	if (argv[2] ==  "-azure") {
		getDataAzureBlob(argv[3],argv[4],jobData);
	} else if (argv[2] == "--local") {
//		get_azure_data(PositionJobData,argv[3],argv[4])
		// get data from CSV
	} else {
		usage();
		return 1;
	}

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
	"Usage: mc-modeling-cmd config_file.xml [-azure storage_account blob_name]|[-local input_file]\n"
	" Azure mode: upload historical data from azure storage account, output will be in stdout\n"
	"   example:  mc-modeling-cmd config_file.xml -azure TestAccount  NASDAQ_DATA\n"
	" Local (standalone) mode: upload date from local file ( run locally ), output will be in stdout\n"
	"   example:  mc-modeling-cmd config_file.xml -local /home/user/my_data.csv"
	<<std::endl;
}