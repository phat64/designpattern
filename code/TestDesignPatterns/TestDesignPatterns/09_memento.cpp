#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;
typedef std::string String;

// Create Memento class
class Memento {
private:
	String state;

public:
	Memento(const String & state) {
		this->state = state;
	}

	const String& getState() {
		return state;
	}
};

// Create Originator class
class Originator {
private:
	String state;

public:
	void setState(const String & state) {
		this->state = state;
	}

	const String& getState() {
		return state;
	}

	Memento* saveStateToMemento() {
		return new Memento(state);
	}

	void getStateFromMemento(Memento* Memento) {
		state = Memento->getState();
	}
};

// Create CareTaker class (where Memento/state are saved)
class CareTaker {
private:
	vector<Memento*> mementoList;

public:
	void add(Memento* state) {
		mementoList.push_back(state);
	}

	Memento* get(int index) {
		return mementoList[index];
	}
};


//example
void main9(int argc, char** arg) {

	Originator originator;
	CareTaker careTaker;

	originator.setState("State #1");
	originator.setState("State #2");
	careTaker.add(originator.saveStateToMemento());

	originator.setState("State #3");
	careTaker.add(originator.saveStateToMemento());

	originator.setState("State #4");
	cout << "Current State: " << originator.getState().c_str() << endl;

	originator.getStateFromMemento(careTaker.get(0));
	cout << "First saved State: " << originator.getState().c_str() << endl;
	originator.getStateFromMemento(careTaker.get(1));
	cout << "Second saved State: " << originator.getState().c_str() << endl;
}

/*
Current State: State #4
First saved State: State #2
Second saved State: State #3
*/
