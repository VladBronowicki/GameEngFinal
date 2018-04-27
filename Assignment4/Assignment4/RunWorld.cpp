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
	mTarget.setView(mWorldView);
	mTarget.draw(mSceneGraph);
}

CommandQueue & RunWorld::getCommandQueue()
{
	return mCommandQueue;
}

bool RunWorld::hasAlivePlayer() const
{
	return true;
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
	mTextures.load(Textures::Run_BG, "Media/Textures/BG/bg.png");
	mTextures.load(Textures::Run_BG_Building1, "Media/Textures/BG/background_builidngs_1.png");
	mTextures.load(Textures::Run_BG_Building1, "Media/Textures/BG/background_builidngs_2.png");
	mTextures.load(Textures::Run_BG_Building1, "Media/Textures/BG/background_builidngs_3.png");
	mTextures.load(Textures::Run_Character_1, "Media/Textures/Character/run_1.png");
	mTextures.load(Textures::Run_Character_2, "Media/Textures/Character/run_2.png");
	mTextures.load(Textures::Run_Character_3, "Media/Textures/Character/run_3.png");
	mTextures.load(Textures::Run_Character_4, "Media/Textures/Character/run_4.png");
	mTextures.load(Textures::Run_Character_5, "Media/Textures/Character/run_5.png");
	mTextures.load(Textures::Run_Character_6, "Media/Textures/Character/run_6.png");
	mTextures.load(Textures::Run_Character_7, "Media/Textures/Character/run_7.png");
	mTextures.load(Textures::Run_Character_8, "Media/Textures/Character/run_8.png");
	mTextures.load(Textures::Run_Character_9, "Media/Textures/Character/run_9.png");
	mTextures.load(Textures::Run_Character_10, "Media/Textures/Character/run_10.png");
	mTextures.load(Textures::Run_Character_11, "Media/Textures/Character/run_11.png");
	mTextures.load(Textures::Run_Character_12, "Media/Textures/Character/run_12.png");

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


