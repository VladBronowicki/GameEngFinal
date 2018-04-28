#include <Book\RunGameState.h>

#include <SFML/Graphics/RenderWindow.hpp>

RunGameState::RunGameState(StateStack & stack, Context context) : 
	State(stack, context)
, mWorld(*context.window, *context.fonts)
{
}

RunGameState::~RunGameState()
{
}

void RunGameState::draw()
{
	mWorld.draw();
}

bool RunGameState::update(sf::Time dt)
{
	mWorld.update(dt);

	if (!mWorld.hasAlivePlayer())
	{
		requestStackPush(States::GameOver);
	}
	else if (mWorld.hasPlayerReachedEnd())
	{
		requestStackPush(States::GameOver);
	}

	CommandQueue& commands = mWorld.getCommandQueue();

	return true;
}


bool RunGameState::handleEvent(const sf::Event & event)
{
	CommandQueue& commands = mWorld.getCommandQueue();

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}
