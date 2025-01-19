#ifndef _COMMON_VIGNETTE_H
#define _COMMON_VIGNETTE_H

#include <lang/Object.h>
#include <gr/Context.h>

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