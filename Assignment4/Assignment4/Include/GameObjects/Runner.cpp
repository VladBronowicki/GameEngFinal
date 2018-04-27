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
	, mAnimationState(AnimState::None)
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
	switch (mAnimationState)
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
	switch (mAnimationState)
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
}

void INFINITYRUNNER::Runner::checkPickupDrop(CommandQueue & commands)
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::checkAbilityUse(sf::Time deltaTime, CommandQueue & commands)
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::updateTexts()
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::updateRunnerAnimation()
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::startRunning()
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::stopRunning()
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::slide()
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::jump()
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::cycleAbility(bool cycleUp)
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::collectAbility(unsigned int count)
{
	//TODO: not implemented!
}

void INFINITYRUNNER::Runner::useAbility()
{
	//TODO: not implemented!
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
