#include <iostream>
#include <assert.h>

using namespace std;

class SingleObject {

private:
	static SingleObject* instance;

	//make the constructor private so that
	// this class cannot be instantiated
private:
	SingleObject() {}

public:
	//Get the only object available
	static SingleObject* getInstance() {
		if (instance == nullptr)
		{
			instance = new SingleObject();
		}
		return instance;
	}

	void showMessage() {
		cout << "Hello World!" << endl;
	}	
};
// static member of SingleObject class
SingleObject* SingleObject::instance = nullptr;



void main1(int argc, char ** argv)
{
	//illegal construct
	//Compile Time Error: The constructor SingleObject() is not visible
	//SingleObject* object = new SingleObject();

	//Get the only object available
	SingleObject* object = SingleObject::getInstance();
	assert(object != nullptr);

	//show the message
	object->showMessage();

	SingleObject* object2 = SingleObject::getInstance();
	assert(object == object2);
}
/* Output : 
Hello World!
*/

class AnotherSingleObject {

private:
	//make the constructor private so that this class cannot be
	//instantiated

	AnotherSingleObject() {}

public:
	//Get the only object available
	static AnotherSingleObject* getInstance() {
		static AnotherSingleObject instance;
		return &instance;
	}

	void showMessage() {
		cout << "Hello word" << endl;
	}
};