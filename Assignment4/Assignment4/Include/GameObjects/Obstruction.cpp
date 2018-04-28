#include <GameObjects/Obstruction.hpp>
#include <Book/DataTables.hpp>
#include <Book/Utility.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>


namespace INFINITYRUNNER
{
	const std::vector<ObstructionData> Table = initializeObstructionData();

}

INFINITYRUNNER::Obstruction::Obstruction(ObjType type, const TextureHolder & textures, const FontHolder & fonts)
	: Actor()
	, mObjType(type)
	, mSprite(textures.get(Table[type].texture), Table[type].textureBoundary)
	, mAnim(textures.get(Textures::Actors))
	, mShowAnim(false)
	, mAct()
	, mActCountdown(sf::Time::Zero)
	, mIsActing(false)
	, mDirectionalIndex(0)
{
	// Center origin of textures
	centerOrigin(mSprite);
	centerOrigin(mAnim);
}

void INFINITYRUNNER::Obstruction::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (mShowAnim)
		target.draw(mAnim, states);
	else
		target.draw(mSprite, states);
}

void INFINITYRUNNER::Obstruction::updateCurrent(sf::Time deltaTime, CommandQueue & commands)
{
	//TODO: Update text status?

	// Update animations
	if (mShowAnim)
		mAnim.update(deltaTime);

	// Update movement physics (no gravity)
	Actor::updateCurrent(deltaTime, commands);
}

void INFINITYRUNNER::Obstruction::updateMovementPattern(sf::Time deltaTime)
{
	//TODO: not implemented!
	//  we will probably axe this
}

void INFINITYRUNNER::Obstruction::updateAnimation(sf::Time deltaTime, int frames)
{
	//TODO: not tested!
	if (Table[mObjType].hasActAnimation)
	{
		sf::IntRect textureBoundary = Table[mObjType].textureBoundary;

		if (mIsActing)
		{
			mActCountdown -= deltaTime;
			if (mActCountdown < sf::Time::Zero)
				mActCountdown += Table[mObjType].actInterval;
		}

		int currentFrame = mActCountdown.asMilliseconds() * frames / Table[mObjType].actInterval.asMilliseconds();
	}
}

void INFINITYRUNNER::Obstruction::startActing()
{
	if (!mIsActing)
		mIsActing = true;
}

void INFINITYRUNNER::Obstruction::stopActing()
{
	if (mIsActing)
		mIsActing = false;
}

unsigned int INFINITYRUNNER::Obstruction::getCategory() const
{
	return 0;
}

sf::FloatRect INFINITYRUNNER::Obstruction::getObstructionBoundaries() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float INFINITYRUNNER::Obstruction::getMaxSpeed() const
{
	return Table[mObjType].velocity;
}

float INFINITYRUNNER::Obstruction::getDamage() const
{
	return Table[mObjType].damage;
}

void INFINITYRUNNER::Obstruction::removeSelf()
{
	Actor::removeSelf();
	mShowAnim = false;
}
