#ifndef _COMMON_APPRATER_H
#define _COMMON_APPRATER_H

#include <game/Resources.h>
#include <LuaManager.hpp>

class Apprater
{
public:
	Apprater(lua::LuaState* state, lua::LuaState* resources);
	void registerMethods(LuaManager* luaManager);
	struct Config
	{
		std::string iTunesAppId;
		double daysUntilPromptFirst;
		double daysUntilPromptLater;
		int triesUntilPromptFirst;
		int triesUntilPromptLater;
	};
private:
	void showAlert(std::string promptReason);
	game::Resources* m_resources;
};

#endif