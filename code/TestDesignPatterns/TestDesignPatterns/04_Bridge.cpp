#include <iostream>
#include <assert.h>

using namespace std;

/* Implemented interface. */
class AbstractInterface
{
public:
	virtual void someFunctionality() = 0;
};

/* Interface for internal implementation that Bridge uses. */
class ImplementationInterface
{
public:
	virtual void anotherFunctionality() = 0;
};

/* The Bridge */
class Bridge : public AbstractInterface
{
protected:
	ImplementationInterface* implementation;

public:
	Bridge(ImplementationInterface* backend)
	{
		implementation = backend;
	}
};

class UseCase1 : public Bridge
{
public:
	UseCase1(ImplementationInterface* backend)
		: Bridge(backend)
	{}

	void someFunctionality()
	{
		std::cout << "UseCase1 on ";
		implementation->anotherFunctionality();
	}
};

class UseCase2 : public Bridge
{
public:
	UseCase2(ImplementationInterface* backend)
		: Bridge(backend)
	{}

	void someFunctionality()
	{
		std::cout << "UseCase2 on ";
		implementation->anotherFunctionality();
	}
};


/* Different background implementations. */

class Windows : public ImplementationInterface
{
public:
	void anotherFunctionality()
	{
		std::cout << "Windows" << std::endl;
	}
};

class Linux : public ImplementationInterface
{
public:
	void anotherFunctionality()
	{
		std::cout << "Linux" << std::endl;
	}
};

int main4()
{
	AbstractInterface *useCase = 0;
	ImplementationInterface *osWindows = new Windows;
	ImplementationInterface *osLinux = new Linux;


	/* First case */
	useCase = new UseCase1(osWindows);
	useCase->someFunctionality();
	delete useCase;

	useCase = new UseCase1(osLinux);
	useCase->someFunctionality();
	delete useCase;

	/* Second case */
	useCase = new UseCase2(osWindows);
	useCase->someFunctionality();
	delete useCase;

	useCase = new UseCase2(osLinux);
	useCase->someFunctionality();
	delete useCase;

	delete osWindows;
	delete osLinux;

	return 0;
}

/* Output : 
UseCase1 on Windows
UseCase1 on Linux
UseCase2 on Windows
UseCase2 on Linux
*/