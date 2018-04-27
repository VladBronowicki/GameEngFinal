#pragma once

// Actor/Level node classification
namespace INFINITYRUNNER
{
	enum ElementClassification
	{
		None				= 0,
		BackgroundLayer		= 1 << 0,
		PlayerRunner		= 2 << 0,
		FriendlyRunner		= 3 << 0,
		RivalRunner			= 4 << 0,
		AbilityCollectible	= 5 << 0,
		ParticleEffect		= 6 << 0,

		//TODO: Problem Code - this causes the input controllers to flip out :S
		//Runner = PlayerRunner | FriendlyRunner | RivalRunner,
	};
}