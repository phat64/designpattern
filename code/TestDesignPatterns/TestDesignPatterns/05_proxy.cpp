#include <iostream>
#include <assert.h>

using namespace std;
typedef std::string String;

#define SafeDelete(ptr) if (ptr){ delete ptr; ptr = nullptr; }

// Create an interface
class Image {
public:
	virtual ~Image() {}
	virtual void display() = 0;
};

// Create concrete classes implementing the same interface.
class RealImage : public Image {

private:
	String fileName;

public:
	RealImage(const String& fileName) {
		this->fileName = fileName;
		loadFromDisk(fileName);
	}

	virtual ~RealImage() {}

	void display() {
		cout << "Displaying " << fileName.c_str() << endl;
	}

	void loadFromDisk(const String& fileName) {
		cout << "Loading " << fileName.c_str() << endl;
	}
};

// Create a Proxy
class ProxyImage : public Image {

private:
	RealImage* realImage;
	String fileName;

public:
	ProxyImage(const String& fileName) : realImage(nullptr) {
		this->fileName = fileName;
	}

	virtual ~ProxyImage() {	SafeDelete(realImage);}

	void display() {
		if (realImage == nullptr) {
			realImage = new RealImage(fileName);
		}
		realImage->display();
	}
};

int main5(int argc, char ** argv)
{
	Image* image = new ProxyImage("test_10mb.jpg");

	//image will be loaded from disk
	image->display();
	cout << endl;

	//image will not be loaded from disk
	image->display();

	delete image;

	return 0;
}

/* Output:
Loading test_10mb.jpg
Displaying test_10mb.jpg

Displaying test_10mb.jpg
*/