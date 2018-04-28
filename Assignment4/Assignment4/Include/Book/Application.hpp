#ifndef BOOK_APPLICATION_HPP
#define BOOK_APPLICATION_HPP

#include <Book/ResourceHolder.hpp>
#include <Book/ResourceIdentifiers.hpp>
#include <Input/DefaultInput.hpp>
#include <Input/JoystickInput.hpp>
#include <Input/MouseInput.hpp>
#include <Book/StateStack.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
	public:
								Application();
		void					run();
		

	private:
		void					processInput();
		void					update(sf::Time dt);
		void					render();

		void					updateStatistics(sf::Time dt);
		void					registerStates();


	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		TextureHolder			mTextures;
	  	FontHolder				mFonts;
		INFINITYRUNNER::DefaultInput	mDefaultInput;
		INFINITYRUNNER::JoystickInput	mJoystickInput;
		INFINITYRUNNER::MouseInput		mMouseInput;
		State::InputControllerState		mInputControllerState;

		StateStack				mStateStack;

		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
};

#endif // BOOK_APPLICATION_HPP
