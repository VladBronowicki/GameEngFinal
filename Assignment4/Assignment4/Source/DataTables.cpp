#include <Book/DataTables.hpp>
#include <Book/Particle.hpp>

#include <GameObjects/Runner.hpp>
#include <GameObjects/Obstruction.hpp>
#include <GameObjects/Ability.hpp>


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;


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
		data[Runner::Professor].texture = Textures::Run_Character_1;
		data[Runner::Professor].textureBoundary = sf::IntRect(0, 0, 413, 363);
		data[Runner::Professor].runFrames = std::vector<Textures::ID>{ Textures::Run_Character_1
																	 , Textures::Run_Character_2
																	 , Textures::Run_Character_3
																	 , Textures::Run_Character_4
																	 , Textures::Run_Character_5
																	 , Textures::Run_Character_6
																	 , Textures::Run_Character_7
																	 , Textures::Run_Character_8
																	 , Textures::Run_Character_9
																	 , Textures::Run_Character_10
																	 , Textures::Run_Character_11
																	 , Textures::Run_Character_12 };
		data[Runner::Professor].runInterval = sf::milliseconds(1000);
		data[Runner::Professor].slideFrame01 = Textures::Run_Character_Slide;
		data[Runner::Professor].slideInterval = sf::milliseconds(1000);
		data[Runner::Professor].jumpFrame01 = Textures::Run_Character_Jump;
		data[Runner::Professor].jumpInterval = sf::milliseconds(1000);
		data[Runner::Professor].cycleInterval = sf::milliseconds(1000);
		data[Runner::Professor].abilityInterval = sf::seconds(10);
		data[Runner::Professor].hasRunAnimation = true;
		data[Runner::Professor].hasSlideAnimation = true;
		data[Runner::Professor].hasJumpAnimation = true;

		data[Runner::Scientist].health = 50.f;
		data[Runner::Scientist].velocity = 150.f;
		data[Runner::Scientist].acceleration = 0.f;
		data[Runner::Scientist].texture = Textures::Run_Character_1;
		data[Runner::Scientist].textureBoundary = sf::IntRect(0, 0, 413, 363);
		data[Runner::Scientist].runFrames = std::vector<Textures::ID>{ Textures::Run_Character_1
																	 , Textures::Run_Character_2
																	 , Textures::Run_Character_3
																	 , Textures::Run_Character_4
																	 , Textures::Run_Character_5
																	 , Textures::Run_Character_6
																	 , Textures::Run_Character_7
																	 , Textures::Run_Character_8
																	 , Textures::Run_Character_9
																	 , Textures::Run_Character_10
																	 , Textures::Run_Character_11
																	 , Textures::Run_Character_12 };
		data[Runner::Scientist].runInterval = sf::milliseconds(1000);
		data[Runner::Scientist].slideFrame01 = Textures::Run_Character_Slide;
		data[Runner::Scientist].slideInterval = sf::milliseconds(1000);
		data[Runner::Scientist].jumpFrame01 = Textures::Run_Character_Jump;
		data[Runner::Scientist].jumpInterval = sf::milliseconds(1000);
		data[Runner::Scientist].cycleInterval = sf::milliseconds(1000);
		data[Runner::Scientist].abilityInterval = sf::seconds(10);
		data[Runner::Scientist].hasRunAnimation = true;
		data[Runner::Scientist].hasSlideAnimation = true;
		data[Runner::Scientist].hasJumpAnimation = true;

		data[Runner::Soldier].health = 50.f;
		data[Runner::Soldier].velocity = 150.f;
		data[Runner::Soldier].acceleration = 0.f;
		data[Runner::Soldier].texture = Textures::Run_Character_1;
		data[Runner::Soldier].textureBoundary = sf::IntRect(0, 0, 413, 363);
		data[Runner::Soldier].runFrames = std::vector<Textures::ID>{ Textures::Run_Character_1
																   , Textures::Run_Character_2
																   , Textures::Run_Character_3
																   , Textures::Run_Character_4
																   , Textures::Run_Character_5
																   , Textures::Run_Character_6
																   , Textures::Run_Character_7
																   , Textures::Run_Character_8
																   , Textures::Run_Character_9
																   , Textures::Run_Character_10
																   , Textures::Run_Character_11
																   , Textures::Run_Character_12 };
		data[Runner::Soldier].runInterval = sf::milliseconds(1000);
		data[Runner::Soldier].slideFrame01 = Textures::Run_Character_Slide;
		data[Runner::Soldier].slideInterval = sf::milliseconds(1000);
		data[Runner::Soldier].jumpFrame01 = Textures::Run_Character_Jump;
		data[Runner::Soldier].jumpInterval = sf::milliseconds(1000);
		data[Runner::Soldier].cycleInterval = sf::milliseconds(1000);
		data[Runner::Soldier].abilityInterval = sf::seconds(10);
		data[Runner::Soldier].hasRunAnimation = true;
		data[Runner::Soldier].hasSlideAnimation = true;
		data[Runner::Soldier].hasJumpAnimation = true;

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
