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


struct ParticleData
{
	sf::Color						color;
	sf::Time						lifetime;
};


std::vector<ParticleData>	initializeParticleData();

namespace INFINITYRUNNER {
	struct RunnerData
	{
		float					health;
		float					velocity;
		float					acceleration;
		Textures::ID			texture;
		sf::IntRect				textureBoundary;
		std::vector<Textures::ID>	runFrames;
		sf::Time				runInterval;
		Textures::ID			slideFrame01;
		sf::Time				slideInterval;
		Textures::ID			jumpFrame01;
		sf::Time				jumpInterval;
		sf::Time				cycleInterval;
		sf::Time				abilityInterval;
		std::vector<Direction>	slideDirections;
		std::vector<Direction>	jumpDirections;
		bool					hasRunAnimation;
		bool					hasSlideAnimation;
		bool					hasJumpAnimation;
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
