#ifndef _MASKTEXTURIZER_H
#define _MASKTEXTURIZER_H

//Classic and Seasons

#include <lang/Object.h>
#include <math/float4.h>
#include <gr/Primitive.h>
#include <gr/Texture.h>

namespace internal
{
	class ImageMask :
		public lang::Object
	{
	public:
		ImageMask();

		void add(const math::float4 vertices[], const math::float4 imageUVs[], Sprite* mask);

		lang::Ptr<gr::Primitive> createPrimitive(Context& context);

		Texture* texture() const;
		bool empty() const;

		void clear();
	private:
		Texture* m_maskTexture;
		std::vector<math::float4> m_verts;
		std::vector<math::float4> m_imageUVs;
		std::vector<math::float4> m_maskUVs;
	};
}

class MaskTexturizer :
	public lang::Object
{
public:
	MaskTexturizer(Context& context);

	void addMask(Texture& context, Sprite& mask, math::float2 dest);

	void render();

	void clear();

	bool empty() const;


private:
	ImageMask& getMask(gr::Texture& texture);
	gr::Context& m_context;
	lang::Ptr<gr::Shader> m_shader;
	bool m_isFreezing;
	std::map<gr::Texture*, internal::ImageMask*> m_tex2mask;
	std::deque<lang::Ptr<internal::ImageMask>> m_masks;
};
#endif