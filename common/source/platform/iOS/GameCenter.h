#ifndef _IOS_GAMECENTER_H
#define _IOS_GAMECENTER_H

#include "GameApp.h"
#include "GameLua.h"
#include <gr/Context.h>

class GameCenter
{
public:
	GameCenter(GameApp *app, GameLua *gl, gr::Context *context);
	~GameCenter();
	
	void init();
	
	void firstInit();
	
	void enableGameCenter();
	
	void disableGameCenter();
	
	void noSupport();
	
	void activate();
	
	void activateAtProfile();
	
	void deactivate();
	
	void postHighscore(std::string leaderBoardId, double scoreValue);
	
	void unlockAchievement(std::string achievementId, float percentage);
	
	void getLeaderboardScoresForPlayers(std::string, std::vector<std::string>);
	
	void getLeaderboardScoreForLocalPlayer(std::string);
	
	void getLeaderboardScoresForRange(std::string leaderBoardId, int start, int length);
	
	void getLeaderboardScoresForFriends();
	
	void getPlayerNames();
	
	void showSplash();
	
	bool isSplashShowing();
	
	void lockToOrientation();
	
	bool isUIShowing();
	
	bool isGameCenterAvailable();
	
	bool loadFriends();
	
	void loadLeaderboardCategories();
	
	void loadAchievements();
	
	void loadAchievementMetaData();
	
	void showLeaderboards();
	
	void showAchievement();
	
	void resumeUpdate();
	
	void setOrientation(gr::OrientationType orientation);
	
	void setGCPopupAllowed(bool allowed);
private:
	GameApp* m_app;
	GameLua* m_gl;
	Context* m_context;
	bool m_popupAllowed;
};

#endif