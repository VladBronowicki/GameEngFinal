#include <GameObjects/Runner.hpp>
#include <Book/DataTables.hpp>
#include <Book/Utility.hpp>
#include <GameObjects/Ability.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>


namespace INFINITYRUNNER
{
	const std::vector<RunnerData> Table = initializeRunnerData();

}

INFINITYRUNNER::Runner::Runner(Character type, const TextureHolder & textures, const FontHolder & fonts)
	: Actor()
	, mCharacter(type)
	, mSprite(textures.get(Table[type].texture), Table[type].textureBoundary)
	, mAnimRun(textures.get(Textures::Actors))
	, mAnimSlide(textures.get(Textures::Actors))
	, mAnimJump(textures.get(Textures::Actors))
	, mAnimUse(textures.get(Textures::Actors))
	, mShowAnimRun(false)
	, mShowAnimSlide(false)
	, mShowAnimJump(false)
	, mShowAnimUse(false)
	, mShowAnimDeathSequence(false)
	, mActionState(AnimState::None)
	, mRun()
	, mRunCountdown(sf::Time::Zero)
	//, mIsRunning(false)
	, mSlide()
	, mSlideCountdown(sf::Time::Zero)
	//, mIsSliding(false)
	, mJump()
	, mJumpCountdown(sf::Time::Zero)
	//, mIsJumping(false)
	, mUseAbility()
	, mAbilityCountdown(sf::Time::Zero)
	//, mIsUsingAbility(false)
	, mDeathSequenceCountdown(sf::Time::Zero)
	//, mIsDying(false)
	, mCycleDown()
	, mCycleDownCountdown(sf::Time::Zero)
	, mIsCyclingDownAbility(false)
	, mCycleUp()
	, mCycleUpCountdown(sf::Time::Zero)
	, mIsCyclingUpAbility(false)
	, mDirectionalIndex(0)
	, mHealthMeter(nullptr)
	, mAbilityMeter(nullptr)
	, mRunDistance(0.f)
	, mDistanceMeter(nullptr)
{
	//TODO: Implement initialization of textures and actions
}

void INFINITYRUNNER::Runner::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Character Animations: Only one should be active at a time.
	//  If no animation is active, a static sprite is rendered
	//  by default.
	switch (mActionState)
	{
	case AnimState::Running:
		target.draw(mAnimRun, states);
		break;
	case AnimState::Dying:
		target.draw(mAnimDie, states);
		break;
	case AnimState::Sliding:
		target.draw(mAnimSlide, states);
		break;
	case AnimState::Jumping:
		target.draw(mAnimJump, states);
		break;
	case AnimState::Falling:
		target.draw(mAnimFall, states);
		break;
	case AnimState::Using:
		target.draw(mAnimUse, states);
		break;
	default:
		target.draw(mSprite, states);
	}
}

void INFINITYRUNNER::Runner::updateCurrent(sf::Time deltaTime, CommandQueue& commands, bool applyGravity)
{
	//TODO: Update text status?
	
	//Update animations
	switch (mActionState)
	{
	case AnimState::Running:
		mAnimRun.update(deltaTime);
		break;
	case AnimState::Dying:
		mAnimDie.update(deltaTime);
		break;
	case AnimState::Sliding:
		mAnimSlide.update(deltaTime);
		break;
	case AnimState::Jumping:
		mAnimJump.update(deltaTime);
		break;
	case AnimState::Falling:
		mAnimFall.update(deltaTime);
		break;
	case AnimState::Using:
		mAnimDie.update(deltaTime);
		break;
	default:;
	}

	// Update movement physics
	Actor::updateCurrent(deltaTime, commands, applyGravity);
}

void INFINITYRUNNER::Runner::updateMovementPattern(sf::Time deltaTime)
{
	//TODO: not implemented!
	//  may not be required for this release if we have no ai runners
}

void INFINITYRUNNER::Runner::checkAbilityDrop(CommandQueue & commands)
{
	//TODO: not implemented!
	//  may not be required for this release if we have no ai runners
}

void INFINITYRUNNER::Runner::checkForAction(sf::Time deltaTime, CommandQueue & commands)
{
	// ABILITY
	// Check for ability ready
	if ((AnimState::Using & mActionState) == AnimState::Using
		&& mAbilityCountdown <= sf::Time::Zero)
	{
		// ready - use!
		commands.push(mUseAbility);
		mAbilityCountdown += Table[mCharacter].abilityInterval;
		mActionState = AnimState(mActionState - AnimState::Using);
	}
	else if (mAbilityCountdown > sf::Time::Zero)
	{
		// not ready - hold!
		mAbilityCountdown -= deltaTime;
		mActionState = AnimState(mActionState - AnimState::Using);
	}
	// JUMP
	// Check for jump action ready
	if ((AnimState::Jumping & mActionState) == AnimState::Jumping
		&& (AnimState::Falling & mActionState) != AnimState::Falling
		&& mJumpCountdown <= sf::Time::Zero)
	{
		// ready - jump!
		commands.push(mJump);
		mJumpCountdown += Table[mCharacter].jumpInterval;
		mActionState = AnimState(mActionState - AnimState::Jumping);
	}
	else if (mJumpCountdown > sf::Time::Zero)
	{
		// not ready - don't jump!
		mJumpCountdown -= deltaTime;
		mActionState = AnimState(mActionState - AnimState::Jumping);
	}
	// SLIDE
	// Check for slide action ready
	if ((AnimState::Sliding & mActionState) == AnimState::Sliding
		&& (AnimState::Jumping & mActionState) != AnimState::Jumping
		&& (AnimState::Falling & mActionState) != AnimState::Falling
		&& mSlideCountdown <= sf::Time::Zero)
	{
		// ready - slide!
		commands.push(mSlide);
		mSlideCountdown += Table[mCharacter].slideInterval;
		mActionState = AnimState(mActionState - AnimState::Sliding);
	}
	else if (mSlideCountdown > sf::Time::Zero)
	{
		// not ready - don't slide!
		mSlideCountdown -= deltaTime;
		mActionState = AnimState(mActionState - AnimState::Sliding);
	}
}

