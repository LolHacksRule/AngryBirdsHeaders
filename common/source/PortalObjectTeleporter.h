#ifndef _COMMON_PORTALOBJECTTELEPORTER_H
#define _COMMON_PORTALOBJECTTELEPORTER_H

#include "ObjectTeleporter.h"

class PortalObjectTeleporter : public ObjectTeleporter
{
public:
	PortalObjectTeleporter(GameObject *object, float angle, float minOutSpeed, std::string fromPortalName, float fromPortalAngle, std::string toPortalName, float toPortalAngle, float delay, game::Resources *resources, particle::Manager *particleSpawner, float particlePositionMultiplier, lua::LuaTable effects, GameLua* gamelua, b2Vec2 position, b2Vec2 fromPortalPosition, b2Vec2 fromPortalCenter, b2Vec2 toPortalPosition);

	virtual ~PortalObjectTeleporter();
	virtual bool update(float dt);
	virtual bool canBeAborted() const;
	virtual bool removeOnObjectRemove() const;
	virtual ObjectTeleporter* inheritCopy(GameObject* childObject) const;
protected:
	virtual void execute();
private:
	const int MAXIMUM_PING_PONG_COUNT = 10;
	void playEffects(bool enter);
	void restoreObject();
	void recalculateLinearVelocity();
	std::string m_fromPortalName;
	std::string m_toPortalName;
	lua::LuaTable m_effects;
	particle::Manager* m_particleSpawner;
	game::Resources* m_resources;
	b2Vec2 m_fromPortalPosition;
	b2Vec2 m_fromPortalCenter;
	float m_fromPortalAngle;
	b2Vec2 m_fromPortalNormal;
	b2Vec2 m_toPortalPosition;
	float m_toPortalAngle;
	b2Vec2 m_toPortalNormal;
	float m_timer;
	float m_particlePositionMultiplier;
	float m_minOutSpeed;
	bool m_timerStarted;
	bool m_recalculateLinearVelocity;
	bool m_maxPingPongReached;
	GameLua *m_gamelua;
};

#endif