#ifndef _COMMON_CLOUD_REMOTENOTIFICATIONSSERVICE_H
#define _COMMON_CLOUD_REMOTENOTIFICATIONSSERVICE_H

#include <GameLua.h>
#include "../RovioCloudManager.h"
#include <pf/RemoteNotifications.h>

class RemoteNotificationsService
{
public:
	RemoteNotificationsService(RovioCloudManager* cloudManager, GameLua* gameLua);
	virtual ~RemoteNotificationsService(RovioCloudManager* cloudManager, GameLua* gameLua);

	void setRemoteNotificationsEnabled(bool value);
private:
	virtual void initialize(); //Blank?
	virtual void onGameActivated(bool active); //Blank?
	virtual bool isAdditionalViewActive() const;
	virtual std::string getServiceName();
	virtual void onRemoteNotificationReceived(const std::string& payloadAsJSON);
	virtual void onRemoteNotificationTokenReceived(const std::string& payloadAsJSON);
	virtual void registerForNotificationService(rcs::Identity* id, bool value);

	lang::Ptr<pf::RemoteNotifications> m_remoteNotifications;
	RovioCloudManager* m_cloudManager;

	GameLua* m_gameLua;

	std::string m_remoteNotificationToken;
};

#endif