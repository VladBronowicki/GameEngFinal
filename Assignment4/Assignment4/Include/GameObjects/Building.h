#pragma once
#include <Book/Entity.hpp>
#include <Book/Command.hpp>
#include <Book/TextNode.hpp>
#include <Book/Animation.hpp>

#include <SFML/Graphics/Sprite.hpp>
class Building : public Entity
{
public:
	Building(const sf::Texture& texture);
	~Building();

private:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void 			updateCurrent(sf::Time dt, CommandQueue& commands);
	void					updateTexts();
	sf::Sprite				mSprite;
};
