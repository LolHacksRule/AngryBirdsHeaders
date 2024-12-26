#ifndef _COMMON_PARTICLE_H
#define _COMMON_PARTICLE_H

#include <game/Sprite.h>
#include <math/float2.h>

namespace particle
{
	struct Particle
	{
		std::string definition;
		math::float2 position;
		math::float2 velocity;
		float angle;
		float angleVelocity;
		float scaleBegin;
		float scaleEnd;
		float scale;
		game::Sprite *sprite;
		float time;
		float lifeTime;
		int spriteIndex;
	};
}

#endif