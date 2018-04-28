#include <GameObjects/Actor.hpp>

#include <cassert>


INFINITYRUNNER::Actor::Actor()
	: mVelocity()
	, mAcceleration()
	, mHealth()
{
}

void INFINITYRUNNER::Actor::updateCurrent(sf::Time deltaTime, CommandQueue& commands)
{
	if (true) this->applyAcceleration(deltaTime);
	move(mVelocity * deltaTime.asSeconds());
}

void INFINITYRUNNER::Actor::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void INFINITYRUNNER::Actor::setVelocity(float velocityX, float velocityY)
{
	mVelocity.x = velocityX;
	mVelocity.y = velocityY;
}

sf::Vector2f INFINITYRUNNER::Actor::getVelocity() const
{
	return mVelocity;
}

void INFINITYRUNNER::Actor::setAcceleration(sf::Vector2f acceleration)
{
	mAcceleration = acceleration;
}

void INFINITYRUNNER::Actor::setAcceleration(float accelerationX, float accelerationY)
{
	mAcceleration.x = accelerationX;
	mAcceleration.y = accelerationY;
}

sf::Vector2f INFINITYRUNNER::Actor::getAcceleration() const
{
	return mAcceleration;
}

void INFINITYRUNNER::Actor::applyAcceleration(sf::Time deltaTime)
{
	//TODO: not yet implemented
}

float INFINITYRUNNER::Actor::getHealth() const
{
	return mHealth;
}

void INFINITYRUNNER::Actor::healHealth(float value)
{
	assert(value > 0);
	mHealth += value;
}

void INFINITYRUNNER::Actor::damageHealth(float value)
{
	assert(value > 0);
	mHealth -= value;
}

void INFINITYRUNNER::Actor::killSelf()
{
	mHealth = 0;
}

void INFINITYRUNNER::Actor::removeSelf()
{
	this->killSelf();
}

bool INFINITYRUNNER::Actor::isDead() const
{
	return mHealth <= 0;
}