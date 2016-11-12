# -- swift settings part

CXXFLAGS = -fPIC -g -O3 -Wall -fmessage-length=0 -std=c++11
CFLAGS = -Wno-address -Wno-char-subscripts # -Wno-sign-compare

#Libraries
LDFLAGS = -shared

LIBS =-lPocoUtild -lPocoUtil -lPocoXML -lPocoNet -lPocoNetd -lPocoFoundation -lPocoXMLd -lPocoFoundationd -lpthread


# -- end of swift
JAVA_DIR = ${JAVA_HOME}

# place for g++ generated binaries - object files, libs and executables
BIN_DIR = bin

#specify compiler name
CC = g++


PROJECT_DIR = $(shell pwd)
#compiler flags 
CFLAGS = -fpic -fexceptions -c $(INCLUDES) -o$@
INCLUDES = -I$(JAVA_DIR)/include -I$(JAVA_DIR)/include/linux -I$(PROJECT_DIR) -I$(PROJECT_DIR)/models
# utils dir
UTILS_DIR=xml_tools

UTILS_OBJS=$(BIN_DIR)/bxmlnode.o $(BIN_DIR)/xml_config.o

# monte carlo model dir
MC_MODEL_DIR=models

MODELOBJS = $(BIN_DIR)/RandomGeneratorSimple.o $(BIN_DIR)/ModelBaseExponent.o	$(BIN_DIR)/BrownMotionGeometric.o \
	$(BIN_DIR)/ModelBaseHistory.o

MC_KERNEL_OBJS = $(BIN_DIR)/PositionProcessor.o $(BIN_DIR)/HistoryDatabase.o $(BIN_DIR)/simulation.o $(BIN_DIR)/simulation_new.o \
	$(BIN_DIR)/PositionHistoryProcessor.o $(BIN_DIR)/hist_prices.o
	
MC_AZURE_OBJS = $(BIN_DIR)/mc-azure.o


COMMON_OBJS = $(MODELOBJS) $(UTILS_OBJS) $(BIN_DIR)/JavaInterface.o
#-----------------------------------------------------------------------------------------------------
MC_SIMULATION_EXECUTABLE = $(BIN_DIR)/mc-modeling.bin

MC_SIMULATION_OBJS_MAIN = $(BIN_DIR)/mc-modeling-cmd.o $(MODELOBJS) $(UTILS_OBJS) $(MC_KERNEL_OBJS) $(MC_AZURE_OBJS)


HIST_PRICES_LIST = $(DEMO_JNI)/data/*.inc

#----------------------------------------------------------------------------------------------------------
#-----------------------------------------  target's part -------------------------------------------------
#----------------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------

all: $(BIN_DIR) $(DEMO_GG_SHARED_LIB) $(DEMO_JNI_SHARED_LIB) $(DEMO_JNI_MAIN_BINARY) $(MC_SIMULATION_EXECUTABLE)

#create bin dir if it not exists
$(BIN_DIR):
	mkdir -p $@

#common files

#utils
$(BIN_DIR)/bxmlnode.o : $(UTILS_DIR)/bxmlnode.cpp   $(UTILS_DIR)/xml_config.h
	$(CC) $(CFLAGS) $(UTILS_DIR)/bxmlnode.cpp

$(BIN_DIR)/xml_config.o :   $(UTILS_DIR)/xml_config.cpp    $(UTILS_DIR)/xml_config.h $(UTILS_DIR)/bxmlnode.cpp
	$(CC) $(CFLAGS) $(UTILS_DIR)/xml_config.cpp


#monte carlo model's library
$(BIN_DIR)/RandomGeneratorSimple.o :	$(MC_MODEL_DIR)/RandomGeneratorSimple.cpp	$(MC_MODEL_DIR)/RandomGeneratorSimple.h	$(MC_MODEL_DIR)/RandomGeneratorCommon.h
	$(CC) $(CFLAGS) $(MC_MODEL_DIR)/RandomGeneratorSimple.cpp

$(BIN_DIR)/ModelBaseExponent.o :	$(MC_MODEL_DIR)/ModelBaseExponent.cpp $(MC_MODEL_DIR)/ModelBaseExponent.h $(MC_MODEL_DIR)/ModelCommon.h
	$(CC) $(CFLAGS) $(MC_MODEL_DIR)/ModelBaseExponent.cpp

$(BIN_DIR)/ModelBaseHistory.o :	$(MC_MODEL_DIR)/ModelBaseHistory.cpp $(MC_MODEL_DIR)/ModelBaseHistory.h $(MC_MODEL_DIR)/ModelCommon.h
	$(CC) $(CFLAGS) $(MC_MODEL_DIR)/ModelBaseHistory.cpp

$(BIN_DIR)/BrownMotionGeometric.o : $(MC_MODEL_DIR)/BrownMotionGeometric.cpp $(MC_MODEL_DIR)/BrownMotionGeometric.h $(MC_MODEL_DIR)/BrownMotionCommon.h
	$(CC) $(CFLAGS) $(MC_MODEL_DIR)/BrownMotionGeometric.cpp


#
# MC_KERNEL folder files
#
$(BIN_DIR)/PositionProcessor.o: mc-kernel/PositionProcessor.cpp      mc-kernel/PositionProcessor.h
	$(CC) $(CFLAGS) mc-kernel/PositionProcessor.cpp

$(BIN_DIR)/HistoryDatabase.o: mc-kernel/HistoryDatabase.cpp      mc-kernel/HistoryDatabase.h
	$(CC) $(CFLAGS) mc-kernel/HistoryDatabase.cpp

$(BIN_DIR)/simulation.o: mc-kernel/simulation.cpp      mc-kernel/simulation.h
	$(CC) $(CFLAGS) mc-kernel/simulation.cpp

$(BIN_DIR)/simulation_new.o: mc-kernel/simulation_new.cpp      mc-kernel/simulation_new.h
	$(CC) $(CFLAGS) mc-kernel/simulation_new.cpp

$(BIN_DIR)/PositionHistoryProcessor.o: mc-kernel/PositionHistoryProcessor.cpp      mc-kernel/PositionHistoryProcessor.h
	$(CC) $(CFLAGS) mc-kernel/PositionHistoryProcessor.cpp

$(BIN_DIR)/hist_prices.o:	mc-kernel/data/hist_prices.cpp	mc-kernel/data/hist_prices.h
	$(CC) $(CFLAGS) mc-kernel/data/hist_prices.cpp


#
# MC_AZURE folder files
#
$(BIN_DIR)/mc-azure.o: mc-azure/mc-azure.cpp      mc-azure/mc-azure.h
	$(CC) $(CFLAGS) mc-azure/mc-azure.cpp


#main binary

$(BIN_DIR)/mc-modeling-cmd.o:
	$(CC) $(CFLAGS) mc-modeling-cmd.cpp


# ------------------------------------------------------------------------------------
# make executable
cmd_line:
$(MC_SIMULATION_EXECUTABLE):    $(MC_SIMULATION_OBJS_MAIN)
	$(CC) $(MC_SIMULATION_OBJS_MAIN) -o $(MC_SIMULATION_EXECUTABLE)


# clean them all - g++ objs and binaries, generated header and compiled java classes
clean:
	rm -f $(BIN_DIR)/*
	

#copy binaries from output dir onto their proprietary location	
copy:	

	

