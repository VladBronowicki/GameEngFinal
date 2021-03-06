#pragma once

#include <GameObjects/Actor.hpp>
#include <Book/Command.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/Animation.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace INFINITYRUNNER {
	/// Runner class
	class Obstruction : public Actor
	{
		/// Enumerators
	public:
		enum ObjType
		{
			Hurdle,
			Limbo,
			Fire,
			TypeCount
		};

		/// Attributes
	private:
		/// Visual
		ObjType				mObjType;
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
		Obstruction(ObjType type, const TextureHolder& textures, const FontHolder& fonts);

		/// Methods
	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void 			updateCurrent(sf::Time deltaTime, CommandQueue& commands);
		void					updateMovementPattern(sf::Time deltaTime);
		void					updateAnimation(sf::Time deltaTime, int frames);

	public:
		/// Action
		void					startActing();
		void					stopActing();

		/// Status
		virtual unsigned int	getCategory() const;
		virtual sf::FloatRect	getObstructionBoundaries() const;
		float					getMaxSpeed() const;
		float					getDamage() const;

		/// Cleanup
		virtual void			removeSelf();

	};
}