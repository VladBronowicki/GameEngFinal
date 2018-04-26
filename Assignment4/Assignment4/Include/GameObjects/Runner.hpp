#pragma once

#include <GameObjects/Actor.hpp>
#include <Book/Command.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/Projectile.hpp>
#include <Book/TextNode.hpp>
#include <Book/Animation.hpp>
#include <Book/Pickup.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace INFINITYRUNNER {
	/// Runner class
	class Runner : public Actor
	{
	/// Enumerators
	public:
		enum Character
		{
			Professor,
			Scientist,
			Soldier,
			TypeCount
		};

		enum AnimState
		{
			None,
			Running,
			Sliding,
			Jumping,
			Falling,
			Using,
			Dying,
			AnimCount
		};

	/// Attributes
	private:
		/// Visual
		Character			mCharacter;
		sf::Sprite			mSprite;
		Animation			mAnimRun;
		Animation			mAnimSlide;
		Animation			mAnimJump;
		Animation			mAnimFall;
		Animation			mAnimUse;
		Animation			mAnimDie;
		bool 				mShowAnimRun;
		bool				mShowAnimSlide;
		bool				mShowAnimJump;
		bool				mShowAnimFall;
		bool				mShowAnimUse;
		bool				mShowAnimDeathSequence;
		AnimState			mAnimationState;

		/// Action
		Command				mRun;
		sf::Time			mRunCountdown;
		//bool				mIsRunning;
		Command				mSlide;
		sf::Time			mSlideCountdown;
		//bool				mIsSliding;
		Command				mJump;
		sf::Time			mJumpCountdown;
		//bool				mIsJumping;
		Command 			mUseAbility;
		sf::Time			mAbilityCountdown;
		//bool 				mIsUsingAbility;
		sf::Time			mDeathSequenceCountdown;
		//bool				mIsDying;

		/// Cycling
		Command				mCycleUp;
		sf::Time			mCycleUpCountdown;
		bool				mIsCyclingUpAbility;
		Command				mCycleDown;
		sf::Time			mCycleDownCountdown;
		bool				mIsCyclingDownAbility;

		/// Status
		sf::Time			mDeathCycle;
		std::size_t			mDirectionalIndex;
		TextNode*			mHealthMeter;
		TextNode*			mAbilityMeter;
		float				mRunDistance;
		TextNode*			mDistanceMeter;

	/// Constructor
	public:
		Runner(Character type, const TextureHolder& textures, const FontHolder& fonts);

	/// Methods
	private:
		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void 			updateCurrent(sf::Time deltaTime, CommandQueue& commands, bool applyGravity);
		void					updateMovementPattern(sf::Time deltaTime);
		void					checkPickupDrop(CommandQueue& commands); //TODO: not sure if needed...
		void					checkAbilityUse(sf::Time deltaTime, CommandQueue& commands);

		void					updateTexts();
		void					updateRunnerAnimation();

	public:
		/// Action
		void					startRunning();
		void					stopRunning();
		void					slide();
		void					jump();
		void					cycleAbility(bool cycleUp);
		void					collectAbility(unsigned int count);
		void 					useAbility();

		/// Status
		virtual unsigned int	getCategory() const;
		virtual sf::FloatRect	getCharacterBoundaries() const;
		float					getMaxSpeed() const;
		bool					isPlayerRunner() const;
		bool					isAllyRunner() const;

		/// Cleanup
		virtual bool			isReadyToDie() const;
		virtual void			removeSelf();

	};
}