void INFINITYRUNNER::Runner::updateTexts()
{
	//TODO: we will need to test the orientation of text
	// health
	if (isDead())
	{
		mHealthMeter->setString("");
		mAbilityMeter->setString("");
		mDistanceMeter->setString("");
	}
	else
	{
		if (mHealthMeter)
		{
			mHealthMeter->setString(toString(getHealth()) + " ST");
		}
		if (mAbilityMeter)
		{
			//TODO: should display Ability.type (ability not yet implemented!)
			//mAbilityMeter->setString(" Ability: " + toString(mEquippedAbility));
		}
		if (mDistanceMeter)
		{
			mDistanceMeter->setString("Distance: " + toString(mRunDistance));
		}
	}
}

void INFINITYRUNNER::Runner::updateRunnerAnimation(sf::Time deltaTime, int frames)
{
	//TODO: not tested!
	if (Table[mCharacter].hasRunAnimation)
	{
		sf::IntRect textureBoundary = Table[mCharacter].textureBoundary;

		// make sure runner is running
		if ((AnimState::Running & mActionState) == AnimState::Running
			&& (AnimState::Jumping & mActionState) != AnimState::Jumping
			&& (AnimState::Falling & mActionState) != AnimState::Falling
			&& (AnimState::Sliding & mActionState) != AnimState::Sliding
			&& (AnimState::Using & mActionState) != AnimState::Using)
		{
			mRunCountdown -= deltaTime;
			if (mRunCountdown < sf::Time::Zero)
				mRunCountdown += Table[mCharacter].runInterval;
		}

		int currentFrame = mRunCountdown.asMilliseconds() * frames / Table[mCharacter].runInterval.asMilliseconds();
	}
}

void INFINITYRUNNER::Runner::startRunning()
{
	if ((AnimState::Running & mActionState) != AnimState::Running)
		mActionState = AnimState(mActionState + AnimState::Running);
}

void INFINITYRUNNER::Runner::stopRunning()
{
	if ((AnimState::Running & mActionState) == AnimState::Running)
		mActionState = AnimState(mActionState - AnimState::Running);
}

void INFINITYRUNNER::Runner::slide()
{
	if ((AnimState::Sliding & mActionState) != AnimState::Sliding)
		mActionState = AnimState(mActionState + AnimState::Sliding);
}

void INFINITYRUNNER::Runner::jump()
{
	if ((AnimState::Jumping & mActionState) != AnimState::Jumping)
		mActionState = AnimState(mActionState + AnimState::Jumping);
}

void INFINITYRUNNER::Runner::cycleAbility(bool cycleUp)
{
	//TODO: not implemented!
	//  to be removed - we will only allow one equip at a time
}

void INFINITYRUNNER::Runner::collectAbility(unsigned int count)
{
	//TODO: not implemented!
	//  need to develop ability first
}

void INFINITYRUNNER::Runner::useAbility()
{
	//TODO: not implemented!
	//  need to develop ability first
}

unsigned int INFINITYRUNNER::Runner::getCategory() const
{
	//if (isPlayerRunner())
	//	return ElementClassification::PlayerRunner;
	//else if (isAllyRunner())
	//	return ElementClassification::FriendlyRunner;
	//else
	//	return ElementClassification::RivalRunner;
	return mCharacter;
}

sf::FloatRect INFINITYRUNNER::Runner::getCharacterBoundaries() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float INFINITYRUNNER::Runner::getMaxSpeed() const
{
	return Table[mCharacter].velocity;
}

bool INFINITYRUNNER::Runner::isPlayerRunner() const
{
	return mCharacter == Professor;
}

bool INFINITYRUNNER::Runner::isAllyRunner() const
{
	return mCharacter == Scientist;
}

bool INFINITYRUNNER::Runner::isReadyToDie() const
{
	return isDead() && (mAnimDie.isFinished() || !mShowAnimDeathSequence);
}

void INFINITYRUNNER::Runner::removeSelf()
{
	Actor::removeSelf();
	mShowAnimDeathSequence = false;
}
