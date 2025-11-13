

//Not in ABS410. Originally in gamerepo/include.

class MaskedImage : public lang::Object
{
	gr::Context* m_context;
	lang::Ptr<gr::Shader> m_shader;
	gr::Image* m_image;
	gr::Image* m_mask;
	FUSION_CUSTOM_VECTOR<math::float4> m_verts;
	FUSION_CUSTOM_VECTOR<math::float4> m_uv0;
	FUSION_CUSTOM_VECTOR<math::float4> m_uv1;
	
	MaskedImage(gr::Context* context);
	~MaskedImage();
	void add(float dstX, float dstY, gr::Image* image, game::Sprite* mask);
	void render();
};