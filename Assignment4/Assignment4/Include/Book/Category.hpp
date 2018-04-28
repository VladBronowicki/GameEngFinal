#pragma once

namespace Category
{
	enum Type
	{
		None				= 0,
		Actor				= 1 << 0,
		Collectible			= 1 << 1,
		ParticleSystem		= 1 << 2,
	};

	enum RunType
	{
		Run_None = 0,
		Run_Foreground = 1 << 0,
		Run_Building = 1 << 1,
		Run_Prop = 1 << 2,
		Run_Player = 1 << 3,
	};
}
