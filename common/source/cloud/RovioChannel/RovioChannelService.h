#ifndef _COMMON_CLOUD_ROVIOCHANNELSERVICE_H
#define _COMMON_CLOUD_ROVIOCHANNELSERVICE_H

#include <CloudServicesNativeSDK/include/channel/ChannelUtils.h>
#include <lua/LuaObject.h>

class IRovioCloudService;

class RovioChannelService : lua::LuaObject, IRovioCloudService, private channel::ChannelListener
{
public:
	RovioChannelService(std::tr1::shared_ptr<CloudConfiguration> cloudConfiguration, lua::LuaState* lua, game::Resources* resources, const std::string& audioPath, const std::vector<uchar>& encryptionKey);
	virtual ~RovioChannelService();
private:
	lang::Ptr<channel::channel> m_channel;
	std::tr1::shared_ptr<CloudConfiguration> m_cloudConfiguration;
	game::Resources *m_resources;
	std::string m_audioPath;
	std::vector<unsigned char> m_encryptionKey;
	std::set<lang::Ptr<lang::event::Link>> m_eventLinks; //?

	void callLoadFromUrl(const std::string& url, int width, int height);
private:
	RovioChannelService(const RovioChannelService&);
	RovioChannelService& operator=(const RovioChannelService&);

	virtual void initialize();
	virtual void onGameActivated(bool active);
	virtual bool isAdditionalViewActive() const;
	virtual std::string getServiceName() const;

	virtual void onRemoteNotification(const std::string& serviceId, std::string& payloadAsJSON, bool active);
	virtual void onChannelLoadingFailed();
	virtual void onChannelShown();
	virtual void onChannelHidden();
	virtual void onChannelClosed();
	virtual void onChannelCancelled();
	virtual void onNewChannelContentUpdated(int numOfNewContent);
	virtual std::string channelData() const;
	virtual void setChannelData(const std::string& data);

	bool isInitialized(); //No code?
	bool isAvailable();
	bool isChannelViewOpened();
	void updateServiceConfiguration();
	bool forceUpdateNewContent(bool forceUpdate);
	void handleRemoteNotificationReceived(const std::string& payloadAsJSON);

	void openChannelView(const std::string locale, int width, int height, const std::string jsonPayload, const std::string entryPoint);
	void cancelChannelViewLoading();
	bool updateNewContent();
	int numOfNewContent();
	void onMenuInitialised();
};

#endif