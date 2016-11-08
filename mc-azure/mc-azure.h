#ifndef ___MC_AZURE__INC___
#define ___MC_AZURE__INC___  1

#include <string>
#include <map>

#include <mc-kernel/PositionProcessor.h>


void getDataAzureBlob(const char *storage_account,const char*blob_name, PositionJobData &job);


#endif


