#include <Book/GameState.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts)
, mPlayer(*context.player)
, mDefaultInput(*context.defaultInput)
, mJoystickInput(*context.joystickInput)
, mMouseInput(*context.mouseInput)
{
	mPlayer.setMissionStatus(Player::MissionRunning);	//TODO: get rid of player references
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
		mPlayer.setMissionStatus(Player::MissionFailure);
		mDefaultInput.setLevelStatus(INFINITYRUNNER::DefaultInput::LevelFailed);
		mJoystickInput.setLevelStatus(INFINITYRUNNER::JoystickInput::LevelFailed);
		mMouseInput.setLevelStatus(INFINITYRUNNER::MouseInput::LevelFailed);
		requestStackPush(States::GameOver);
	}
	else if (mWorld.hasPlayerReachedEnd())
	{
		mPlayer.setMissionStatus(Player::MissionSuccess);
		mDefaultInput.setLevelStatus(INFINITYRUNNER::DefaultInput::LevelPassed);
		mJoystickInput.setLevelStatus(INFINITYRUNNER::JoystickInput::LevelPassed);
		mMouseInput.setLevelStatus(INFINITYRUNNER::MouseInput::LevelPassed);
		requestStackPush(States::GameOver);
	}

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);
	mDefaultInput.handleDynamicInput(commands);
	mJoystickInput.handleDynamicInput(commands);
	mMouseInput.handleDynamicInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);
	mDefaultInput.handleInput(event, commands);
	mJoystickInput.handleInput(event, commands);
	mMouseInput.handleInput(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}