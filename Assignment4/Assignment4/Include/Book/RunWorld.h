#pragma once

#include <Book/ResourceHolder.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Book/SceneNode.hpp>
#include <Book/SpriteNode.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/Command.hpp>

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
	void								adaptPlayerVelocity();
	void								handleCollisions();

	void								buildScene();
	void								destroyEntitiesOutsideView();
	sf::FloatRect						getViewBounds() const;
	sf::FloatRect						getLevelBounds() const;

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
	float								mScrollSpeed;
};

