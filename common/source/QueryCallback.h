#ifndef COMMON_QUERYCALLBACK_H
#define COMMON_QUERYCALLBACK_H

#include <Box2D/Dynamics/b2Body.h> //Partial copy of B2D
#include <Box2D/Dynamics/b2Vec2.h>

class QueryCallback : public b2QueryCallback
{
	QueryCallback(const b2Vec2& point, std::vector<b2Body*>* objs, bool incStatic);

	virtual ~QueryCallback();

	virtual bool ReportFixture(b2Fixture* fixture);

	b2Vec2 m_point;
	std::vector<b2Body*> *m_objects;
	bool m_includeStatic;
};

#endif