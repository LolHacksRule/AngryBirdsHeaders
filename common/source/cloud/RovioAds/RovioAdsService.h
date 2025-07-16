#ifndef _COMMON_CLOUD_ROVIOADSSERVICE_H
#define _COMMON_CLOUD_ROVIOADSSERVICE_H

#include <GameLua.h>
#include "../RovioCloudManager.h"

class RovioAdsService : public lua::LuaObject, public IRovioCloudService, private rcs::ads::Manager::Listener, private rcs::ads::Renderer, private rcs::ads::RewardListener
{
public:
	RovioAdsService(RovioCloudManager* cloudManager, GameLua* gameLua);
	~RovioAdsService();
	
	void addPlacement(std::string placement);
	void addPlacementWithGeometry(std::string placement, int x, int y, int width, int height);
	void addPlacementNative(std::string placement);
	bool show(std::string placement);
	void refresh(std::string placement);
	void hide(std::string placement);
	void click(std::string placement);
	
	void setTargetingParams(const std::vector<char>& targetParams);
	void trackConversion();
	
	void startSession();
	
	bool isAdManagerReady();
	
	virtual void onRewardResult(const std::string& placement, rcs::ads::RewardListener::Result result);
	
	virtual void onRewardResult(const std::string& placement, rcs::ads::RewardListener::Result result, const std::string& voucherId);
	
	virtual void initialize();
	virtual void onGameActivated(bool active);
	virtual bool isAdditionalViewActive() const;
	virtual std::string getServiceName() const;
	
	virtual void onStateChanged(const std::string& placement, rcs::ads::Manager::AdState state);
	virtual void onSizeChanged(const std::string& placement, int width, int height);
	virtual bool onActionInvoked(const std::string& action, const std::string& placement);
	
	virtual bool onRenderableReady(const std::string& placement, const rcs::ads::Renderable& renderable);
	virtual bool onShow(const std::string& placement);
	virtual bool onHide(const std::string& placement);
	
	RovioAdsService(const RovioAdsService&);
	RovioAdsService& operator=(RovioAdsService&);
private:
	GameLua *m_gameLua;
	rcs::ads::Manager *m_adManager;
	std::tr1::shared_ptr<CloudConfiguration> m_cloudConfiguration;
	gr::Context *m_context;
	game::Resources *m_resources;
	int m_screenWidth;
	int m_screenHeight;
	
	bool m_sessionStarted;
	int64_t m_deactivationTime;
	std::map<std::string,std::string> m_targetParams;
	lang::Ptr<lang::event::Link> m_adTargetingParamsLink;
};

#endif