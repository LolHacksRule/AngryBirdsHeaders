#ifndef _COMMON_SPOTLIGHT_H
#define _COMMON_SPOTLIGHT_H

#include <math/float2.h>
#include <gr/Context.h>
#include <gr/Shader.h>
#include <lang/Ptr.h>

class Spotlight : public lang::Object
{
public:
	Spotlight(gr::Context* context);
	void setPosition(math::float2 position);
	void move(float dt);
	void render() const;
private:
	math::float4 m_position;
	math::float2 m_velocity;
	math::float2 m_acceleration;
	gr::Context *m_context;
	lang::Ptr<gr::Shader> m_shader;
}

#endif