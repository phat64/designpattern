#include <iostream>
#include <list>
#include <algorithm>
#include <assert.h>

using namespace std;
typedef std::string String;

class Employee {
private:
	String name;
	String dept;
	int salary;
	list<Employee*> subordinates;

public:
	// constructor
	Employee(const String& name, const String& dept, int sal) {
		this->name = name;
		this->dept = dept;
		this->salary = sal;
	}

	virtual ~Employee()
	{
		cout << "delete :" << name.c_str() << endl;

		for (Employee* e : subordinates)
		{
			delete e;
		}
		subordinates.clear();
	}

	void add(Employee* e) {
		subordinates.push_back(e);
	}

	void remove(Employee* e) {
		subordinates.remove(e);
	}

	const list<Employee*>& getSubordinates() {
		return subordinates;
	}

	void printEmployees() {
		cout << "Employee :[ Name : " << name.c_str() << ", dept : " << dept.c_str() << ", salary :" << salary << " ]" << endl;
		for (Employee* e : subordinates)
		{
			e->printEmployees();
		}
	}
};

void main15(int argc, char ** argv) {

	Employee* CEO = new Employee("John", "CEO", 30000);

	Employee* headSales = new Employee("Robert", "Head Sales", 20000);

	Employee* headMarketing = new Employee("Michel", "Head Marketing", 20000);

	Employee* clerk1 = new Employee("Laura", "Marketing", 10000);
	Employee* clerk2 = new Employee("Bob", "Marketing", 10000);

	Employee* salesExecutive1 = new Employee("Richard", "Sales", 10000);
	Employee* salesExecutive2 = new Employee("Rob", "Sales", 10000);

	CEO->add(headSales);
	CEO->add(headMarketing);

	headSales->add(salesExecutive1);
	headSales->add(salesExecutive2);

	headMarketing->add(clerk1);
	headMarketing->add(clerk2);

	//print all employees of the organization
	CEO->printEmployees();

	// recursive deletion
	delete CEO;
}