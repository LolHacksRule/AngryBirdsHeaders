#ifndef _COMMON_PARTICLEUTILS_H
#define _COMMON_PARTICLEUTILS_H

#include <math/float4.h>

namespace particle
{
	namespace System
	{
		enum Enum
		{
			SCREEN,
			WORLD,
			COUNT
		};
	}
	struct Rect
	{
public:
		Rect(float bottom, float left, float top, float right);
		Rect(math::float4 w0);
		
		math::float2 center() const;
		float left() const;
		float right() const;
		float top() const;
		float bottom() const;
		
		float width() const;
		float height() const;
		math::float2 dimensions() const;
		float area() const;
		
		bool contains(math::float2 pos) const;
		math::float2 confine(math::float2 pos) const;
private:
		math::float4 bounds;
	};
	class RectSubtraction
	{
public:
		RectSubtraction(const particle::Rect& a, const particle::Rect& b);
		
		float area() const;
		size_t size() const;
		operator[](size_t i) const;
private:
		particle::Rect rects[4];
		size_t count;
	};
}

#endif