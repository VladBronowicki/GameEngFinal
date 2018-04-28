#pragma once

//TODO: Replace Book/SceneNode.hpp with new scene header
#include <Book/SceneNode.hpp>

namespace INFINITYRUNNER {
	/// Actor class
	class Actor : public SceneNode
	{
	/// Attributes
	private:
		sf::Vector2f	mVelocity;
		sf::Vector2f	mAcceleration;
		float			mHealth;

	/// Constructor
	public:
		explicit		Actor();

	/// Methods
	protected:
		virtual void	updateCurrent(sf::Time deltaTime, CommandQueue& commands);

	public:
		/// Motion
		void			setVelocity(sf::Vector2f velocity);
		void			setVelocity(float velicityX, float velocityY);
		sf::Vector2f	getVelocity() const;
		void			setAcceleration(sf::Vector2f acceleration);
		void			setAcceleration(float accelrationX, float accelerationY);
		sf::Vector2f	getAcceleration() const;

		/// Gravity
		void			applyAcceleration(sf::Time deltaTime);

		/// Status
		float			getHealth() const;
		void			healHealth(float value);
		void			damageHealth(float value);

		/// Cleanup
		void			killSelf();
		virtual void	removeSelf();
		virtual bool	isDead() const;
	};
}