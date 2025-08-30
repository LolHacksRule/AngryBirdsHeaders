#ifndef _COMMON_SPOTLIGHT_H
#define _COMMON_SPOTLIGHT_H

#include <gr/Context.h>

using namespace io;
using namespace math;
using namespace gr;
using namespace lang;

class Spotlight : public lang::Object
{
public:
	Spotlight(Context* context);
	void setPosition(float2 position);
	void move(float dt);
	void render() const;
private:
	float4 m_position;
	float2 m_velocity;
	float2 m_acceleration;
	Context *m_context;
	lang::Ptr<gr::Shader> m_shader;
}

#endif