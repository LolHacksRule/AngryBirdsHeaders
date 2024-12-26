#ifndef _COMMON_CLOUDCONFIGURATION_H
#define _COMMON_CLOUDCONFIGURATION_H

//This is in the root of "common/source" in legacy releases.

#include "RovioCloudManager.h"
#include "../GameLua.h"
#include <lang/Ptr.h>

class CloudConfiguration
{
	typedef std::tr1::function<void ()> rcs::SkynestIdentity::LoginSuccessCallback LoginSuccessCallback; //?
	typedef std::tr1::function<void ()> rcs::SkynestIdentity::LoginFailureCallback LoginFailureCallback; //?
public:
	const time_t LOGIN_RETRY_TIME = 60;
private:
	RovioCloudManager* m_cloudManager;
	bool m_configurationLoaded;
	bool m_configurationLoading;
	time_t m_lastLoginAttempt;
	rcs::SkynestIdentity* m_skynestIdentity;
	GameLua* m_gameLua;
	lang::Ptr<rcs::Identity> m_identity;
	struct LoginCallback
	{
		LoginSuccessCallback onSuccess;
		LoginFailureCallback onError;
	};
	std::deque<CloudConfiguration::LoginCallback> m_loginCallbacks;
public:
	CloudConfiguration(RovioCloudManager* cloudManager, GameLua* gamelua, const std::string id, const std::string version, const std::string key, const std::string customer, const std::string definition);
	~CloudConfiguration();
	lang::Ptr<rcs::Identity> getIdentity();
	bool isServiceAvailable(const std::string& serviceName);
	void fetchCloudConfiguration(const std::string& serviceName);
	const ServiceConfiguration& getServiceConfiguration(const std::string& );
	bool isConfigurationLoaded();
	void setConfigurationLoaded(bool);
	bool isGuestMode();
	void getLevel2Identity() const;
	bool isLoggedIn();
	void requireLogin(LoginSuccessCallback onSuccess, LoginFailureCallback onError);
};

#endif