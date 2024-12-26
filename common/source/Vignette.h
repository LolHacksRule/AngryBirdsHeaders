#ifndef COMMON_VIGNETTE_H
#define COMMON_VIGNETTE_H

#include <lang/Ptr.h>
#include <lang/Object.h>
#include <gr/Context.h>
#include <gr/Shader.h>

class Vignette :
	public lang::Object
{
private:
	bool m_enabled;
	gr::Context* m_context;
	lang::Ptr<gr::Shader> m_shader;
public:
	Vignette(gr::Context* context);
	virtual ~Vignette();
	void enable(bool enable);
	void render() const;
};

#endif