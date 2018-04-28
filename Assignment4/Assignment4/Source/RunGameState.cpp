#include <Book\RunGameState.h>

#include <SFML/Graphics/RenderWindow.hpp>

RunGameState::RunGameState(StateStack & stack, Context context) : 
	State(stack, context)
, mWorld(*context.window, *context.fonts)
, mDefaultInput(*context.defaultInput)
, mJoystickInput(*context.joystickInput)
, mMouseInput(*context.mouseInput)
{
	mDefaultInput.setLevelStatus(INFINITYRUNNER::DefaultInput::LevelActive);
	mJoystickInput.setLevelStatus(INFINITYRUNNER::JoystickInput::LevelActive);
	mMouseInput.setLevelStatus(INFINITYRUNNER::MouseInput::LevelActive);
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
		mDefaultInput.setLevelStatus(INFINITYRUNNER::DefaultInput::LevelFailed);
		mJoystickInput.setLevelStatus(INFINITYRUNNER::JoystickInput::LevelFailed);
		mMouseInput.setLevelStatus(INFINITYRUNNER::MouseInput::LevelFailed);
		requestStackPush(States::GameOver);
	}
	else if (mWorld.hasPlayerReachedEnd())
	{
		mDefaultInput.setLevelStatus(INFINITYRUNNER::DefaultInput::LevelPassed);
		mJoystickInput.setLevelStatus(INFINITYRUNNER::JoystickInput::LevelPassed);
		mMouseInput.setLevelStatus(INFINITYRUNNER::MouseInput::LevelPassed);
		requestStackPush(States::GameOver);
	}

	CommandQueue& commands = mWorld.getCommandQueue();
	mDefaultInput.handleDynamicInput(commands);
	mJoystickInput.handleDynamicInput(commands);
	mMouseInput.handleDynamicInput(commands);

	return true;
}


bool RunGameState::handleEvent(const sf::Event & event)
{
	CommandQueue& commands = mWorld.getCommandQueue();
	mDefaultInput.handleInput(event, commands);
	mJoystickInput.handleInput(event, commands);
	mMouseInput.handleInput(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}
