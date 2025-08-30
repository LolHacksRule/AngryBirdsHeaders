#ifndef _COMMON_CLOUD_ROVIOCLOUDMANAGER_H
#define _COMMON_CLOUD_ROVIOCLOUDMANAGER_H

#include "cloud/Payment/CloudPayment.hpp"

class RovioCloudManager :
	public lang::Object
{
public:
	const lang::Event<void(const std::string&, const std::string&, bool)> EVENT_ON_REMOTE_NOTIFICATION_RECEIVED; //?
	const lang::Event<void(lang::Ptr<rcs::RovioIdentity>)> EVENT_ON_ROVIO_ACCOUNT_ACTIVATED; //?
	const lang::Event<void(const std::string&, const std::string&)> EVENT_ON_ROVIO_ACCOUNT_LOGGED_IN; //?
	RovioCloudManager(GameLua* gameLua, game::Resources* resources, const std::string& audioPath, std::vector<unsigned char, std::allocator<unsigned char> > const&, lua::LuaState* lua, std::string customerString);
	virtual ~RovioCloudManager();
	
	void initialize();
	void update();
	void refresh() { m_hasFetchedConfiguration = false; }
	void activate();
	bool additionalViewsActive();
	
	std::tr1::shared_ptr<CloudConfiguration> getConfiguration();
	
	template <class T>
	std::tr1::weak_ptr<T> getServiceOfType<T>();
	void registerService<T>(std::tr1::shared_ptr<IRovioCloudService> service);
	
	CloudPayment& payment();
private:
	GameLua* m_gameLua;
	CloudPayment* m_cloudPayment;
	std::tr1::shared_ptr<CloudConfiguration> m_cloudConfiguration;
	bool m_hasFetchedConfiguration;
	std::map<std::string, std::tr1::shared_ptr<IRovioCloudService>> m_services;
	std::set<lang::Ptr<lang::event::Link>> m_eventLinks;
};

#endif