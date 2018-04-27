#include <Book/DataTables.hpp>
#include <Book/Aircraft.hpp>
#include <Book/Projectile.hpp>
#include <Book/Pickup.hpp>
#include <Book/Particle.hpp>

#include <GameObjects/Runner.hpp>
#include <GameObjects/Obstruction.hpp>
#include <GameObjects/Ability.hpp>


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<AircraftData> initializeAircraftData()
{
	std::vector<AircraftData> data(Aircraft::TypeCount);

	data[Aircraft::Eagle].hitpoints = 100;
	data[Aircraft::Eagle].speed = 200.f;
	data[Aircraft::Eagle].fireInterval = sf::seconds(1);
	data[Aircraft::Eagle].texture = Textures::Entities;
	data[Aircraft::Eagle].textureRect = sf::IntRect(0, 0, 48, 64);
	data[Aircraft::Eagle].hasRollAnimation = true;

	data[Aircraft::Raptor].hitpoints = 20;
	data[Aircraft::Raptor].speed = 80.f;
	data[Aircraft::Raptor].texture = Textures::Entities;
	data[Aircraft::Raptor].textureRect = sf::IntRect(144, 0, 84, 64);
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));
	data[Aircraft::Raptor].directions.push_back(Direction(-45.f, 160.f));
	data[Aircraft::Raptor].directions.push_back(Direction(+45.f, 80.f));
	data[Aircraft::Raptor].fireInterval = sf::Time::Zero;
	data[Aircraft::Raptor].hasRollAnimation = false;

	data[Aircraft::Avenger].hitpoints = 40;
	data[Aircraft::Avenger].speed = 50.f;
	data[Aircraft::Avenger].texture = Textures::Entities;
	data[Aircraft::Avenger].textureRect = sf::IntRect(228, 0, 60, 59);
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f,  50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(  0.f,  50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(-45.f, 100.f));
	data[Aircraft::Avenger].directions.push_back(Direction(  0.f,  50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f,  50.f));
	data[Aircraft::Avenger].fireInterval = sf::seconds(2);
	data[Aircraft::Avenger].hasRollAnimation = false;

	return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Textures::Entities;
	data[Projectile::AlliedBullet].textureRect = sf::IntRect(175, 64, 3, 14);

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 300.f;
	data[Projectile::EnemyBullet].texture = Textures::Entities;
	data[Projectile::EnemyBullet].textureRect = sf::IntRect(178, 64, 3, 14);

	data[Projectile::Missile].damage = 200;
	data[Projectile::Missile].speed = 150.f;
	data[Projectile::Missile].texture = Textures::Entities;
	data[Projectile::Missile].textureRect = sf::IntRect(160, 64, 15, 32);

	return data;
}

std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);
	
	data[Pickup::HealthRefill].texture = Textures::Entities;
	data[Pickup::HealthRefill].textureRect = sf::IntRect(0, 64, 40, 40);
	data[Pickup::HealthRefill].action = [] (Aircraft& a) { a.repair(25); };
	
	data[Pickup::MissileRefill].texture = Textures::Entities;
	data[Pickup::MissileRefill].textureRect = sf::IntRect(40, 64, 40, 40);
	data[Pickup::MissileRefill].action = std::bind(&Aircraft::collectMissiles, _1, 3);
	
	data[Pickup::FireSpread].texture = Textures::Entities;
	data[Pickup::FireSpread].textureRect = sf::IntRect(80, 64, 40, 40);
	data[Pickup::FireSpread].action = std::bind(&Aircraft::increaseSpread, _1);
	
	data[Pickup::FireRate].texture = Textures::Entities;
	data[Pickup::FireRate].textureRect = sf::IntRect(120, 64, 40, 40);
	data[Pickup::FireRate].action = std::bind(&Aircraft::increaseFireRate, _1);

	return data;
}

std::vector<ParticleData> initializeParticleData()
{
	std::vector<ParticleData> data(Particle::ParticleCount);

	data[Particle::Propellant].color = sf::Color(255, 255, 50);
	data[Particle::Propellant].lifetime = sf::seconds(0.6f);

	data[Particle::Smoke].color = sf::Color(50, 50, 50);
	data[Particle::Smoke].lifetime = sf::seconds(4.f);

	return data;
}

