#include <Book/SettingsState.hpp>
#include <Book/Utility.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
	
	//BINDINGS
	addDefaultButtonLabel(INFINITYRUNNER::DefaultInput::Slide,		300.f, "Slide(Keyboard)", context);
	addDefaultButtonLabel(INFINITYRUNNER::DefaultInput::Jump,		350.f, "Jump(Keyboard)", context);
	addJoystickButtonLabel(INFINITYRUNNER::JoystickInput::Slide,	400.f, "Slide(Joystick)", context);
	addJoystickButtonLabel(INFINITYRUNNER::JoystickInput::Jump,		450.f, "Jump(Joystick)", context);
	addMouseButtonLabel(INFINITYRUNNER::MouseInput::Slide,			500.f, "Slide(Mouse)", context);
	addMouseButtonLabel(INFINITYRUNNER::MouseInput::Jump,			550.f, "Jump(Mouse)", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setPosition(80.f, 620.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	mGUIContainer.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	
	//KEYBOARD
	for (std::size_t action = 0; action < INFINITYRUNNER::DefaultInput::ActionCount; ++action)
	{
		if (mDefaultBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().defaultInput->assignKeybind(static_cast<INFINITYRUNNER::DefaultInput::Action>(action), event.key.code);
				mDefaultBindingButtons[action]->deactivate();
			}
			break;
		}
	}
	//JOYSTICK
	for (std::size_t action = 0; action < INFINITYRUNNER::JoystickInput::ActionCount; ++action)
	{
		if (mJoystickBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::JoystickMoved)
			{
				getContext().joystickInput->assignKeybind(static_cast<INFINITYRUNNER::JoystickInput::Action>(action), event.joystickMove.axis);
				mJoystickBindingButtons[action]->deactivate();
			}
			break;
		}
	}
	//MOUSE
	for (std::size_t action = 0; action < INFINITYRUNNER::MouseInput::ActionCount; ++action)
	{
		if (mMouseBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::MouseButtonReleased)
			{
				getContext().mouseInput->assignKeybind(static_cast<INFINITYRUNNER::MouseInput::Action>(action), event.mouseButton.button);
				mMouseBindingButtons[action]->deactivate();
			}
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		updateLabels();
	else
		mGUIContainer.handleEvent(event);

	return false;
}

void SettingsState::updateLabels()
{
	//KEYBOARD
	INFINITYRUNNER::DefaultInput& defaultInput = *getContext().defaultInput;
	for (std::size_t index = 0; index < INFINITYRUNNER::DefaultInput::ActionCount; index++)
	{
		sf::Keyboard::Key key = defaultInput.getKeybind(static_cast<INFINITYRUNNER::DefaultInput::Action>(index));
		mBindingLabels[index]->setText(toString(key));
	}
	//JOYSTICK
	INFINITYRUNNER::JoystickInput& joystickInput = *getContext().joystickInput;
	for (std::size_t index = 0; index < INFINITYRUNNER::JoystickInput::ActionCount; index++)
	{
		sf::Joystick::Axis axis = joystickInput.getKeybind(static_cast<INFINITYRUNNER::JoystickInput::Action>(index));
		mBindingLabels[index + 2]->setText(toString(axis));
	}
	//MOUSE
	INFINITYRUNNER::MouseInput& mouseInput = *getContext().mouseInput;
	for (std::size_t index = 0; index < INFINITYRUNNER::MouseInput::ActionCount; index++)
	{
		sf::Mouse::Button button = mouseInput.getKeybind(static_cast<INFINITYRUNNER::MouseInput::Action>(index));
		mBindingLabels[index + 4]->setText(toString(button));
	}
}

void SettingsState::addDefaultButtonLabel(INFINITYRUNNER::DefaultInput::Action action, float y, const std::string & text, Context context)
{
	//KEYBOARD
	mDefaultBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mDefaultBindingButtons[action]->setPosition(50.f + float(action * 50), y);
	mDefaultBindingButtons[action]->setText(text);
	mDefaultBindingButtons[action]->setToggle(true);

	mDefaultBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mDefaultBindingLabels[action]->setPosition(300.f, y + 15.f);

	mGUIContainer.pack(mDefaultBindingButtons[action]);
	mGUIContainer.pack(mDefaultBindingLabels[action]);
}

void SettingsState::addJoystickButtonLabel(INFINITYRUNNER::JoystickInput::Action action, float y, const std::string & text, Context context)
{
	//JOYSTICK
	mJoystickBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mJoystickBindingButtons[action]->setPosition(250.f, y);
	mJoystickBindingButtons[action]->setText(text);
	mJoystickBindingButtons[action]->setToggle(true);

	mJoystickBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mJoystickBindingLabels[action]->setPosition(300.f, y + 15.f);

	mGUIContainer.pack(mJoystickBindingButtons[action]);
	mGUIContainer.pack(mJoystickBindingLabels[action]);
}

void SettingsState::addMouseButtonLabel(INFINITYRUNNER::MouseInput::Action action, float y, const std::string & text, Context context)
{
	//MOUSE
	mMouseBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mMouseBindingButtons[action]->setPosition(450.f, y);
	mMouseBindingButtons[action]->setText(text);
	mMouseBindingButtons[action]->setToggle(true);

	mMouseBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mMouseBindingLabels[action]->setPosition(300.f, y + 15.f);

	mGUIContainer.pack(mMouseBindingButtons[action]);
	mGUIContainer.pack(mMouseBindingLabels[action]);
}
