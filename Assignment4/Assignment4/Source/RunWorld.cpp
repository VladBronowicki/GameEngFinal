#include <Book\RunWorld.h>

#include <Book\Entity.hpp>

#include <GameObjects/Actor.hpp>
#include <Book/TextNode.hpp>
#include <Book/Foreach.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <GameObjects\Building.h>

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
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mSpawnLayer(Collision)
, mScrollSpeed(100.0f)
, mPlayerRunner(nullptr)
, mObstacleGenerators()
, mObstructions()
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
	mPlayerRunner->setVelocity(0.f, 0.f);
	destroyEntitiesOutsideView();
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity(dt);
	handleCollisions();
	mSceneGraph.removeWrecks();
	generateObstructions();
	mSceneGraph.update(dt, mCommandQueue);
	adaptPlayerPosition();

	mTimeCounter += dt.asMilliseconds();
	if ((int)mTimeCounter % ((rand()%250)+250) == 0) {
		printf("Spawning building...");
		loadBuildings();
	}



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
	return !mPlayerRunner->isReadyToDie();
}

bool RunWorld::hasPlayerReachedEnd() const
{
	return !mWorldBounds.contains(mPlayerRunner->getPosition());
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
	sf::FloatRect viewBounds = getViewBounds();
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerRunner->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerRunner->setPosition(position);

}

void RunWorld::adaptPlayerVelocity(sf::Time deltaTime)
{
	//TODO: possibly add gravity here

	// Add scrolling velocity
	mPlayerRunner->applyAcceleration(deltaTime);
}

bool matchesCategories(SceneNode::Pair& colliders, Category::RunType type1, Category::RunType type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void RunWorld::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	FOREACH(SceneNode::Pair pair, collisionPairs)
	{
		if (matchesCategories(pair, Category::Run_Player, Category::Run_Prop))
		{
			auto& player = static_cast<INFINITYRUNNER::Actor&>(*pair.first);
			auto& enemy = static_cast<INFINITYRUNNER::Obstruction&>(*pair.second);

			// Collision: Player damage = enemy's remaining HP
			player.damageHealth(enemy.getDamage());
			enemy.killSelf();
		}

	}
}

void RunWorld::loadBuildings()
{
	Textures::ID tx = Textures::Run_BG_Building1;
	int outPut = rand() % 3;
	switch (outPut) {
	case 0:
		tx = Textures::Run_BG_Building1;
		break;
	case 1:
		tx = Textures::Run_BG_Building2;
		break;
	case 2:
		tx = Textures::Run_BG_Building3;
		break;
	default:
		return;
	}

	sf::Texture& bgTexture = mTextures.get(tx);
	sf::IntRect textureRect(mWorldBounds);
	textureRect.height = bgTexture.getSize().y;
	textureRect.width = bgTexture.getSize().x;
	std::unique_ptr<Building> bgSprite(new Building(bgTexture));
	float scale = rand() % 5 / 100.f;
	bgSprite->setScale(.5f+scale, .5f+scale);
	bgSprite->setPosition(mWorldView.getSize().x + 100.f + ((mTimeCounter / 1000) * mScrollSpeed), (mWorldView.getSize().y - (bgTexture.getSize().y / 2)) + (rand()%50));
	bgSprite->setVelocity(mScrollSpeed / ((rand() % 10) + 2), 0);
	mSceneLayers[Background]->attachChild(std::move(bgSprite));
}

void RunWorld::loadBuildingsStart()
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
	std::unique_ptr<Building> bgSprite(new Building(bgTexture));
	bgSprite->setScale(mWorldView.getSize().x / bgTexture.getSize().x, mWorldView.getSize().y / bgTexture.getSize().y);
	bgSprite->setVelocity(mScrollSpeed, 0);
	mSceneLayers[Background]->attachChild(std::move(bgSprite));

	loadBuildings();
	loadBuildings();
	loadBuildings();
	loadBuildings();
	loadBuildings();
	loadBuildings();

	//PLAYER
	std::unique_ptr<INFINITYRUNNER::Runner> player(new INFINITYRUNNER::Runner(INFINITYRUNNER::Runner::Character::Professor, mTextures, mFonts));
	mPlayerRunner = player.get();
	mPlayerRunner->setPosition(mSpawnPosition);
	mSceneLayers[mSpawnLayer]->attachChild(std::move(player));

	placeObstructions();
}

void RunWorld::placeObstructions()
{
}

void RunWorld::placeObstruction(INFINITYRUNNER::Obstruction::ObjType type, float rX, float rY, Layer spawnLayer)
{
	ObstaclePoint gen(type, mSpawnPosition.x + rX, mSpawnPosition.y - rY, spawnLayer);
	mObstacleGenerators.push_back(gen);
}

void RunWorld::generateObstructions()
{
	while (!mObstacleGenerators.empty()
		&& mObstacleGenerators.back().originX > getLevelBounds().left)
	{
		ObstaclePoint gen = mObstacleGenerators.back();

		std::unique_ptr<INFINITYRUNNER::Obstruction> enemy(new INFINITYRUNNER::Obstruction(gen.objType, mTextures, mFonts));
		enemy->setPosition(gen.originX, gen.originY);
		//enemy->setRotation(180.f);

		mSceneLayers[gen.originLayer]->attachChild(std::move(enemy));

		// Enemy is spawned, remove from the list to spawn
		mObstacleGenerators.pop_back();
	}
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
	bounds.left -= 300.f;
	bounds.width += 300.f;

	return bounds;
}


