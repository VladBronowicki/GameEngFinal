#pragma once

#include <Book/ResourceIdentifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <functional>


class Aircraft;

struct Direction
{
	Direction(float angle, float distance)
	: angle(angle)
	, distance(distance)
	{
	}

	float angle;
	float distance;
};

struct AircraftData
{
	int								hitpoints;
	float							speed;
	Textures::ID					texture;
	sf::IntRect						textureRect;
	sf::Time						fireInterval;
	std::vector<Direction>			directions;
	bool							hasRollAnimation;
};

struct ProjectileData
{
	int								damage;
	float							speed;
	Textures::ID					texture;
	sf::IntRect						textureRect;
};

struct PickupData
{
	std::function<void(Aircraft&)>	action;
	Textures::ID					texture;
	sf::IntRect						textureRect;
};

struct ParticleData
{
	sf::Color						color;
	sf::Time						lifetime;
};


std::vector<AircraftData>	initializeAircraftData();
std::vector<ProjectileData>	initializeProjectileData();
std::vector<PickupData>		initializePickupData();
std::vector<ParticleData>	initializeParticleData();

namespace INFINITYRUNNER {
	struct RunnerData
	{
		float					health;
		float					velocity;
		float					acceleration;
		Textures::ID			texture;
		sf::IntRect				textureBoundary;
		sf::Time				runInterval;
		sf::Time				slideInterval;
		sf::Time				jumpInterval;
		sf::Time				cycleInterval;
		sf::Time				abilityInterval;
		std::vector<Direction>	slideDirections;
		std::vector<Direction>	jumpDirections;
		bool					hasRunAnimation;
		int						runAnimFrames;
		bool					hasSlideAnimation;
		int						slideAnimFrames;
		bool					hasJumpAnimation;
		int						jumpAnimFrames;
	};

	struct ObstructionData
	{
		float					damage;
		float					velocity;
		float					acceleration;
		Textures::ID			texture;
		sf::IntRect				textureBoundary;
		sf::Time				actInterval;
		std::vector<Direction>	actDirections;
		bool					hasActAnimation;
		int						actAnimFrames;
	};

	struct AbilityData
	{
		//std::function<void(Runner&)>	action;
		float							velocity;
		float							acceleration;
		Textures::ID					texture;
		sf::IntRect						textureBoundary;
		sf::Time						actInterval;
		std::vector<Direction>			actDirections;
		bool							hasActAnimation;
	};

	std::vector<RunnerData>			initializeRunnerData();
	std::vector<ObstructionData>	initializeObstructionData();
	std::vector<AbilityData>		initializeAbilityData();
}
