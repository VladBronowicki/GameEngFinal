#include "GameObjects\Building.h"
#include <Book/CommandQueue.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>

Building::Building(const sf::Texture& texture) :
	Entity(1)
, mSprite(texture)
{
	updateTexts();
}



Building::~Building()
{
}

void Building::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Building::updateCurrent(sf::Time dt, CommandQueue & commands)
{
	updateTexts();
	Entity::updateCurrent(dt, commands);
}

void Building::updateTexts()
{
}
