//
//  ClockTicks.h
//  Intro to C++
//
//  Created by Adam J. Leuer on 7/27/13.
//  Copyright (c) 2013 Adam J. Leuer. All rights reserved.
//

#ifndef __Time__
#define __Time__

#include <iostream>
#include <chrono>

#include "Debug.h"


using namespace std ;

/**
 * @brief A class providing simple nanosecond-precision timing facilities
 */
class Timer {
	
private:
	
	bool timerStarted ;
	
	chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> start ;

public:
	
	Timer() ;
	
	Timer(Timer && other) ;
	
	~Timer() ;
	
	Timer & operator=(Timer && rhs) ;
	
	/**
	 * @brief Starts the timer.
	 */
	void startTimer() ;
	
	/**
	 * @brief Checks the time elapsed since startTimer() was called.
	 *		  Unlike stopTimer(), this function will not stop the timer.
	 *
	 * @note 1 millisecond = 1000000 nanoseconds
	 *
	 * @return The time elapsed in nanoseconds.
	 */
	std::chrono::nanoseconds checkTimeElapsed() ;
	
	/**
	 * @brief Resets the timer to 0
	 */
	void reset() ;
	
	/**
	 * @brief Stops timer and returns the time elapsed since startTimer() was called.
	 *
	 * @note 1 millisecond = 1000000 nanoseconds
     *
	 * @return The time elapsed in nanoseconds.
	 */
	std::chrono::nanoseconds stopTimer() ;
} ;







#endif /* defined Time */
