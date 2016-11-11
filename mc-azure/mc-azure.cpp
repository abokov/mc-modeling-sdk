
#include <iostream>
#include <map>

#include "mc-azure.h"


#ifdef AZURE_BUILD
bool getDataAzureBlob(const char *storage_account,const char *account_key,const char *container_name, 
			const char*blob_name,PositionJobData &job) {
	AzureStorageParams params;
	McAzureStorage azure_storage;

	params.account_name=storage_account;
	params.account_key=account_key;
	params.container_name=container_name
	params.blob_name=blob_name;
	
	if  (azure_storage.Init(params) == false)
			return false;
}

#endif

