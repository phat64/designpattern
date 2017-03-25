#include <iostream>
#include <list>
#include <algorithm>
#include <assert.h>

using namespace std;
typedef std::string String;

// Create a "Abstract class" Dessert
class Dessert
{
private:
	String label;
	float price;

public:
	virtual ~Dessert() {}

	virtual const String getLabel()
	{
		return label;
	}
	
	virtual float getPrice()
	{
		return price;
	}

	void printInfo()
	{
		cout << getLabel().c_str() << " : " << ((int)getPrice())<< "."<< (((int)(100*getPrice()))%100) << " dollars" << endl;
	}

protected:
	void setLabel(const String& label)
	{
		this->label = label;
	}
	
	void setPrice(float price)
	{
		this->price = price;
	}
};

// 2 implementations of Dessert
class Waffle : public Dessert
{
public:
	Waffle()
	{
		setLabel("Waffle");
		setPrice(1.80f);
	}
};

class Crepe : public Dessert
{
public:
	Crepe()
	{
		setLabel("Crepe");
		setPrice(1.50f);
	}
};

// Abstract Class abstraite IngredientDecorator that inherits from Dessert
class IngredientDecorator: public Dessert
{
protected:
	Dessert* dessert;// Dessert sur leuquel on applique l'ingrédient.

	// On oblige les ingrédients à implémenter la méthode getLibelle().
	virtual const String getLabel() = 0;
	// On oblige les ingrédients à implémenter la méthode getPrix().
	virtual float getPrice() = 0;
};

// Implémentation of Chantilly and Chocolat classes 
class Chantilly : public IngredientDecorator
{
public:

	Chantilly(Dessert* d)
	{
		dessert = d;
	}

	// Show the label of the dessert and add the label of the chantilly ingredient 
	const String getLabel()
	{
		return dessert->getLabel() + ", chantilly";
	}

	// Add the price of the dessert and the price of the chantilly ingredient
	float getPrice()
	{
		return dessert->getPrice() + 0.50f;
	}
};

class Chocolate : public IngredientDecorator
{
public:
	Chocolate(Dessert* d)
	{
		dessert = d;
	}

	// Show the label of the dessert and add the label of the chocolate ingredient 
	const String getLabel()
	{
		return dessert->getLabel() + ", chocolate";
	}

	// Add the price of the dessert and the price of the chocolate ingredient
	float getPrice()
	{
		return dessert->getPrice() + 0.20f;
	}
};

void main16(int argc, char ** argv)
{
	// Create and show a Waffle with chocolate
	Dessert* waffle = new Waffle();
	waffle->printInfo();
	Dessert* waffleWithChocolate = new Chocolate(waffle);
	waffleWithChocolate->printInfo();

	// Create and show a Waffle with chocolate and chantilly
	Dessert* crepe = new Crepe();
	crepe->printInfo();
	Dessert* crepeWithChocolate = new Chocolate(crepe);
	crepeWithChocolate->printInfo();
	Dessert* crepeWithChantilly = new Chantilly(crepe);
	crepeWithChantilly->printInfo();

	delete waffle;
	delete waffleWithChocolate;
	delete crepe;
	delete crepeWithChocolate;
	delete crepeWithChantilly;
}

/* Output : 
Waffle: 1.80 dollars
Waffle, chocolate : 2.0 dollars
Crepe : 1.50 dollars
Crepe, chocolate : 1.70 dollars
Crepe, chantilly : 2.0 dollars
*/