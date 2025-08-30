#ifndef _COMMON_PARTICLEMANAGER_H
#define _COMMON_PARTICLEMANAGER_H

//#include "GameLua.h"
#include "Particle.h"
#include "Utils.h"
#include "Definition.h"
#include <game/Resources.h>
#include <lua/LuaObject.h>

using namespace gr;
using namespace math;
using namespace lua;
using namespace game;

class GameLua;

namespace particle
{
	class Manager
	{
public:
		Manager(lua::LuaState *lua, GameLua *game, game::Resources *resources);
		~Manager();
		
		void add(particle::System::Enum type, const std::string& definitionName, size_t amount, math::float2 angle, math::float2 rotation, float pos, bool ignoreLimits, float);
		
		void draw(gr::Context* context, particle::System::Enum type, math::float2 scale, float translate);
		
		void update(particle::System::Enum type, float dt);
		
		void setSoftLimit(size_t limit, float multiplier);
		
		void setHardLimit(size_t limit);
		
		void clear();
		
		void clear(System::Enum type);
		
		void reset();
		
		bool useCloudsInsteadOfGround();
private:
		void lua_add(float type, std::string, size_t amount, float x, float y, float w, float h, float angle, bool ignoreLimits);
		
		void lua_deprecatedAdd();
		
		void lua_update(float type, float dt);
		int lua_clear(LuaState* state);
		
		typedef std::vector<Particle> ParticleContainer;
		
		LuaObject m_interface;
		GameLua* m_gameLua;
		Resources* m_resources;
		
		bool cloudsInsteadOfGround;
		
		struct ParticleType
		{
			Definition definition;
			ParticleContainer particles[2];
		};
		
		std::map<std::string,ParticleType> m_particleSystems;
		
		float m_softLimitMultiplier;
		size_t m_softLimit;
		size_t m_hardLimit;
		
		int m_viewWidth, m_viewHeight;
		Rect m_cameraBounds;
		std::vector<lang::Ptr<lang::event::Link> m_persistentLinks;
		
		void setCameraBounds(float left, float top, float right, float bottom);
		//void setDefaultLimits(); //Inline?
		void resolutionChanged(int width, int height);
		void updateLooping(const std::string& defName, ParticleType& pt, const Rect& oldView, const Rect& newView);
		
		Manager(const Manager&)
		operator=(Manager);
	};
}

#endif