

class Strategy
{
public:
	Strategy() {}
	virtual ~Strategy() {}

	void Play()
	{
		Analyse();
		Apply();
	}

protected:
	virtual void Analyse() = 0;
	virtual void Apply() = 0;
};

class Agressive : public Strategy
{
	void Analyse() {}
	void Apply() {}

};

class Defensive : public Strategy
{
	void Analyse() {}
	void Apply() {}
};

class IA
{
	int m_health;
	Strategy* m_strategy;
public:
	IA() : m_health(100), m_strategy(nullptr) {}
	virtual ~IA() {}

	void SetStrategy(Strategy* strategy)
	{
		m_strategy = strategy;
	}

	void ChangeHealth(int i)
	{
		m_health = i;
	}

	int GetHealth()
	{
		return m_health;
	}

	void Play()
	{
		if (m_strategy)
		{
			m_strategy->Play();
		}
	}
};




int main6(int argc, char** argv)
{
	Agressive* agressive = new Agressive;
	Defensive* defensive = new Defensive;

	IA* ia = new IA;

	while (ia->GetHealth() > 0)
	{
		if (ia->GetHealth() < 50)
		{
			ia->SetStrategy(defensive);
		}
		else
		{
			ia->SetStrategy(agressive);
		}

		ia->Play();
	}

	delete ia;
	delete agressive;
	delete defensive;

	return 0;
}