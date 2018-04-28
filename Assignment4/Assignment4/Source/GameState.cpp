#include <Book/GameState.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts)
, mDefaultInput(*context.defaultInput)
, mJoystickInput(*context.joystickInput)
, mMouseInput(*context.mouseInput)
{
	mDefaultInput.setLevelStatus(INFINITYRUNNER::DefaultInput::LevelActive);
	mJoystickInput.setLevelStatus(INFINITYRUNNER::JoystickInput::LevelActive);
	mMouseInput.setLevelStatus(INFINITYRUNNER::MouseInput::LevelActive);
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	if (!mWorld.hasAlivePlayer())
	{
		mDefaultInput.setLevelStatus(INFINITYRUNNER::DefaultInput::LevelFailed);
		mJoystickInput.setLevelStatus(INFINITYRUNNER::JoystickInput::LevelFailed);
		mMouseInput.setLevelStatus(INFINITYRUNNER::MouseInput::LevelFailed);
		//requestStackPush(States::GameOver);
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

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mDefaultInput.handleInput(event, commands);
	mJoystickInput.handleInput(event, commands);
	mMouseInput.handleInput(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}