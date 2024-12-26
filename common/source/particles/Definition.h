#ifndef _COMMON_PARTICLEDEFINITION_H
#define _COMMON_PARTICLEDEFINITION_H

namespace particle
{
	struct Definition
	{
		enum EmitterType
		{
			ET_BOX,
			ET_CIRCLE,
			ET_BAT,
		};
		std::string name;
		std::vector<std::string> sprites;
		std::string spriteSheet;
		bool lifeTimeAnimation;
		bool randomizeBirthPosition;
		EmitterType emitterType;
		float minVel;
		float maxVel;
		float minVelX;
		float maxVelX;
		float minVelY;
		float maxVelY;
		float minAngleVel;
		float maxAngleVel;
		float minScaleBegin;
		float maxScaleBegin;
		float minScaleEnd;
		float maxScaleEnd;
		float lifeTime;
		float gravityX;
		float gravityY;
		float angleMinEmitter;
		float angleMaxEmitter;
		float targetX;
		float targetY;
		float killEarlyPercent;
		float animationLength;
		float density;
		bool targetedParticle;
		bool looping;
		bool drawCloudInsteadOfGround;
	};
}

#endif