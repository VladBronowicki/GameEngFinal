#ifndef BOOK_SETTINGSSTATE_HPP
#define BOOK_SETTINGSSTATE_HPP

#include <Book/State.hpp>
//TODO: REPLACE!
#include <Book/Player.hpp>
#include <Input/DefaultInput.hpp>
#include <Input/JoystickInput.hpp>
#include <Input/MouseInput.hpp>
#include <Book/Container.hpp>
#include <Book/Button.hpp>
#include <Book/Label.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State
{
	public:
										SettingsState(StateStack& stack, Context context);

		virtual void					draw();
		virtual bool					update(sf::Time dt);
		virtual bool					handleEvent(const sf::Event& event);


	private:
		void							updateLabels();
		void							addDefaultButtonLabel(INFINITYRUNNER::DefaultInput::Action action, float y, const std::string& text, Context context);
		void							addJoystickButtonLabel(INFINITYRUNNER::JoystickInput::Action action, float y, const std::string& text, Context context);
		void							addMouseButtonLabel(INFINITYRUNNER::MouseInput::Action action, float y, const std::string& text, Context context);


	private:
		sf::Sprite											mBackgroundSprite;
		GUI::Container										mGUIContainer;
		std::array<GUI::Button::Ptr, Player::ActionCount>	mBindingButtons;
		std::array<GUI::Label::Ptr, Player::ActionCount> 	mBindingLabels;
		std::array<GUI::Button::Ptr, INFINITYRUNNER::DefaultInput::ActionCount>		mDefaultBindingButtons;
		std::array<GUI::Label::Ptr, INFINITYRUNNER::DefaultInput::ActionCount> 		mDefaultBindingLabels;
		std::array<GUI::Button::Ptr, INFINITYRUNNER::JoystickInput::ActionCount>	mJoystickBindingButtons;
		std::array<GUI::Label::Ptr, INFINITYRUNNER::JoystickInput::ActionCount> 	mJoystickBindingLabels;
		std::array<GUI::Button::Ptr, INFINITYRUNNER::MouseInput::ActionCount>		mMouseBindingButtons;
		std::array<GUI::Label::Ptr, INFINITYRUNNER::MouseInput::ActionCount> 		mMouseBindingLabels;
};

#endif // BOOK_SETTINGSSTATE_HPP
