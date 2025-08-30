#ifndef _COMMON_DRAWUTILS_H
#define _COMMON_DRAWUTILS_H

#include <game/Resources.h>

class DrawUtils :
	public lang::Object
{
private:
	lang::Ptr<gr::Shader> m_invertedMultiplyTextureShader;
	lang::Ptr<gr::Shader> m_multiplyTextureShader;
	lang::Ptr<gr::Shader> m_fillTextureShader;
	game::Resources *m_resources;
	gr::Context *m_context;
	bool m_platformSupportsShaders;
public:
	DrawUtils(gr::Context* context, game::Resources* resources);
	virtual ~DrawUtils();
	void customGlyphRenderer(gr::Context* context, game::Sprite* sprite, float x, float y, math::float4 color, gr::Shader* shader);
	void drawThemeSpriteTinted(game::Sprite* spr, float x, float y, const math::float2& scale, const math::float4& color);
	void drawThemeSpriteTinted(const std::string& spriteId, float x, float y, const math::float2& scale, const math::float4& color);
	bool platformSupportsShaders() const
	{
		return m_platformSupportsShaders;
	}
	
	gr::Shader* getInvertedMultiplyTextureShader();
	gr::Shader* getMultiplyTextureShader();
	gr::Shader* getFillTextureShader();
};

#endif