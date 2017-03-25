#include <iostream>
#include <assert.h>

using namespace std;

// Interface
class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual void* next() = 0;
};

// Interface
class Container {
public:
	virtual Iterator* getIterator() = 0;
};

class NameIterator : public Iterator {
private:
	int index;
	char** names;

public:
	NameIterator(char ** _names) : index(0), names(_names)
	{}

	bool hasNext() {

		if (names[index]) {
			return true;
		}
		return false;
	}
	
	void* next() {

		if (this->hasNext()) {
			return (void*)names[index++];
		}
		return nullptr;
	}
};

class NameRepository : public Container {
public:
	Iterator* getIterator() {
		static char* names[] = {
			"Robert" ,
			"John" ,
			"Julie" ,
			"Lora",
			nullptr
		};

		return new NameIterator(names);
	}
};


// example
void main3(int argc, char ** argv)
{
	NameRepository* namesRepository = new NameRepository();

	Iterator* iter = namesRepository->getIterator();

	while (iter->hasNext()) {
		char* name = (char*)iter->next();
		cout << "Name : "<< name << endl;
	}
	delete iter;
	delete namesRepository;
}

/* Output :
Name : Robert
Name : John
Name : Julie
Name : Lora
*/