#include <iostream>
#include <map>
#include <vector>
#include <assert.h>

using namespace std;
typedef std::string String;

namespace templatemethod
{
	// Create an abstract class with a template method
	class Game {
	private:
		virtual void initialize() = 0;
		virtual void startPlay() = 0;
		virtual void endPlay() = 0;

	public:
		//template method
		void play() {

			//initialize the game
			initialize();

			//start game
			startPlay();

			//end game
			endPlay();
		}
	};

	// Create concrete classes extending the above class
	class Cricket: public Game {
	private:
		void endPlay() {
			cout << "Cricket Game Finished!" << endl;
		}


		void initialize() {
			cout << "Cricket Game Initialized! Start playing." << endl;
		}


		void startPlay() {
			cout << "Cricket Game Started. Enjoy the game!" << endl;
		}
	};

	class Football: public Game {
	private:

		void endPlay() {
			cout << "Football Game Finished!" << endl;
		}

		void initialize() {
			cout << "Football Game Initialized! Start playing." << endl;
		}

		void startPlay() {
			cout << "Football Game Started. Enjoy the game!" << endl;
		}
	};
}

using namespace templatemethod;

int main22(int argc, char ** argv)
{
	Game* game = new Cricket();
	game->play();
	delete game;
	cout << endl;
	
	game = new Football();
	game->play();
	delete game;

	return 0;
}

/* output : 

Cricket Game Initialized!Start playing.
Cricket Game Started.Enjoy the game!
Cricket Game Finished!

Football Game Initialized!Start playing.
Football Game Started.Enjoy the game!
Football Game Finished! */
