/*#include <vector>
#include <iostream>
using namespace std;
typedef int Info;
class Observable;

class Observer
{
protected:
	std::vector<Observable*> m_list;

public:
	virtual void Update(const Observable* observable) const
	{
		cout << (int)observable->Statut() << endl;
	}

	void AddObs(Observable* obs)
	{
		m_list.push_back(obs);
	}

	void DelObs(Observable* obs)
	{
		auto it = std::find(m_list.begin(), m_list.end(), obs);
		if (it != m_list.end())
			m_list.erase(it);
	}

	virtual ~Observer()
	{
		for (int i = 0; i < m_list.size(); i++)
		{
			m_list[i]->DelObs(this);
		}
	}
};

class Observable
{
	std::vector<Observer*> m_list;

public:
	void AddObs(Observer* obs)
	{
		m_list.push_back(obs);

		// give the object to observe
		obs->AddObs(this);
	}

	void DelObs(Observer* obs)
	{
		auto it = find(m_list.begin(), m_list.end(), obs);
		if (it != m_list.end())
			m_list.erase(it);
	}

	virtual Info Statut(void) const = 0;

	virtual ~Observable()
	{
		for (int i = 0; i < m_list.size(); i++)
		{
			m_list[i]->DelObs(this);
		}
	}

protected:
	void NotifyAllObservers(void)
	{
		for (int i = 0; i < m_list.size(); i++)
		{
			m_list[i]->Update(this);
		}
	}
};

class Barometre : public Observable
{
private:
	int pression;

public:
	Barometre() :pression(0) {}

	void Change(int valeur)
	{
		pression = valeur;
		NotifyAllObservers();
	}

	Info Statut(void) const
	{
		return pression;
	}
};

class Thermometre : public Observable
{
private:
	int temperature;

public:
	Thermometre() : temperature(0) {}

	void Change(int valeur)
	{
		temperature = valeur;
		NotifyAllObservers();
	}

	Info Statut(void) const
	{
		return temperature;
	}
};

class MeteoFrance : public Observer
{

};

int main(void)
{

	Barometre barometre;
	Thermometre thermometre;

	// limit the scope of the "station"
	{
		MeteoFrance station;

		thermometre.AddObs(&station);
		barometre.AddObs(&station);

		thermometre.Change(31);
		barometre.Change(975);
	}

	thermometre.Change(45);
	return 0;
}*/