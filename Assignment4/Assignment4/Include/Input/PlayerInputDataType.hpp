#pragma once

namespace INFINITYRUNNER {
	/// Basic Player Input Data Structure
	struct BasicInput {
		bool slide;			// player slide input, executes slide action
		bool jump;			// player jump input, executes jump action

		BasicInput(bool _slide, bool _jump)
			: slide(_slide)
			, jump(_jump)
		{
			/// PlayerInput struct constructor
		}
	};

	/// Advanced Player Input Data Structure w/ Use PowerUp Ability
	struct AdvancedInput {
		bool slide;			// player slide input, executes slide action
		bool jump;			// player jump input, executes jump action
		int cyclePowerup;	// player cycle input, 1 = cycle up, -1 = cycle down
		bool usePowerup;	// player use input, executes use held powerup

		AdvancedInput(bool _slide, bool _jump, int _cyclePowerup, bool _usePowerup)
			: slide(_slide)
			, jump(_jump)
			, cyclePowerup(_cyclePowerup)
			, usePowerup(_usePowerup)
		{
			/// AdvancedInput struct constructor
		}
	};

}