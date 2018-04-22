#include <Input/MouseInput.hpp>
#include <Book/CommandQueue.hpp>
#include <GameObjects/Runner.hpp>
#include <Book/Foreach.hpp>

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;

INFINITYRUNNER::MouseInput::MouseInput()
	:mCurrentLevelStatus(LevelActive)
{
	// set bindings
	mKeyBinding[sf::Mouse::Left] = Slide;
	mKeyBinding[sf::Mouse::Right] = Jump;
	mKeyBinding[sf::Mouse::XButton2] = CycleDown;
	mKeyBinding[sf::Mouse::XButton1] = CycleUp;
	mKeyBinding[sf::Mouse::Middle] = UseAbility;

	// initialize actions
	initializeActions();

	// assign categories
	//TODO: create categories for new game
}

void INFINITYRUNNER::MouseInput::handleInput(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.mouseButton.button);
		if (found != mKeyBinding.end() && !isDynamicAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void INFINITYRUNNER::MouseInput::handleDynamicInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	FOREACH(auto pair, mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Mouse::isButtonPressed(pair.first) && isDynamicAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void INFINITYRUNNER::MouseInput::assignKeybind(INFINITYRUNNER::MouseInput::Action action, sf::Mouse::Button key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Mouse::Button INFINITYRUNNER::MouseInput::getKeybind(INFINITYRUNNER::MouseInput::Action action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	//TODO: Mouse has no unknown button option???
	return sf::Mouse::XButton2;
}

void INFINITYRUNNER::MouseInput::setLevelStatus(INFINITYRUNNER::MouseInput::LevelStatus status)
{
	mCurrentLevelStatus = status;
}

INFINITYRUNNER::MouseInput::LevelStatus INFINITYRUNNER::MouseInput::getLevelStatus() const
{
	return mCurrentLevelStatus;
}

void INFINITYRUNNER::MouseInput::initializeActions()
{
	mActionBinding[Slide].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.slide(); });
	mActionBinding[Jump].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.jump(); });
	mActionBinding[CycleDown].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.cycleAbility(false); });
	mActionBinding[CycleUp].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.cycleAbility(true); });
	mActionBinding[UseAbility].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.useAbility(); });
}

bool INFINITYRUNNER::MouseInput::isDynamicAction(INFINITYRUNNER::MouseInput::Action action)
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
