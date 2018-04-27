#ifndef BOOK_CATEGORY_HPP
#define BOOK_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		SceneAirLayer		= 1 << 0,
		PlayerAircraft		= 1 << 1,
		AlliedAircraft		= 1 << 2,
		EnemyAircraft		= 1 << 3,
		Pickup				= 1 << 4,
		AlliedProjectile	= 1 << 5,
		EnemyProjectile		= 1 << 6,
		ParticleSystem		= 1 << 7,

		Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
		Projectile = AlliedProjectile | EnemyProjectile,
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

#endif // BOOK_CATEGORY_HPP
