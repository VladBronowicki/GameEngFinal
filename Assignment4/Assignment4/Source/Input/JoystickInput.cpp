#include <Input/JoystickInput.hpp>
#include <Book/CommandQueue.hpp>
#include <GameObjects/Runner.hpp>
#include <Book/Foreach.hpp>

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;

INFINITYRUNNER::JoystickInput::JoystickInput()
	:mCurrentLevelStatus(LevelActive)
{
	// set bindings
	mKeyBinding[sf::Joystick::X] = Slide;
	mKeyBinding[sf::Joystick::Y] = Jump;
	mKeyBinding[sf::Joystick::R] = CycleDown;
	mKeyBinding[sf::Joystick::U] = CycleUp;
	mKeyBinding[sf::Joystick::Z] = UseAbility;

	// initialize actions
	initializeActions();

	// assign categories
	//TODO: create categories for new game
}

void INFINITYRUNNER::JoystickInput::handleInput(const sf::Event& event, CommandQueue& commands)
{
	// not implemented
}

void INFINITYRUNNER::JoystickInput::handleDynamicInput(CommandQueue& commands)
{
	// not implemented
}

void INFINITYRUNNER::JoystickInput::assignKeybind(INFINITYRUNNER::JoystickInput::Action action, sf::Joystick::Axis key)
{
	// not implemented
}

sf::Joystick::Axis INFINITYRUNNER::JoystickInput::getKeybind(INFINITYRUNNER::JoystickInput::Action action) const
{
	// not implemented
	return sf::Joystick::Z;
}

void INFINITYRUNNER::JoystickInput::setLevelStatus(INFINITYRUNNER::JoystickInput::LevelStatus status)
{
	mCurrentLevelStatus = status;
}

INFINITYRUNNER::JoystickInput::LevelStatus INFINITYRUNNER::JoystickInput::getLevelStatus() const
{
	return mCurrentLevelStatus;
}

void INFINITYRUNNER::JoystickInput::initializeActions()
{
	//TODO: initialize properly
	mActionBinding[Slide].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.slide(); });
	mActionBinding[Jump].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.jump(); });
	mActionBinding[CycleDown].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.cycleAbility(false); });
	mActionBinding[CycleUp].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.cycleAbility(true); });
	mActionBinding[UseAbility].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.useAbility(); });
}

bool INFINITYRUNNER::JoystickInput::isDynamicAction(INFINITYRUNNER::JoystickInput::Action action)
{
	switch (action)
	{
	case Slide:
	case Jump:
	case UseAbility:
		return true;

	default:
		return false;
	}
}
