#include <Input/DefaultInput.hpp>
#include <Book/CommandQueue.hpp>
#include <GameObjects/Runner.hpp>
#include <Book/Foreach.hpp>

#include <map>
#include <string>
#include <algorithm>

using namespace std::placeholders;

INFINITYRUNNER::DefaultInput::DefaultInput()
	:mCurrentLevelStatus(LevelActive)
{
	// set bindings
	mKeyBinding[sf::Keyboard::Down] = Slide;
	mKeyBinding[sf::Keyboard::Up] = Jump;
	mKeyBinding[sf::Keyboard::PageDown] = CycleDown;
	mKeyBinding[sf::Keyboard::PageUp] = CycleUp;
	mKeyBinding[sf::Keyboard::Space] = UseAbility;

	// initialize actions
	initializeActions();

	// assign categories
	//TODO: create categories for new game
}

void INFINITYRUNNER::DefaultInput::handleInput(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isDynamicAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void INFINITYRUNNER::DefaultInput::handleDynamicInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	FOREACH(auto pair, mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isDynamicAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void INFINITYRUNNER::DefaultInput::assignKeybind(INFINITYRUNNER::DefaultInput::Action action, sf::Keyboard::Key key)
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

sf::Keyboard::Key INFINITYRUNNER::DefaultInput::getKeybind(INFINITYRUNNER::DefaultInput::Action action) const
{
	FOREACH(auto pair, mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void INFINITYRUNNER::DefaultInput::setLevelStatus(INFINITYRUNNER::DefaultInput::LevelStatus status)
{
	mCurrentLevelStatus = status;
}

INFINITYRUNNER::DefaultInput::LevelStatus INFINITYRUNNER::DefaultInput::getLevelStatus() const
{
	return mCurrentLevelStatus;
}

void INFINITYRUNNER::DefaultInput::initializeActions()
{
	//TODO: initialize successfully
	mActionBinding[Slide].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.slide(); });
	mActionBinding[Jump].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.jump(); });
	mActionBinding[CycleDown].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.cycleAbility(false); });
	mActionBinding[CycleUp].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.cycleAbility(true); });
	mActionBinding[UseAbility].action = derivedAction<Runner>([](Runner& r, sf::Time) { r.useAbility(); });
}

bool INFINITYRUNNER::DefaultInput::isDynamicAction(INFINITYRUNNER::DefaultInput::Action action)
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
