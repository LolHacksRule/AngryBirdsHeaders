#ifndef _GAMEAPP_H
#define _GAMEAPP_H

//Classic and Seasons

#include <lang/Object.h>
//#include <lang/Ptr.h>
#include <gr/Context.h>
#include <framework/App.h>
#include <framework/OSInterface.h>
#include "GameLua.h"
#include "apprater/Apprater.h"

class GameApp :
	public framework::App
{
public:
	GameApp(gr::Context* context, framework::OSInterface* os);
	virtual ~GameApp();
	
	virtual void update(float dt, gr::Context * context, int);
	virtual void activate(bool active);
	virtual bool activateAudio(bool active);
	virtual void loadFromUrl(const std::string& url);
	virtual void mouseMove(int dx, int dy);
	virtual void keyDown(KeyType key);
	virtual void keyUp(KeyType key);
	virtual void resolutionChanged(); //Only has code on PC/Mac
	virtual void mouseWheel(int ticks);
	virtual void orientationChanged();
	void toggleZoomSteps(float minZoom, float maxZoom, short steps);
	GameLua* getGameLua() const;
	virtual bool safeToQuit() const;
	std::string getDeviceModel();
	bool isHDVersion();
	void changeMultitouchState(); //Only has code on PC/Mac
	void GameApp(gr::Context *context, framework::OSInterface *os);
	Context* m_context;
	bool m_fullscreen;
	float m_scale;
	bool m_zooming;

	float m_maxScale;
	
	float m_smoothScalingStartScale;
	float m_smoothScalingTargetScale;
	float m_smoothScalingTime;
	float m_smoothScalingTargetTime;
	
	float m_oldScale;
	bool m_audioPlayAllowed;
	
protected:
	lang::Ptr<lua::LuaState> m_lua;
	lang::Ptr<GameLua> m_gameLua;
	
	lang::unique_ptr<LuaManager, lang::detail::default_delete<LuaManager> > m_luaManager;
	
	lang::unique_ptr<LuaGetTimeStamp, lang::detail::default_delete<LuaGetTimeStamp> > m_luaGetTimeStamp;
	
	lang::unique_ptr<LuaRovioShelf, lang::detail::default_delete<LuaRovioShelf> > m_luaRovioShelf;
	lang::unique_ptr<GameCenter, lang::detail::default_delete<GameCenter> > m_gameCenter;
	
	lang::Ptr<flurry::Flurry> m_flurry;
	lang::Ptr<flurry::FlurryLuaInterface> m_luaFlurry;
	
	lang::Ptr<game::LuaResources> m_resources;
	std::vector<lang::Ptr<gr::Shader>> m_preloadedShaders;
	
	bool m_keyPressedTemp[131];
	bool m_keyReleasedTemp[131];
	
	Apprater m_apprater;
};

#endif