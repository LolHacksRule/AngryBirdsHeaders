#ifndef _COMMON_OBJECTTELEPORTER_H
#define _COMMON_OBJECTTELEPORTER_H

#include "GameObject.hpp"
#include <Box2D/Dynamics/b2Body.h>

class ObjectTeleporter
{
	ObjectTeleporter(std::string identifier, GameObject* object, float angle, b2Vec2 position, b2Vec2 linearVelocity);
	virtual ~ObjectTeleporter();
	virtual bool update(float dt);
	b2Body* getBody();
	std::string getIdentifier() const;
	virtual bool canBeAborted() const;
	virtual bool removeOnObjectRemove() const;
	virtual ObjectTeleporter* inheritCopy(GameObject* childObject) const;
protected:
	virtual void execute();
	GameObject *m_object;
	b2Vec2 m_position;
	b2Vec2 m_linearVelocity;
	std::string m_identifier;
	float m_angle;
};

#endif