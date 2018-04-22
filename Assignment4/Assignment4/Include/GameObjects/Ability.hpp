#pragma once

#include <GameObjects/Actor.hpp>
#include <Book/Command.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/Animation.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace INFINITYRUNNER {
	/// Runner class
	class Ability : public Actor
	{
	/// Enumerators
	public:
		enum PickupType
		{
			Regeneration,
			Barrier,
			Destruction,
			FreezeTime,
			TypeCount
		};

	/// Attributes
	private:
		/// Visual
		PickupType			mPickupType;
		sf::Sprite			mSprite;
		Animation			mAnim;
		bool 				mShowAnim;

		/// Action
		Command 			mAct;
		sf::Time			mActCountdown;
		bool 				mIsActing;

		/// Status
		std::size_t			mDirectionalIndex;

	/// Constructor
	public:
		Ability(PickupType type, const TextureHolder& textures, const FontHolder& fonts);

	/// Methods
	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void 			updateCurrent(sf::Time deltaTime, CommandQueue& commands);
		void					updateMovementPattern(sf::Time deltaTime);
		void					updateAnimation();

	public:
		/// Action
		void					startActing();
		void					stopActing();
		void					imbueEffect(Actor& actor) const;

		/// Status
		virtual unsigned int	getCategory() const;
		virtual sf::FloatRect	getBoundingRect() const;
		float					getMaxSpeed() const;
		float					getDamage() const;

		/// Cleanup
		virtual void			removeSelf();
		virtual bool			isDead() const;

	};
}