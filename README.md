# mc-modeling-sdk
Processes and data modeling framework based on Monte-Carlo simulation and historical data, now on c++, multi-platform and Azure-enabled

# How does it work

Monte Carlo simulation performs risk analysis by building models of possible results by substituting a range of values—a probability distribution—for any factor that has inherent uncertainty. It then calculates results over and over, each time using a different set of random values from the probability functions. Depending upon the number of uncertainties and the ranges specified for them, a Monte Carlo simulation could involve thousands or tens of thousands of recalculations before it is complete.
Using this SDK you can Monte-Carlo simulation on requires number of recalculations and use customuzed type of random generation model. From practical point of view you can use it as using [MonteCarlo class](../master/mc-kernel/simulation.h), [stand-alone binary](../master/docs/standalone.md) or call it from [java via JNI](../master/demo_jni)

# Configure and customize

First of all common overview of modeling process which implemented in this SDK - we do create 'PositionJobData' object (is litellaly list of data-arrays which will be used to modeling ), pass that object into 'runMonteCarlo' method who do run cycles and modeling. On each cycle of modeling we need to get some kind of random numbers and to get these numbers we can use different models - simplest one ( and used by default ) is [plain random generaton](../master/models/RandomGeneratorSimple.cpp). It use standart rand() function to get random value and initiate set pseudo-random sequence ( so it's not_a_really_random thing here!) with mixing current date, time and initial value.

Current implementation of SDK are targeted to modeling stocks and bonds, to there's a 'horizon' for modeling and we treat that horizon in days. Also we do separate bank accounts and stocks - main difference between them is how do we calculate units - bank accounts is about keeping money is USD (for example), but stocks is one bond which may costs some USD. Before run modeling we took a historical data from pre-sets - see [TreasureBond enum](../master/mc-kernel/data/hist_prices.h) - current implementation use 'StockOptions::TreasureBond' in case of bank account ( this one may be not always correct assumption ).
So then we go to first cycle - for required amount of iterations we do simulation for each portfolio element and get next value for simulatation as average from previous value and new one ( looks like linear approach, but actually this more related to derivative of function which is line for x^2 class of methods ). Getting new numbers for simulation (another important part) is implemented inside UpdateBrownMotionValues() method - it use 


There's several options to setting up SDK - first of all there's entry data-sets which should be used as entry data for simulation, second thing is implementation of model for random generator which can be used fo

##
##

# build linux
# build windows
--tbd-

# Run
## On Azure
## On your own environment
## GCE

# Debug
# Samples
