#include "RunWorld.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cmath>
#include <limits>

RunWorld::RunWorld(sf::RenderTarget & outputTarget, FontHolder & fonts) : mTarget(outputTarget)
, mSceneTexture()
, mWorldView(outputTarget.getDefaultView())
, mTextures()
, mFonts(fonts)
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 5000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
{
	mSceneTexture.create(mTarget.getSize().x, mTarget.getSize().y);

	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void RunWorld::update(sf::Time dt)
{
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	destroyEntitiesOutsideView();
	handleCollisions();
	mSceneGraph.removeWrecks();
	mSceneGraph.update(dt, mCommandQueue);
	adaptPlayerPosition();

}

void RunWorld::draw()
{
}

CommandQueue & RunWorld::getCommandQueue()
{
	// TODO: insert return statement here
}

bool RunWorld::hasAlivePlayer() const
{
	return false;
}

bool RunWorld::hasPlayerReachedEnd() const
{
	return false;
}

RunWorld::~RunWorld()
{
}

void RunWorld::loadTextures()
{
}

void RunWorld::adaptPlayerPosition()
{
}

void RunWorld::adaptPlayerVelocity()
{
}

void RunWorld::handleCollisions()
{
}

void RunWorld::buildScene()
{
}

void RunWorld::destroyEntitiesOutsideView()
{
}

sf::FloatRect RunWorld::getViewBounds() const
{
	return sf::FloatRect();
}

sf::FloatRect RunWorld::getLevelBounds() const
{
	return sf::FloatRect();
}


