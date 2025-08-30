#ifndef _COMMON_GAMEOBJECT_HPP
#define _COMMON_GAMEOBJECT_HPP

//Classic and Seasons

#include <game/CompoSprite.h>
#include <lua/LuaTable.h>

enum ColliderType
{
	COLLIDER_BASIC,
	COLLIDER_EAGLE,
	COLLIDER_STATIC,
	COLLIDER_BIRD,
	COLLIDER_PIG,
	COLLIDER_GHOST,
	COLLIDER_EGG,
	COLLIDER_BASKETBALL,
	COLLIDER_INVISIBLE,
	COLLIDER_PORTAL,
	COLLIDER_HOOP,
	COLLIDER_NO_COLLISION,
	COLLIDER_NO_BIRD_COLLISION,
	COLLIDER_NO_OTHER_COLLISION,
	COLLIDER_GLUE,
	COLLIDER_BUBBLE,
	COLLIDER_COUNT,
	COLLIDER_INVALID
};

enum ShapeType
{
	SHAPE_CIRCLE,
	SHAPE_BOX,
	SHAPE_POLYGON,
	SHAPE_COUNT,
	SHAPE_INVALID
};

struct TransformData
{
	float x;
	float y;
	float angle;
};

class GameObject :
	public lang::Object
{
public:
	GameObject(b2World* world);
	~GameObject();
	
	void create();
	void recreate();
	
	void setupLuaTable(LuaTable& world);
	
	ColliderType getColliderType() const;
	ShapeType getShapeType() const;
	math::float2 getScale() const;
	float getWidth() const;
	float getHeight() const;
	bool getVisible() const;
	bool isSensor() const;
	void setColliderType (ColliderType type);
	void setShape(ShapeType shape);
	void setDimensions(float width, float height);
	void setRadius(float radius);
	void setVertices(const std::vector<b2Vec2>& verts);
	void setDensity(float density);
	void setFriction(float friction);
	void setRestitution(float restitution);
	void setScale(math::float2 scale);
	void setVisible(bool visible);
	void setSensor(bool sensor);
	void setFilterCategory(int category);
	void setFilterMask(int mask);
	int incrementPortalPingPongCount(std::string enterPortal, std::string exitPortal);
	void setGravityEnabled(bool enabled);
	bool isGravityEnabled const();
	void triggerRemoval(float delay);
private:
	ColliderType m_colliderType;
	ShapeType m_shapeType;
	float m_width;
	float m_height;
	float m_density;
	float m_friction;
	float m_restitution;
	math::float2 m_scale;
	b2World* m_world;
	bool m_visible;
	bool m_sensor;
	bool m_gravityEnabled;
public:
	b2Body* m_body;
private:
	std::vector<b2Vec2> m_vertices;
	std::string m_lastExitedPortal;
	int m_portalPingPongCount;

	void createFixture();
public:
	TransformData positions[2];
	std::string rollingSound;
	lua::LuaTable objectTable;
	math::float2 afterCollisionVelocity;
	std::string objectName;
	std::string spriteName;
	std::string textureName;
	game::Sprite* sprite;
	game::CompoSprite* compoSprite;
	gr::Image* texture;
	float radius;
	float x;
	float y;
	float angle;
	float z_order;
	bool updateAfterCollision;
	bool oldSleep;
	bool collision;
	bool hasForceOrFriction;
	bool toBeRemoved;
	float removeTimer;
	bool scalable;
	float scaleX;
	float scaleY;
	float originalScaleX;
	float originalScaleY;
	bool ghostBlock;
	bool hoopCorrectlyEntered;
	float ghostWobbleAngle;
	float passThroughParticleTimer;
	std::string passThroughParticles;
	std::string passThroughSound;
};

#endif