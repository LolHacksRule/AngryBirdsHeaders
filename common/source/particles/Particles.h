#ifndef _AB_LEGACY_PARTICLES_H
#define _AB_LEGACY_PARTICLES_H

#include <game/Sprite.h>
#include <lang/Array.h>

//Old impl of particles.

struct ParticleData
{
	lang::String definition;
	lang::String spriteName;
	math::float2 position;
	math::float2 velocity;
	float angle;
	float angleVelocity;
	float scaleBegin;
	float scaleEnd;
	float scale;
	game::Sprite *sprite;
	float time;
	float lifeTime;
	int spriteIndex;
	ParticleSystemData* psd;
	bool lifeTimeAnimation;
};

struct ParticleSystemData
{
	lang::String name;
	lang::Array<lang::String> sprites;
	lang::String spriteSheet;
	bool lifeTimeAnimation;
	bool randomizeBirthPosition;
	float minVelX;
	float maxVelX;
	float minVelY;
	float maxVelY;
	float minAngleVel;
	float maxAngleVel;
	float minScaleBegin;
	float maxScaleBegin;
	float minScaleEnd;
	float maxScaleEnd;
	float lifeTime;
	float gravityX;
	float gravityY;
	float angleMinEmitter;
	float angleMaxEmitter;
};

class Particles : public lua::LuaObject
{
	GameLua* m_gamelua;
	game::Resources* m_resources;
	lang::Array<ParticleData> m_particles;
	lang::Array<ParticleData> m_particles_weather;
	lang::Hashtable<lang::String,ParticleSystemData*,lang::Hash<lang::String> > m_particleSystems;
	float m_softLimitMultiplier;
	int m_softLimit;
	int m_hardLimit;
	int m_weatherSoftLimit;
	int m_weatherHardLimit;

public:
	Particles(lua::LuaState* lua, GameLua* game, game::Resources* resources);
	virtual	~Particles();

	void addParticles(lang::String definitionName, float amount, float x, float y, float w, float h, float angle, bool ignoreLimits, bool isWeather);
	void clearAll();
	void draw(gr::Context* context, bool inGame);
	void setHardLimit(float limit);
	void setSoftLimit(float limit);
	void update(float dt, bool inGame);
	void updateWeather(float dt, bool inGame);
};

#endif