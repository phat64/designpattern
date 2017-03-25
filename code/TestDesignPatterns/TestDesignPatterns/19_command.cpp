#include <iostream>
#include <map>
#include <vector>
#include <assert.h>

using namespace std;
typedef std::string String;
namespace nocommand {

	enum BUTTON
	{
		BUTTON_X = 0,
		BUTTON_Y,
		BUTTON_A,
		BUTTON_B,
		BUTTON_COUNT
	};

	class Hero
	{
	public:
		void jump() {}
		void fireGun() {}
		void swapWeapon() {}
		void lurchIneffectively() {}
	};

	class InputHandler
	{
	public:

		void handleInput(Hero * hero)
		{
			if (isPressed(BUTTON_X)) hero->jump();
			else if (isPressed(BUTTON_Y)) hero->fireGun();
			else if (isPressed(BUTTON_A)) hero->swapWeapon();
			else if (isPressed(BUTTON_B)) hero->lurchIneffectively();
		}

		bool isPressed(enum BUTTON button) 
		{
			return buttonStates[button];
		}

	private:
		bool buttonStates[BUTTON_COUNT];
	};
}


namespace command {

	enum BUTTON
	{
		BUTTON_X = 0,
		BUTTON_Y,
		BUTTON_A,
		BUTTON_B,
		BUTTON_COUNT
	};


	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute() = 0;
	};

	class Hero
	{
	public:
		void jump() {}
		void fireGun() {}
		void swapWeapon() {}
		void lurchIneffectively() {}
	};

	class JumpCommand : public Command
	{
	public:
		JumpCommand(Hero* h) :hero(h) {}
		virtual void execute() { hero->jump(); }
	private:
		Hero* hero;
	};

	class FireCommand : public Command
	{
	public:
		FireCommand(Hero* h) :hero(h) {}
		virtual void execute() { hero->fireGun(); }
	private:
		Hero* hero;
	};

	class SwapWeaponCommand : public Command
	{
	public:
		SwapWeaponCommand(Hero* h) :hero(h) {}
		virtual void execute() { hero->swapWeapon(); }
	private:
		Hero* hero;
	};

	class LurchIneffectivelyCommand : public Command
	{
	public:
		LurchIneffectivelyCommand(Hero* h) :hero(h) {}
		virtual void execute() { hero->lurchIneffectively(); }

	private:
		Hero* hero;
	};


	class InputHandler
	{
	public:

		InputHandler(Hero * h)
		{
			buttonX = new JumpCommand(h);
			buttonY = new FireCommand(h);
			buttonA = new SwapWeaponCommand(h);
			buttonB = new LurchIneffectivelyCommand(h);
		}

		~InputHandler()
		{
			delete buttonX;
			delete buttonY;
			delete buttonA;
			delete buttonB;
		}

		void handleInput(Hero * hero)
		{
			if (isPressed(BUTTON_X)) buttonX->execute();
			else if (isPressed(BUTTON_Y)) buttonY->execute();
			else if (isPressed(BUTTON_A)) buttonA->execute();
			else if (isPressed(BUTTON_B)) buttonB->execute();
		}

		bool isPressed(enum BUTTON button)
		{
			return buttonStates[button];
		}

	private:
		bool buttonStates[BUTTON_COUNT];

		Command* buttonX;
		Command* buttonY;
		Command* buttonA;
		Command* buttonB;
	};
}

int main19()
{
	//...
	return 0;
}