#pragma once

#include <GameObjects/Actor.hpp>
#include <Book/Command.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/TextNode.hpp>
#include <Book/Animation.hpp>

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
			None		= 0,
			Running		= 1 << 0,
			Sliding		= 1 << 1,
			Jumping		= 1 << 2,
			Falling		= 1 << 3,
			Using		= 1 << 4,
			Dying		= 1 << 5,
			AnimCount	= 1 << 6
		};

	/// Attributes
	private:
		/// Visual
		Character			mCharacter;
		sf::Sprite			mSprite;
		std::vector<sf::Sprite>			mAnimRun;
		int					mCurrentRunFrame;
		int					mTotalRunFrames;
		sf::Sprite			mAnimSlide;
		sf::Sprite			mAnimJump;
		sf::Sprite			mAnimFall;
		sf::Sprite			mAnimUse;
		sf::Sprite			mAnimDie;
		bool 				mShowAnimRun;
		bool				mShowAnimSlide;
		bool				mShowAnimJump;
		bool				mShowAnimFall;
		bool				mShowAnimUse;
		bool				mShowAnimDeathSequence;
		AnimState			mActionState;

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
		//Ability*			mEquippedAbility;	TODO: can't figure out why this won't work yet
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
		virtual void 			updateCurrent(sf::Time deltaTime, CommandQueue& commands);
		void					updateMovementPattern(sf::Time deltaTime);
		void					checkAbilityDrop(CommandQueue& commands); //TODO: not sure if needed...
		void					checkForAction(sf::Time deltaTime, CommandQueue& commands);

		void					updateTexts();
		void					updateRunnerAnimation(sf::Time deltaTime);

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