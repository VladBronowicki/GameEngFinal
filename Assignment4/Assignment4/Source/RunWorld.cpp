#include <Book\RunWorld.h>

#include <Book\Entity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <cfloat>

RunWorld::RunWorld(sf::RenderTarget & outputTarget, FontHolder & fonts) : mTarget(outputTarget)
, mSceneTexture()
, mWorldView(outputTarget.getDefaultView())
, mTextures()
, mFonts(fonts)
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f,mWorldView.getSize().x, mWorldView.getSize().y)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(0.0f)
{
	mSceneTexture.create(mTarget.getSize().x, mTarget.getSize().y);

	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void RunWorld::update(sf::Time dt)
{
	mWorldView.move(mScrollSpeed * dt.asSeconds(), .0f);
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
	mTextures.load(Textures::Run_BG_Building2, "Media/Textures/BG/background_builidngs_2.png");
	mTextures.load(Textures::Run_BG_Building3, "Media/Textures/BG/background_builidngs_3.png");
	//
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
	mTextures.load(Textures::Run_Character_Jump, "Media/Textures/Character/jump.png");
	mTextures.load(Textures::Run_Character_Slide, "Media/Textures/Character/slide.png");

	mTextures.load(Textures::Run_FG_instr, "Media/Textures/FG/title_instructions_building.png");
	mTextures.load(Textures::Run_FG_nowin1, "Media/Textures/FG/long_building_no_windows.png");
	mTextures.load(Textures::Run_FG_nowin2, "Media/Textures/FG/short_building_no_windows.png");
	mTextures.load(Textures::Run_FG_win1, "Media/Textures/FG/long_building_with_windows.png");
	mTextures.load(Textures::Run_FG_win2, "Media/Textures/FG/short_building_with_windows.png");

	mTextures.load(Textures::Run_Props_BlackBird, "Media/Textures/Props/black_bird.png");
	mTextures.load(Textures::Run_Props_Flowers, "Media/Textures/Props/flowers.png");
	mTextures.load(Textures::Run_Props_Lamp, "Media/Textures/Props/light_post.png");
	mTextures.load(Textures::Run_Props_HouseNoWin, "Media/Textures/Props/penthouse_no_window.png");
	mTextures.load(Textures::Run_Props_HouseWin, "Media/Textures/Props/penthouse_with_winow.png");
	mTextures.load(Textures::Run_Props_WhiteBird, "Media/Textures/Props/white_bird.png");

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
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		bool value = i == (int)Collision;
		Category::RunType category;
		if (value) {
			category = Category::Run_Foreground;
		}
		else {
			category = Category::Run_None;
		}
		

		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}
	sf::Texture& bgTexture = mTextures.get(Textures::Run_BG);
	bgTexture.setRepeated(true);
	
	float viewHeight = mWorldView.getSize().y;
	sf::IntRect textureRect(mWorldBounds);
	textureRect.height = bgTexture.getSize().y;
	textureRect.width = bgTexture.getSize().x;
	std::unique_ptr<SpriteNode> bgSprite(new SpriteNode(bgTexture, textureRect));
	bgSprite->setScale(mWorldView.getSize().x/bgTexture.getSize().x, mWorldView.getSize().y / bgTexture.getSize().y);
	//bgSprite->setPosition(mWorldBounds.left, mWorldBounds.top - viewHeight);
	
	mSceneLayers[Background]->attachChild(std::move(bgSprite));
}

void RunWorld::destroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Projectile | Category::EnemyAircraft;
	command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
	{
		if (!getLevelBounds().intersects(e.getBoundingRect()))
			e.remove();
	});

	mCommandQueue.push(command);
}

sf::FloatRect RunWorld::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect RunWorld::getLevelBounds() const
{
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}


