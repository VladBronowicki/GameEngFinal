#pragma once

#include <Book/ResourceHolder.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/SceneNode.hpp>
#include <Book/SpriteNode.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/Command.hpp>
#include <GameObjects/Runner.hpp>
#include <GameObjects/Obstruction.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <array>
#include <queue>

namespace sf
{
	class RenderTarget;
	//class RenderTexture;
}

class RunWorld : private sf::NonCopyable
{
private:
	enum Layer
	{
		Background,
		BackgroundA,
		BackgroundB,
		Collision,
		Foreground,
		LayerCount
	};
	struct ObstaclePoint
	{
		ObstaclePoint(INFINITYRUNNER::Obstruction::ObjType type, float oX, float oY, Layer oLayer)
			: objType(type)
			, originX(oX)
			, originY(oY)
			, originLayer(oLayer)
		{
		}
		INFINITYRUNNER::Obstruction::ObjType objType;
		float originX;
		float originY;
		Layer originLayer;
	};

public:
	explicit							RunWorld(sf::RenderTarget& outputTarget, FontHolder& fonts);
	void								update(sf::Time dt);
	void								draw();

	CommandQueue&						getCommandQueue();

	bool 								hasAlivePlayer() const;
	bool 								hasPlayerReachedEnd() const;
	~RunWorld();

private:
	void								loadTextures();
	void								adaptPlayerPosition();
	void								adaptPlayerVelocity(sf::Time deltaTime);
	void								handleCollisions();
	void								loadBuildings();
	void								loadBuildingsStart();
	void								buildScene();
	void								placeObstructions();
	void								placeObstruction(INFINITYRUNNER::Obstruction::ObjType type, float rX, float rY, Layer spawnLayer);
	void								generateObstructions();
	void								destroyEntitiesOutsideView();
	sf::FloatRect						getViewBounds() const;
	sf::FloatRect						getLevelBounds() const;

private:
	sf::RenderTarget&					mTarget;
	sf::RenderTexture					mSceneTexture;
	sf::View							mWorldView;
	TextureHolder						mTextures;
	FontHolder&							mFonts;

	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	CommandQueue						mCommandQueue;

	sf::FloatRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;
	Layer								mSpawnLayer;
	float								mScrollSpeed;
	float								mTimeCounter = 0;
	INFINITYRUNNER::Runner*				mPlayerRunner;

	std::vector<ObstaclePoint>			mObstacleGenerators;
	std::vector<INFINITYRUNNER::Obstruction*>	mObstructions;
};

