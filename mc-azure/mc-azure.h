#ifndef ___MC_AZURE__INC___
#define ___MC_AZURE__INC___  1

#include <string>
#include <map>

#include <mc-kernel/PositionProcessor.h>

#ifdef AZURE_BUILD
// false on error
bool getDataAzureBlob(const char *storage_account,const char *account_key,
    const char *container_name, const char*blob_name, PositionJobData &job);


#endif

#endif


