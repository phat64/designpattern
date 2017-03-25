#include <iostream>
#include <map>
#include <vector>
#include <assert.h>

using namespace std;
typedef std::string String;

namespace interpreter
{
	// Create an expression "interface".
	class Expression {
	public:
		virtual ~Expression() {}
		virtual bool interpret(const String &context) = 0;
	};


	// Create concrete classes implementing the above interface.
	class TerminalExpression : public Expression {

	private:
		String data;

	public:
		TerminalExpression(const String & data)
		{
			this->data = data;
		}

		~TerminalExpression() {}

		bool interpret(const String & context) 
		{	
			if (context.find(data) >=0)
			{
				return true;
			}
			return false;
		}

	};

	class OrExpression: public Expression {
	private:
		Expression* expr1 = nullptr;
		Expression* expr2 = nullptr;

	public:
		OrExpression(Expression* expr1, Expression* expr2) {
			this->expr1 = expr1;
			this->expr2 = expr2;
		}

		~OrExpression() { delete expr1; delete expr2;}

		bool interpret(const String& context) {
			return expr1->interpret(context) || expr2->interpret(context);
		}
	};


	class AndExpression : public Expression {
	private:
		Expression* expr1 = nullptr;
		Expression* expr2 = nullptr;

	public:
		AndExpression(Expression* expr1, Expression* expr2) {
			this->expr1 = expr1;
			this->expr2 = expr2;
		}

		~AndExpression() { delete expr1; delete expr2; }

		bool interpret(const String& context) {
			return expr1->interpret(context) && expr2->interpret(context);
		}
	};

	class InterpreterPatternDemo {
	public:
		//Rule: Robert and John are male
		static Expression* getMaleExpression() {
			Expression* robert = new TerminalExpression("Robert");
			Expression* john = new TerminalExpression("John");
			return new OrExpression(robert, john);
		}

		//Rule: Julie is a married women
		static Expression* getMarriedWomanExpression() {
			Expression* julie = new TerminalExpression("Julie");
			Expression* married = new TerminalExpression("Married");
			return new AndExpression(julie, married);
		}
	};
}

using namespace interpreter;

int main20()
{
	Expression* isMale = InterpreterPatternDemo::getMaleExpression();
	Expression* isMarriedWoman = InterpreterPatternDemo::getMarriedWomanExpression();

	cout << std::noboolalpha  << "John is male? " << std::boolalpha << isMale->interpret("John") << endl;
	cout << "Julie is a married women? " << std::boolalpha << isMarriedWoman->interpret("Married Julie") << endl;

	delete isMale;
	delete isMarriedWoman;

	return 0;
}

// Verify the output.
// John is male ? true
// Julie is a married women ? true
