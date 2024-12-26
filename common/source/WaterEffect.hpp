#ifndef _COMMON_WATEREFFECT_HPP
#define _COMMON_WATEREFFECT_HPP

#include <lua/LuaTable.h>

class WaterEffect //Classic and Seasons
{
public:
	void WaterEffect(const lua::LuaTable& objects);
	float waterLevel() const { return m_waterLevel; };
	float killLevel() const { return m_killLevel; };
	bool hasKillLevel() const { return m_hasKillLevel; };
	bool isFreezing() const { return m_isFreezing; };
	operator bool() const { return m_hasWater; };
private:
	bool m_hasWater;
	bool m_hasKillLevel;
	bool m_isFreezing;
	float m_waterLevel;
	float m_killLevel;
};

#endif