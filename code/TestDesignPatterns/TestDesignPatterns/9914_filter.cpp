#include <iostream>
#include <list>
#include <algorithm>
#include <assert.h>

using namespace std;
typedef std::string String;

// Create a class on which criteria is to be applied.
class Person {
private:
	String name;
	String gender;
	String maritalStatus;

public:
	Person(const String & name, const String & gender, const String & maritalStatus) {
		this->name = name;
		this->gender = gender;
		this->maritalStatus = maritalStatus;
	}

	virtual ~Person() {}

	const String& getName() {
		return name;
	}

	const String& getGender() {
		return gender;
	}
	const String& getMaritalStatus() {
		return maritalStatus;
	}
};

// Create an interface for Criteria.
class Criteria {
public:
	virtual list<Person*> meetCriteria(const list<Person*> &persons) = 0;
};


// Create concrete classes implementing the Criteria interface.
class CriteriaMale : public Criteria {

public:
	list<Person*> meetCriteria(const list<Person*>& persons) {
		list<Person*> malePersons;

		for (Person* person : persons) {
			if (person->getGender() == "Male") {
				malePersons.push_back(person);
			}
		}
		return malePersons;
	}
};

class CriteriaFemale : public Criteria {
public:
	list<Person*> meetCriteria(const list<Person*>& persons) {
		list<Person*> femalePersons;

		for (Person* person : persons) {
			if (person->getGender() == "Female") {
				femalePersons.push_back(person);
			}
		}
		return femalePersons;
	}
};

class CriteriaSingle : public Criteria {

public:
	list<Person*> meetCriteria(const list<Person*>& persons) {
		list<Person*> singlePersons;

		for (Person* person : persons) {
			if (person->getMaritalStatus() == "Single") {
				singlePersons.push_back(person);
			}
		}
		return singlePersons;
	}
};

class AndCriteria : public Criteria {
private:
	Criteria* criteria;
	Criteria* otherCriteria;

public:
	AndCriteria(Criteria* criteria, Criteria* otherCriteria) {
		this->criteria = criteria;
		this->otherCriteria = otherCriteria;
	}

	list<Person*> meetCriteria(const list<Person*>& persons) {
		list<Person*> firstCriteriaPersons = criteria->meetCriteria(persons);
		return otherCriteria->meetCriteria(firstCriteriaPersons);
	}
};


class OrCriteria : public Criteria {
private:
	Criteria* criteria;
	Criteria* otherCriteria;

public:
	OrCriteria(Criteria* criteria, Criteria* otherCriteria) {
		this->criteria = criteria;
		this->otherCriteria = otherCriteria;
	}

	list<Person*> meetCriteria(const list<Person*>& persons) {
		list<Person*> firstCriteriaItems = criteria->meetCriteria(persons);
		list<Person*> otherCriteriaItems = otherCriteria->meetCriteria(persons);

		for (Person* person : otherCriteriaItems) {
			if (std::find(firstCriteriaItems.begin(), firstCriteriaItems.end(), person) == firstCriteriaItems.end()){
				firstCriteriaItems.push_back(person);
			}
		}
		return firstCriteriaItems;
	}
};


// Use different Criteria and their combination to filter out persons.
void printPersons(const list<Person*>& persons);

void main9914(int argc, char **argv) {
	list<Person*> persons;

	persons.push_back(new Person("Robert", "Male", "Single"));
	persons.push_back(new Person("John", "Male", "Married"));
	persons.push_back(new Person("Laura", "Female", "Married"));
	persons.push_back(new Person("Diana", "Female", "Single"));
	persons.push_back(new Person("Mike", "Male", "Single"));
	persons.push_back(new Person("Bobby", "Male", "Single"));

	Criteria* male = new CriteriaMale();
	Criteria* female = new CriteriaFemale();
	Criteria* single = new CriteriaSingle();
	Criteria* singleMale = new AndCriteria(single, male);
	Criteria* singleOrFemale = new OrCriteria(single, female);

	cout << "Males: " << endl;
	printPersons(male->meetCriteria(persons));
	cout << endl;

	cout << "Females: " << endl;;
	printPersons(female->meetCriteria(persons));
	cout << endl;

	cout << "Single Males: " << endl;
	printPersons(singleMale->meetCriteria(persons));
	cout << endl;

	cout << "\nSingle Or Females: " << endl;
	printPersons(singleOrFemale->meetCriteria(persons));

	delete male;
	delete female;
	delete single;
	delete singleMale;
	delete singleOrFemale;
	
	for (Person* person : persons)
	{
		delete person;
	}
	persons.clear();

}

void printPersons(const list<Person*>& persons) {

	for (Person* person : persons) {
		cout << "Person : [ Name : " << person->getName().c_str();
		cout << ", Gender : " << person->getGender().c_str();
		cout << ", Marital Status : " << person->getMaritalStatus().c_str();
		cout << " ]" << endl;
	}
}

/* Output :
Males:
Person: [Name:Robert, Gender : Male, Marital Status : Single]
Person : [Name:John, Gender : Male, Marital Status : Married]
Person : [Name:Mike, Gender : Male, Marital Status : Single]
Person : [Name:Bobby, Gender : Male, Marital Status : Single]

Females :
Person : [Name:Laura, Gender : Female, Marital Status : Married]
Person : [Name:Diana, Gender : Female, Marital Status : Single]

Single Males :
Person: [Name:Robert, Gender : Male, Marital Status : Single]
Person : [Name:Mike, Gender : Male, Marital Status : Single]
Person : [Name:Bobby, Gender : Male, Marital Status : Single]

Single Or Females :
Person: [Name:Robert, Gender : Male, Marital Status : Single]
Person : [Name:Diana, Gender : Female, Marital Status : Single]
Person : [Name:Mike, Gender : Male, Marital Status : Single]
Person : [Name:Bobby, Gender : Male, Marital Status : Single]
Person : [Name:Laura, Gender : Female, Marital Status : Married]
*/