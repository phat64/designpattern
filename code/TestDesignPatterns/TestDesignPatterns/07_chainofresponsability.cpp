#include <iostream>
#include <assert.h>

using namespace std;
typedef std::string String;

#define SafeDelete(ptr) if (ptr){ delete ptr; ptr = nullptr; }


class AbstractLogger {
public:
	enum {INFO = 1,	DEBUG = 2,	ERROR = 3	};

protected:
	int level;

	//next element in chain or responsibility
	AbstractLogger* nextLogger;

public:
	AbstractLogger() : nextLogger(nullptr) {}
	virtual ~AbstractLogger() { /* destroy all elements of the chain*/ }

	void setNextLogger(AbstractLogger* nextLogger) {
		this->nextLogger = nextLogger;
	}

	void logMessage(int level, const String & message) {
		if (this->level <= level) {
			write(message);
		}
		if (nextLogger != nullptr) {
			nextLogger->logMessage(level, message);
		}
	}

private:
	virtual void write(const String & message) = 0;
};

class ConsoleLogger : public AbstractLogger {

public:
	ConsoleLogger(int level) : AbstractLogger() {
		this->level = level;
	}

private:
	void write(const String & message) {
		cout << "Standard Console::Logger: " << message.c_str() << endl;
	}
};

class ErrorLogger : public AbstractLogger {

public:
	ErrorLogger(int level) : AbstractLogger() {
		this->level = level;
	}

private:
	void write(const String& message) {
		cout << "Error Console::Logger: " << message.c_str() << endl;
	}
};

class FileLogger : public AbstractLogger {

public:
	FileLogger(int level) : AbstractLogger() {
		this->level = level;
	}

private:
	void write(const String & message) {
		cout << "File::Logger: " << message.c_str() << endl;
	}
};

class ChainPatternDemo {

public:
	static AbstractLogger* getChainOfLoggers() {

		AbstractLogger* errorLogger = new ErrorLogger(AbstractLogger::ERROR);
		AbstractLogger* fileLogger = new FileLogger(AbstractLogger::DEBUG);
		AbstractLogger* consoleLogger = new ConsoleLogger(AbstractLogger::INFO);

		errorLogger->setNextLogger(fileLogger);
		fileLogger->setNextLogger(consoleLogger);

		return errorLogger;
	}
};


int main7(int argc, char **argv)
{
	AbstractLogger* loggerChain = ChainPatternDemo::getChainOfLoggers();

	loggerChain->logMessage(AbstractLogger::INFO,
		"This is an information.");

	loggerChain->logMessage(AbstractLogger::DEBUG,
		"This is an debug level information.");

	loggerChain->logMessage(AbstractLogger::ERROR,
		"This is an error information.");

	delete loggerChain;
	return 0;
}

/*
Standard Console::Logger: This is an information.
File::Logger : This is an debug level information.
Standard Console::Logger : This is an debug level information.
Error Console::Logger : This is an error information.
File::Logger : This is an error information.
Standard Console::Logger : This is an error information.
*/