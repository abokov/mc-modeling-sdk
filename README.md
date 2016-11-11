Processes and data modeling framework based on Monte-Carlo simulation and historical data, now on c++, multi-platform and Azure-enabled.

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



# Source code : build, run and contribute

For both builds you need to have [Azure Storage SDK C++](https://github.com/Azure/azure-storage-cpp) which based on [C++ REST SDK](https://github.com/Microsoft/cpprestsdk) prebuild and located in correct places - see CASSANDRA_PATH variable in makefile - please refer to [detailed build manual](../blob/master/docs/build. If you don't need Azure storage to be inolved into build - please use makefile with NO_AZURE setting.

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



## Run: standalone binary
## Run: from java via JNI
## Run: from your c++ code as lib


## Contribute 

# Debug
# Samples
