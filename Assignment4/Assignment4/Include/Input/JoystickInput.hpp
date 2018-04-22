#pragma once

//TODO: replace Book/Command.hpp with new command header
#include <Book/Command.hpp>
#include <Input/PlayerInputDataType.hpp>

#include <SFML/Window/Event.hpp>

#include <map>

/// Forward Declarations
class CommandQueue;

namespace INFINITYRUNNER {
	/// Default Player Input - Keyboard Input
	class JoystickInput
	{
		/// Enumerators
	public:
		enum Action
		{
			Slide,
			Jump,
			CycleUp,
			CycleDown,
			UseAbility,
			ActionCount
		};
		enum LevelStatus
		{
			LevelActive,
			LevelPassed,
			LevelFailed,
			LevelCancel,
			StatusCount
		};

		/// Attributes
	private:
		std::map<sf::Joystick::Axis, Action>	mKeyBinding;
		std::map<Action, Command>				mActionBinding;
		LevelStatus								mCurrentLevelStatus;

		/// Constructor
	public:
		JoystickInput();

		/// Input Methods
	public:
		void				handleInput(const sf::Event& input, CommandQueue& commands);
		void				handleDynamicInput(CommandQueue& commands);

		/// Keybind Methods
		void				assignKeybind(Action action, sf::Joystick::Axis key);
		sf::Joystick::Axis	getKeybind(Action action) const;
	private:
		void				initializeActions();
		static bool			isDynamicAction(Action action);

		/// Level Status Methods
	public:
		void				setLevelStatus(LevelStatus stat);
		LevelStatus			getLevelStatus() const;
	};

}