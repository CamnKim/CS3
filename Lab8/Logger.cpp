// singleton logger
// Cameron Kim
// 10/30/20

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using std::string; using std::ofstream; using std::cout; using std::endl;

class Logger {
public:
	static Logger *instance(); // returns pointer to single instance

	void report(const string&); // logs string into log.txt

private:
	Logger();

	// copying prohibited
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	static void cleanUp(); // correct object destruction
	static Logger* onlyInstanceInt_; // pointer to its instance
	static ofstream log_; // log object
};
ofstream Logger::log_;

// initializing pointer to its instance
Logger* Logger::onlyInstanceInt_ = nullptr;

// returns pointer to instance of singleton
Logger* Logger::instance() {
	if (onlyInstanceInt_ == nullptr) {
		// constructor is invoked here
		onlyInstanceInt_ = new Logger;

		log_.open("log.txt", std::fstream::out | std::fstream::app);
	}

	return onlyInstanceInt_;
}

// registering behavior at program shutdown
Logger::Logger() { atexit(cleanUp); }

// deallocate instance, re-set pointer
void Logger::cleanUp() {
	cout << "cleaning up..." << endl;
	delete onlyInstanceInt_;
	onlyInstanceInt_ = nullptr;
	log_.close();
}

void Logger::report(const string& str) {
	log_ << str << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
void functionOne() {
	cout << "in function one" << endl;
	Logger::instance()->report("in function one");
}

int power(int x, int y) {
	string log = "in power:   x: " + std::to_string(x) + ", y: " + std::to_string(y);
	int result = x;

	for (int i = 0; i < y - 1; ++i) {
		result *= x;
	}

	log += (", x^y = " + result);
	Logger::instance()->report(log);
	return result;
}

int main() {
	int x = 2;
	int y = 5;

	functionOne();
	power(x, y);
}