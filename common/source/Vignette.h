#ifndef _COMMON_VIGNETTE_H
#define _COMMON_VIGNETTE_H

#include <gr/Context.h>

using namespace lang;
using namespace gr;
using namespace math;

class Vignette :
	public Object
{
public:
	Vignette(Context* context);
	virtual ~Vignette();
	void enable(bool enable);
	void render() const;
private:
	bool m_enabled;
	gr::Context* m_context;
	lang::Ptr<gr::Shader> m_shader;
};

#endif