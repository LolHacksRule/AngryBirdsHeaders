#ifndef _COMMON_LUAGETTIMESTAMP_HPP
#define _COMMON_LUAGETTIMESTAMP_HPP

#include "GetTimeStamp.hpp"

class LuaGetTimeStamp
{
public:
	LuaGetTimeStamp(LuaManager& luaManager, lua::LuaState& luaState);
	
	bool done();
	
	TimeStamp get();
private:
	void lua_fetchTimeStamp(std::string url, std::string uid);
	
	bool lua_hasResult();
	
	int lua_getTimeStamp(lua::LuaState* luaState);
	lua::LuaObject m_interface;
	lang::unique_ptr<GetTimeStamp, lang::detail::default_delete<GetTimeStamp>> m_getter;
};

#endif