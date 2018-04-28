#pragma once

#include <Book/State.hpp>
#include "RunWorld.h"
#include <Input/DefaultInput.hpp>
#include <Input/JoystickInput.hpp>
#include <Input/MouseInput.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class RunGameState : public State
{
public:
	RunGameState(StateStack& stack, Context context);
	~RunGameState();
	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	RunWorld				mWorld;
	INFINITYRUNNER::DefaultInput&	mDefaultInput;
	INFINITYRUNNER::JoystickInput&	mJoystickInput;
	INFINITYRUNNER::MouseInput&		mMouseInput;
};

