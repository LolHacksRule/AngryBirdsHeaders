#ifndef _COMMON_WATEREFFECT_HPP
#define _COMMON_WATEREFFECT_HPP

#include <lua/LuaTable.h>

using namespace lua;

class WaterEffect //Classic and Seasons
{
public:
	void WaterEffect(const LuaTable& objects);
	static float waterLevel() const;
	static float killLevel() const;
	static bool hasKillLevel() const;
	static bool isFreezing() const;
	operator bool() { return m_hasWater; };
private:
	bool m_hasWater;
	bool m_hasKillLevel;
	bool m_isFreezing;
	float m_waterLevel;
	float m_killLevel;
};

#endif