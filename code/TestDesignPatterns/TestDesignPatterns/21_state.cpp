#include <iostream>
#include <map>
#include <vector>
#include <assert.h>

using namespace std;
typedef std::string String;

namespace state
{
	enum Input
	{
		PRESS_A,
		PRESS_B,
		PRESS_LEFT,
		PRESS_RIGHT,
		PRESS_DOWN,
		RELEASE_A,
		RELEASE_DOWN,
	};

	enum Animate
	{
		IMAGE_JUMP,
		IMAGE_DUCK,
		IMAGE_STAND,
		IMAGE_DIVE
	};

	static const int JUMP_VELOCITY = 1;
	static const int MAX_CHARGE = 10;

	namespace Spaghetti5
	{
		class Heroine
		{
		public:
			void setGraphics(Animate animate) {}
			void handleInput(Input input);
			double yVelocity_;
			bool isJumping_;
			bool isDucking_;
		};

		//^spaghetti-5
		void Heroine::handleInput(Input input)
		{
			if (input == PRESS_B)
			{
				if (!isJumping_ && !isDucking_)
				{
					// Jump...
				}
			}
			else if (input == PRESS_DOWN)
			{
				if (!isJumping_)
				{
					isDucking_ = true;
					setGraphics(IMAGE_DUCK);
				}
				else
				{
					isJumping_ = false;
					setGraphics(IMAGE_DIVE);
				}
			}
			else if (input == RELEASE_DOWN)
			{
				if (isDucking_)
				{
					// Stand...
				}
			}
		}
		//^spaghetti-5
	}

	namespace FSM
	{
		//^enum
		enum State
		{
			STATE_STANDING,
			STATE_JUMPING,
			STATE_DUCKING,
			STATE_DIVING
		};
		//^enum

		class Heroine
		{
		public:
			void setGraphics(Animate animate) {}
			void superBomb() {}
			void handleInput(Input input);
			void update();
			double yVelocity_;
			State state_;
			int chargeTime_;

			void startDucking()
			{
				Input input = PRESS_DOWN;

				//^start-ducking
				// In standing state:
				if (input == PRESS_DOWN)
				{
					// Change state...
					chargeTime_ = 0;
					setGraphics(IMAGE_DUCK);
				}
				//^start-ducking
			}
		};

		//^state-switch
		void Heroine::handleInput(Input input)
		{
			switch (state_)
			{
			case STATE_STANDING:
				if (input == PRESS_B)
				{
					state_ = STATE_JUMPING;
					yVelocity_ = JUMP_VELOCITY;
					setGraphics(IMAGE_JUMP);
				}
				else if (input == PRESS_DOWN)
				{
					state_ = STATE_DUCKING;
					setGraphics(IMAGE_DUCK);
				}
				break;

			case STATE_JUMPING:
				if (input == PRESS_DOWN)
				{
					state_ = STATE_DIVING;
					setGraphics(IMAGE_DIVE);
				}
				break;

			case STATE_DUCKING:
				if (input == RELEASE_DOWN)
				{
					state_ = STATE_STANDING;
					setGraphics(IMAGE_STAND);
				}
				break;
				//^omit
			case STATE_DIVING:
				break;
				//^omit
			}
		}

		//^state-switch

		//^switch-update
		void Heroine::update()
		{
			if (state_ == STATE_DUCKING)
			{
				chargeTime_++;
				if (chargeTime_ > MAX_CHARGE)
				{
					superBomb();
				}
			}
		}
		//^switch-update
	}

	namespace StaticStateInstances
	{
		class HeroineState;
		class StandingState;
		class DuckingState;
		class JumpingState;
		class DivingState;

		class Heroine
		{
			friend class JumpingState;
		public:
			void setGraphics(Animate animate) {}
			void changeState(HeroineState* state) {}
		private:
			HeroineState* state_;
		};

		//^heroine-static-states
		class HeroineState
		{
		public:
			static StandingState standing;
			static DuckingState ducking;
			static JumpingState jumping;
			static DivingState diving;

			virtual void handleInput(Heroine& heroine, Input input) {}

			// Other code...
		};
		//^heroine-static-states

		class StandingState : public HeroineState {};
		class DuckingState : public HeroineState {};

		class JumpingState : public HeroineState {
		public:
			void handleInput(Heroine& heroine, Input input)
			{
				//^jump
				if (input == PRESS_B)
				{
					heroine.state_ = &HeroineState::jumping;
					heroine.setGraphics(IMAGE_JUMP);
				}
				//^jump
			}
		};
		class DivingState : public HeroineState {};
	}

}



int main21(int argc, char ** argv)
{
	return 0;
}

