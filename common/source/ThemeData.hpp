#ifndef _COMMON_THEMEDATA_HPP
#define _COMMON_THEMEDATA_HPP

#include <game/Resources.h>
#include <lua/LuaTable.h>

using namespace game;
using namespace lua;

class ThemeLayerData
{
public:
	ThemeLayerData(const lua::LuaTable& layerTable, game::Resources& res);
	std::string sheet;
	std::string sprite;

	float height;
	float width;

	math::float2 pivot;

	float parallaxSpeed;
	float scale;
	float offset;
	bool looping;
	bool water;
	uint8_t color[4];
	float velocity;
	float scaleWobbleY;
	float startX;
	float offsetY;
	bool hasSprite;
	bool overrideTint;
	std::vector<ThemeSpriteData> sprites;

	bool fillBelow;
	uint8_t fillColor[4];
};

struct ThemeSpriteData
{
public:
	game::Sprite* sprite;
	float x;
	float y;
	float speedX;
	float scaleX;
	float scaleY;
	float angle;
	std::string name;
};

class ThemeData
{
public:
	ThemeData(const lua::LuaTable& themeTable, game::Resources& res);

	ThemeData();

	math::float3 bgTintColor;
	math::float3 bgColor;
	math::float3 groundColor;
	math::float3 waterBottomColor;

	std::vector<ThemeLayerData> bgLayers;
	std::vector<ThemeLayerData> fgLayers;
private:
	ThemeData(const ThemeData&);
};