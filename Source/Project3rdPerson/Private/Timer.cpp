
#include "Project3rdPerson.h"

#include "Timer.hpp"

using namespace std ;

Timer::Timer() : timerStarted(false) {}

Timer::Timer(Timer && other) : timerStarted(std::move(other.timerStarted)), start(std::move(other.start)) {}

Timer::~Timer() {}

Timer & Timer::operator=(Timer && rhs) {
	if (this != &rhs) {
		timerStarted = rhs.timerStarted ;
		start = std::move(rhs.start) ;
	}
	return *this ;
}

void Timer::startTimer() {
	if (timerStarted) {
		cerr << "stopTimer() must be called before startTimer() can be called again for this Timer object \n" ;
		throw exception() ;
	}
	timerStarted = true ;
	start = chrono::steady_clock::now() ;
}


std::chrono::nanoseconds Timer::checkTimeElapsed() {
	//returns in micro or nanoseconds
	if (!timerStarted) {
		cerr << "checkTimeElapsed() can only be called after startTimer() has been called once \n" ;
		throw exception() ;
	}
	auto duration = chrono::steady_clock::now() - start ;
	return duration ;
}

void Timer::reset() {
	start = chrono::steady_clock::now() ;
}

std::chrono::nanoseconds Timer::stopTimer() {
	if (!timerStarted) {
		cerr << "stopTimer() can only be called after startTimer() has been called once \n" ;
		throw exception() ;
	}
	auto duration = chrono::steady_clock::now() - start ;
	timerStarted = false ;
	return duration ;
}
