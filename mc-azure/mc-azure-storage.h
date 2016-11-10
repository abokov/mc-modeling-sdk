#ifndef __MC_AZURE_STORAGE_INC__
#define __MC_AZURE_STORAGE_INC__ 1


#include "was/storage_account.h"
#include "was/blob.h"
#include "cpprest/filestream.h"
#include "cpprest/containerstream.h"

namespace mc_azure {

class AzureStorageParams {
	std::string descr;
public:
	std::string account_name,account_key,container_name,blob_name,upload_file;
	const char * GetDescription(void) {
                descr = "account_name=\"" + account_name + "\"";
                descr += ",account_key=\"" + account_key + "\"";
		descr += ",container_name=\"" + container_name + "\"";
                descr += ",blob_name=\"" + blob_name + "\"";
                descr += ",upload_file=\"" + upload_file + "\"";

		return descr.c_str();
	};
	// check params for correct lentgh
	bool Validate(void) const {
		if (account_name.length()==0)
			return false;
		if (account_key.length()!=64)
			return false;
		if (container_name.length()==0)
			return false;
		if (blob_name.length()==0)
			return false;
		if (upload_file.length()==0)
			return false;
		return true;
	};
};

class McAzureStorage {

	utility::string_t storage_connection_string;
	std::string error_descr;

//     Azure storage objects
	azure::storage::cloud_storage_account storage_account;
	azure::storage::cloud_blob_client blob_client;
	azure::storage::cloud_blob_container blob_container;

public:
	McAzureStorage();
	virtual ~McAzureStorage();
	bool Init(AzureStorageParams &azure_params);

	bool SaveFileToBlob(const char *blob_name, const char *file_name, bool is_public);
	bool SaveBlobToFile(const char *blob_name, const char *file_name);

	const char * GetErrorDescription(void) { 
		return error_descr.c_str();
	};

};

}

#endif
