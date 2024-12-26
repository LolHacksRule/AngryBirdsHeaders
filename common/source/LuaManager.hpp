#ifndef _COMMON_LUAMANAGER_HPP
#define _COMMON_LUAMANAGER_HPP

#include <lua/LuaTable.h>

class LuaManager //Classic and Seasons
{
public:
	LuaManager(lua::LuaState& luaState, std::vector<std::string> scriptPaths);
	
	void addNativeInterface(const std::string& name, const lua::LuaObject& obj);
	
	void loadLuaScript(const std::string& file);
private:
	int lua_loadLuaScript(lua::LuaState* lua);
	
	void lua_logError(std::string msg);
	
	void lua_logWarning(std::string msg);
	
	void lua_logInfo(std::string msg); //Dummied in retail?
	
	void lua_logVerbose(std::string msg); //Dummied in retail?
	
	void lua_logDebug(std::string msg); //Dummied in retail?
	
	std::string findScriptPath(const std::string& file);
	
	lua::LuaObject m_nativeLuaInterface;

	std::vector<std::string> m_scriptPaths;
};

#endif