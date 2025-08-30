#ifndef _COMMON_CLOUD_ROVIOACCOUNT_CLOUDSYNC_H
#define _COMMON_CLOUD_ROVIOACCOUNT_CLOUDSYNC_H

#include <external/CloudServicesNativeSDK/cloud/core/Identity.h>

class GameLua;

class CloudSync : public lang::Object
{
public:
	CloudSync(GameLua*, rcs::Identity*);
	virtual ~CloudSync();
	
	void setKeys(const std::string&, const std::string&, const std::string&);
	void setIdentity(rcs::RovioIdentity*);
	
	void setRequestTimeout(int);
	
	bool cloudSaveValue(const std::string&, io::ByteArrayOutputStream&);
	bool cloudLoadValue(const std::string&);
	std::string getLoadedValue(const std::string&);
	
	bool hasFailed();
	void clearState();
	int getErrorId();
	bool isReady();
private:
	std::string m_version;
	std::string m_id;
	std::string m_key;
	
	GameLua* m_gameLua;
	
	rcs::Identity* m_deviceIdentity;
	rcs::StorageService* m_storageService;
};

#endif