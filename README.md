Processesing and data modeling C++ framework based on Monte-Carlo simulation and historical data.

# How does it work

## Basic theory

Monte Carlo simulation performs risk analysis by building models of possible results by substituting a range of values—a probability distribution—for any factor that has inherent uncertainty. It then calculates results over and over, each time using a different set of random values from the probability functions. Depending upon the number of uncertainties and the ranges specified for them, a Monte Carlo simulation could involve thousands or tens of thousands of recalculations before it is complete.
Using this SDK you can Monte-Carlo simulation on requires number of recalculations and use customuzed type of random generation model. From practical point of view you can use it as using [MonteCarlo class](../master/mc-kernel/simulation.h), [stand-alone binary](../master/docs/standalone.md) or call it from [java via JNI](../master/demo_jni)

## Implementation and design

First of all common overview of modeling process which implemented in this SDK - we do create 'PositionJobData' object (is litellaly list of data-arrays which will be used to modeling ), pass that object into 'runMonteCarlo' method who do run cycles and modeling. On each cycle of modeling we need to get some kind of random numbers and to get these numbers we can use different models - simplest one ( and used by default ) is [plain random generaton](../master/models/RandomGeneratorSimple.cpp). It use standart rand() function to get random value and initiate set pseudo-random sequence ( so it's not_a_really_random thing here!) with mixing current date, time and initial value.

Current implementation of SDK are targeted to modeling stocks and bonds, to there's a 'horizon' for modeling and we treat that horizon in years. Also we do separate bank accounts and stocks - main difference between them is how do we calculate units - bank accounts is about keeping money is USD (for example), but stocks is one bond which may costs some USD. Before run modeling we took a historical data from pre-sets - see [TreasureBond enum](../master/mc-kernel/data/hist_prices.h) - current implementation use 'StockOptions::TreasureBond' in case of bank account ( this one may be not always correct assumption ).

So then we go to first cycle - for required amount of iterations we do simulation for each portfolio element and get next value for simulatation as average from previous value and new one ( looks like linear approach, but actually this more related to derivative of function which is line for x^2 class of methods ). Getting new numbers for simulation (another important part) is implemented inside UpdateBrownMotionValues() method - it uses on the end [BrownMotionGeometric::GetMovementValue()](../master/models/BrownMotionGeometric.cpp) which called somewhere to standart random() method. In case if you're not happy with that random() - you need just change [RandomGeneratorSimple::GetInt/Double() methods](../master/models/RandomGeneratorSimple.cpp).
In that first cycle for Bonds we do simulation and set values, and only do simulation (get simulated value ) for Bank Account.

In second cycle we do simulation for percent of money changes in that account and to do that we do calculations which I describe above, but then we do another cycle going through all bank account (in the same simulation cycle ) to set this percent change. So for each Monte Carlo iteration we do cycle for each portfolio element inside as well ( portfolio contains array of Bank Account or Bonds ). Note: for Bonds we just run another time BrownMotionSimulation.

Then we go to last cycles - third cycle is only for bank accounts we need to know how much money overall do we have in that account and 4th cycle is to calculated numbers in correct measured units.

## Threads

Existing implementation in _'master'_ branch are not using any thread pools, so you can easily embed that in any single thread and run via thread pool or use other parallelization techniques. Please be aware of fact that inside SDK we use std:: a lot, and in case of AZURE_SDK build we use Azure Storage SDK which based on C++ REST SDK - last one already support async, so be informed - [C++ REST SDK: asynchronous tasks vs. C++11 multithreading](http://stackoverflow.com/questions/36338032/c-rest-sdk-asynchronous-tasks-vs-c11-multithreading).
So currently all code run as plain thing in one thread ( if not AZURE_SDK who do async web api calls ) - this decision made by experience and practical scenarios, especially when running SDK in cloud environment. Multi-thread/async running _migt_ bring not so linear/plain performance estimation, and having evetything in one thread it makes things simplier.

But in some scenarios ( when SDK using as part of computational back-end for multi-tenant applicion ) this may brings unefficient usage of computational resources and increase costs of ownership - for that purpose I started branch _'dev-thread-pool'_

# Source code : build, run and contribute

For both builds you need to have [Azure Storage SDK C++](https://github.com/Azure/azure-storage-cpp) which based on [C++ REST SDK](https://github.com/Microsoft/cpprestsdk) prebuild and located in correct places - see below
```
AZURE_STORAGE_SDK = ${AZURE_STORAGE_SDK}
REST_API_SDK = ${REST_API_SDK}
```
Please refer to complete build process description in [detailed build manual](../blob/master/docs/build). To build with Azure SDK usage please set 'AZURE_SDK' environment variable during build time, by defaul it not set.

## build linux

Current process is pretty simple - it's enough to make command
```
make
```
All binaries are located under bin folder and executable file is _mc-modeling.bin_
Note: there's some issues with running standalone binary on some linux flavours, I checked it on 64bits Ubuntu16.04, but I got feedback about issues on another linux-es/.

## build windows
_to be done_
I'm working on that - see [Add windows build](../issues/1)

## Contribute 
There's 3 branches at this momemt:
* master - where we keep more-less stable release ( it might not include all features, but works somehow ).
* dev-trunk-azure - where we keep azure related dev branch
* open-stack  - integration with Swift storage

# Input data

Entry data format is XML (or xml like if you want ) - it describes two types of elements which may exists in portfolio - stocks - which related to stock options and bonds, which are bank accounts - as it described below they treated differently during simulation.
```
<xml>
<simulation_data>


<horizon years="1" month="2" days="3">
</horizon>
           
<portfolio>
         <element name="IBM" type="stock" amount="100"/>
         <element name="Oracle" type="bond" amount="200">
           <history>
                <data="213"/>
                <data="333">
           </history>     
         </element>
         <element name="Mr.Lee" type="bond" amount="200"/>
         
</portfolio>         
         
         
 </xml>
```
Note: actually SDK do not check for XML syntax, so it might happened that syntax-wrong XML-like file will be okay for SDK, adding syntax check will increase complexity of codebase without any benefits.


# Usage (as framework )

Entry point for framework is class [_MonteCarlo_](https://github.com/abokov/mc-modeling-sdk/blob/master/mc-kernel/simulation.h)
```
MonteCarlo::runMonteCarlo(PositionJobData &job);
```
where PositionJobData is actually keep array (std::vector - see [Bjarne Stroustrup: C++11 Style](https://channel9.msdn.com/Events/GoingNative/GoingNative-2012/Keynote-Bjarne-Stroustrup-Cpp11-Style) - so here you need to initialize horizon (in days!) and number of iterations (int, remember MAX_INT number!) via corresponding setters inside PositionJobData class. 
```
PositionVector portfolio;
int horizon;
int iters;
```
Data (i.e. portfolio itself ) contained in poftofolio which is std::vector
```
typedef std::vector<PositionData> PositionVector;
```
Then PositionData class is actually related to each entity of portfolio:
```
std::string name, type;
double units, amount, simulatedValue;
double price;
double perc_accumulated;
double perc_accumulated_sum;
bool is_bank_account;
```

where name is name ("Oracle"), type is type("bond" or "stock"), units and amount are should be set before simulation.
During simulation SDK setup these fields:  _simulatedValue_,  _price_, _perc_accumulated_ and _perc_accumulated_sum_.
Flag is_bank_account is RFU.

You can set PositionJobData by yourself from required data source ( now we support local file, azure blob file, and in future open stack swift storage ), but inside that SDK we have helpers which might help you with that.

## Reading data from XML

Inside [xml_tools](https://github.com/abokov/mc-modeling-sdk/blob/master/xml_tools/) you may find xml_config.h contains class _XmlConfigFile_
lass XmlConfigFile {
	std::string cfg_file;
	BaseTypes::SimulationTask task; 
public:
	XmlConfigFile(const char *config_file, BaseTypes::SimulationTask &my_task);
	~XmlConfigFile();

	void Init(const char *config_file, BaseTypes::SimulationTask &my_task);

	bool Read(void);

};


# Usage ( command line )

note: very beta, some bugs may exists, thanks!
By xml file here we means Input data file format which desrcibed before. If you set hotizon and iteration number in command line it overrides settings in xml file.

```
Usage: mc-modeling-cmd config_file.xml [-azure storage_account blob_name]|[-local input_file] -iterations number\n"
	Azure mode: upload historical data from azure storage account, output will be in stdout\n"
            Please use params in order from below, change order not supported yet\n"
	  example:  mc-modeling-cmd config_file.xml -azure TestAccount  NASDAQ_DATA  -iterations 10000000 -horizon 20\n"
	" Local (standalone) mode: upload date from local file ( run locally ), output will be in stdout\n"
	"   example:  mc-modeling-cmd config_file.xml -local /home/user/my_data.csv -iterations 10000000 -horizon 10" 
```
