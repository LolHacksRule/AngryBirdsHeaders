#ifndef _ROVIOANALYTICSSERVICE_H
#define _ROVIOANALYTICSSERVICE_H

#include <GameLua.h>
#include <lua/LuaObject.h>

class AnalyticsService : private IRovioCloudService, private lua::LuaObject
{
public:
	AnalyticsService(RovioCloudManager* cloud, GameLua* gameLua);
	virtual ~AnalyticsService();
	
	void dispose(); //No code?
private:
	virtual void initialize();
	virtual void onGameActivated(bool active);
	virtual bool isAdditionalViewActive();
	virtual std:string getServiceName() const;
	
	AnalyticsService(); //?
	void startSession(); //Inline?
	void stopSession(); //Inline?
	void resetIdentity(rcs::Identity* );
	void registerLuaBindings(lua::LuaState*);
	int logEvent(lua::LuaState* lua);
	bool isLuaString(LuaState*, int);
	void onRemoteNotificationReceived(const std::string& payloadAsJSON, const std::string& serviceId, bool active);
private:
	rcs::analytics::SessionManager *m_sessionManager;
	GameLua *m_gameLua;
	
	std::set<lang::Ptr<lang::event::Link>> m_eventLinks;
};

#endif