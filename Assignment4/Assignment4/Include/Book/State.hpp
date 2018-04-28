#ifndef BOOK_STATE_HPP
#define BOOK_STATE_HPP

#include <Book/StateIdentifiers.hpp>
#include <Book/ResourceIdentifiers.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
	class RenderWindow;
}

class StateStack;
class Player;

namespace INFINITYRUNNER
{
	class DefaultInput;
	class JoystickInput;
	class MouseInput;
}

class State
{
	public:
		enum InputControllerState
		{
			None				= 0,
			DefaultController	= 1 << 0,
			JoystickController	= 2 << 0,
			MouseController		= 3 << 0,
			PlayerController	= 4 << 0
		};
		typedef std::unique_ptr<State> Ptr;

		struct Context
		{
								Context(sf::RenderWindow& window
										, TextureHolder& textures
										, FontHolder& fonts
										, Player& player
										, INFINITYRUNNER::DefaultInput& defaultInput
										, INFINITYRUNNER::JoystickInput& joystickInput
										, INFINITYRUNNER::MouseInput& mouseInput
										, InputControllerState& inputControllerState);

			sf::RenderWindow*	window;
			TextureHolder*		textures;
			FontHolder*			fonts;
			Player*				player;
			INFINITYRUNNER::DefaultInput*	defaultInput;
			INFINITYRUNNER::JoystickInput*	joystickInput;
			INFINITYRUNNER::MouseInput*		mouseInput;
			InputControllerState*			inputControllerState;
		};


	public:
							State(StateStack& stack, Context context);
		virtual				~State();

		virtual void		draw() = 0;
		virtual bool		update(sf::Time dt) = 0;
		virtual bool		handleEvent(const sf::Event& event) = 0;


	protected:
		void				requestStackPush(States::ID stateID);
		void				requestStackPop();
		void				requestStateClear();

		Context				getContext() const;


	private:
		StateStack*			mStack;
		Context				mContext;
};

#endif // BOOK_STATE_HPP