namespace INFINITYRUNNER {
	std::vector<RunnerData> initializeRunnerData()
	{
		std::vector<RunnerData> data(Runner::TypeCount);

		data[Runner::Professor].health = 50.f;
		data[Runner::Professor].velocity = 150.f;
		data[Runner::Professor].acceleration = 0.f;
		data[Runner::Professor].texture = Textures::Actors;
		data[Runner::Professor].textureBoundary = sf::IntRect(0, 0, 48, 64);
		data[Runner::Professor].runInterval = sf::milliseconds(500);
		data[Runner::Professor].slideInterval = sf::milliseconds(1000);
		data[Runner::Professor].jumpInterval = sf::milliseconds(1000);
		data[Runner::Professor].cycleInterval = sf::milliseconds(1000);
		data[Runner::Professor].abilityInterval = sf::seconds(10);
		data[Runner::Professor].hasRunAnimation = true;
		data[Runner::Professor].runAnimFrames = 12;
		data[Runner::Professor].hasSlideAnimation = true;
		data[Runner::Professor].slideAnimFrames = 1;
		data[Runner::Professor].hasJumpAnimation = true;
		data[Runner::Professor].jumpAnimFrames = 1;

		data[Runner::Scientist].health = 50.f;
		data[Runner::Scientist].velocity = 150.f;
		data[Runner::Scientist].acceleration = 0.f;
		data[Runner::Scientist].texture = Textures::Actors;
		data[Runner::Scientist].textureBoundary = sf::IntRect(0, 0, 48, 64);
		data[Runner::Scientist].runInterval = sf::milliseconds(650);
		data[Runner::Scientist].slideInterval = sf::milliseconds(1000);
		data[Runner::Scientist].jumpInterval = sf::milliseconds(1000);
		data[Runner::Scientist].cycleInterval = sf::milliseconds(1000);
		data[Runner::Scientist].abilityInterval = sf::seconds(10);
		data[Runner::Scientist].hasRunAnimation = true;
		data[Runner::Scientist].runAnimFrames = 12;
		data[Runner::Scientist].hasSlideAnimation = true;
		data[Runner::Scientist].slideAnimFrames = 1;
		data[Runner::Scientist].hasJumpAnimation = true;
		data[Runner::Scientist].jumpAnimFrames = 1;

		data[Runner::Soldier].health = 50.f;
		data[Runner::Soldier].velocity = 150.f;
		data[Runner::Soldier].acceleration = 0.f;
		data[Runner::Soldier].texture = Textures::Actors;
		data[Runner::Soldier].textureBoundary = sf::IntRect(0, 0, 48, 64);
		data[Runner::Soldier].runInterval = sf::milliseconds(255);
		data[Runner::Soldier].slideInterval = sf::milliseconds(1000);
		data[Runner::Soldier].jumpInterval = sf::milliseconds(1000);
		data[Runner::Soldier].cycleInterval = sf::milliseconds(1000);
		data[Runner::Soldier].abilityInterval = sf::seconds(10);
		data[Runner::Soldier].hasRunAnimation = true;
		data[Runner::Soldier].runAnimFrames = 12;
		data[Runner::Soldier].hasSlideAnimation = true;
		data[Runner::Soldier].slideAnimFrames = 1;
		data[Runner::Soldier].hasJumpAnimation = true;
		data[Runner::Soldier].jumpAnimFrames = 1;

		return data;
	}

	std::vector<ObstructionData> initializeObstructionData()
	{
		std::vector<ObstructionData> data(Obstruction::TypeCount);

		data[Obstruction::Hurdle].damage = 10;
		data[Obstruction::Hurdle].velocity = 0.f;
		data[Obstruction::Hurdle].acceleration = 0.f;
		data[Obstruction::Hurdle].texture = Textures::Actors;
		data[Obstruction::Hurdle].textureBoundary = sf::IntRect(5, 5, 5, 5);
		data[Obstruction::Hurdle].actInterval = sf::Time::Zero;
		data[Obstruction::Hurdle].hasActAnimation = false;
		data[Obstruction::Hurdle].actAnimFrames = 1;

		data[Obstruction::Limbo].damage = 10;
		data[Obstruction::Limbo].velocity = 0.f;
		data[Obstruction::Limbo].acceleration = 0.f;
		data[Obstruction::Limbo].texture = Textures::Actors;
		data[Obstruction::Limbo].textureBoundary = sf::IntRect(5, 5, 5, 5);
		data[Obstruction::Limbo].actInterval = sf::Time::Zero;
		data[Obstruction::Limbo].hasActAnimation = false;
		data[Obstruction::Limbo].actAnimFrames = 1;

		data[Obstruction::Fire].damage = 100;
		data[Obstruction::Fire].velocity = 0.f;
		data[Obstruction::Fire].acceleration = 0.f;
		data[Obstruction::Fire].texture = Textures::Actors;
		data[Obstruction::Fire].textureBoundary = sf::IntRect(5, 5, 5, 5);
		data[Obstruction::Fire].actInterval = sf::seconds(3);
		data[Obstruction::Fire].hasActAnimation = true;
		data[Obstruction::Fire].actInterval = sf::Time::Zero;
		data[Obstruction::Fire].hasActAnimation = false;
		data[Obstruction::Fire].actAnimFrames = 1;

		return data;
	}

	std::vector<AbilityData> initializeAbilityData()
	{
		std::vector<AbilityData> data(Ability::TypeCount);

		data[Ability::Regeneration].velocity = 0.f;
		data[Ability::Regeneration].acceleration = 0.f;
		data[Ability::Regeneration].texture = Textures::Actors;
		data[Ability::Regeneration].textureBoundary = sf::IntRect(5, 5, 5, 5);
		data[Ability::Regeneration].actInterval = sf::Time::Zero;
		data[Ability::Regeneration].hasActAnimation = false;

		data[Ability::Barrier].velocity = 0.f;
		data[Ability::Barrier].acceleration = 0.f;
		data[Ability::Barrier].texture = Textures::Actors;
		data[Ability::Barrier].textureBoundary = sf::IntRect(5, 5, 5, 5);
		data[Ability::Barrier].actInterval = sf::Time::Zero;
		data[Ability::Barrier].hasActAnimation = false;

		data[Ability::Destruction].velocity = 0.f;
		data[Ability::Destruction].acceleration = 0.f;
		data[Ability::Destruction].texture = Textures::Actors;
		data[Ability::Destruction].textureBoundary = sf::IntRect(5, 5, 5, 5);
		data[Ability::Destruction].actInterval = sf::Time::Zero;
		data[Ability::Destruction].hasActAnimation = false;

		data[Ability::FreezeTime].velocity = 0.f;
		data[Ability::FreezeTime].acceleration = 0.f;
		data[Ability::FreezeTime].texture = Textures::Actors;
		data[Ability::FreezeTime].textureBoundary = sf::IntRect(5, 5, 5, 5);
		data[Ability::FreezeTime].actInterval = sf::Time::Zero;
		data[Ability::FreezeTime].hasActAnimation = false;

		return data;
	}
}
