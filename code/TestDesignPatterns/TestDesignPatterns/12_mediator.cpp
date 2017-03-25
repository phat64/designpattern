/*#include <vector>
#include <string>
#include <iostream>

using namespace std;
typedef std::string String;

class User;

class Date
{
public:
	static const char* now() { return ""; }
};

 // create a concrete class
class User {
private:
	String name;

public:
	const String & getName(){
		return name;
	}

	void setName(const String & name) {
		this->name = name;
	}

	User(const String & name) {
		this->name = name;
	}

	void sendMessage(const String & message) {
		ChatRoom::showMessage(this, message);
	}
};

// Mediator class
class ChatRoom {
public:
	static void showMessage(User* user, const String & message) {
		cout << Date::now() << " [" <<	user->getName().c_str()
			<< "] : " <<message.c_str() << endl;
	}
};

// example
void main(int argc, char ** argv) {
	User robert ("Robert");
	User john("John");

	robert.sendMessage("Hi! John!");
	john.sendMessage("Hello! Robert!");
}
*/
/* Output :
Thu Jan 31 16:05:46 IST 2013 [Robert] : Hi! John!
Thu Jan 31 16:05:46 IST 2013 [John] : Hello! Robert!
*/

