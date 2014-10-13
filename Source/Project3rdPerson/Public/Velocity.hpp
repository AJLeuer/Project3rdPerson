//
//  Velocity.hpp
//  SpriteFight
//
//  Created by Adam James Leuer on 6/29/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef SpriteFight_Speed_hpp
#define SpriteFight_Speed_hpp

#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include <assert.h>

#include "Timer.hpp"
#include "BasicConcurrency.h"
#include "Configuration.h"

using namespace std ;

extern bool * velocityMonitorContinueSignal ;

template<typename N>
struct Velocity {

typedef N Distance ;
	
protected:
	
	static bool velocityMonitorInit ;
	static unsigned IDs ;
	static vector<Velocity *> velocityStorage ;
	
	
	int id ;
	const Distance * distance ;
	Timer * timer ;
	bool * localContinueSignal ;
	
	Distance lastDistance = 0 ;
	
	/**
	 * The unit of time that will function as the denominator
	 * for this Velocity object. By default it is 64 milliseconds.
	 */
	chrono::nanoseconds baseTimeUnit = std::chrono::milliseconds(30) ;
	
	double lastVelocity = 0 ;
	
	static void calculateVelocity() ;
	
	//friend class Vectr ;


public:
	
	static BasicMutex * sharedVelMutex ;
	
	static const vector<Velocity *> * getVelocityStorage() { return & velocityStorage ; }
	
	static void monitorVelocity() ;
	
	/**
	 * Constructs a Velocity object. Distance is a pointer
	 * that should increase in value as the caller moves. When
	 * Velocity detects that distance has changed from its initial value,
	 * it will begin monitoring speed.
	 * 
	 * @param distance A pointer to the distance covered by the client class, which Velocity expects to change over time
	 * @param mut A mutex shared with Velocity that should be locked when this velocity or distance is about to be deleted
	 */
	Velocity(const Distance * distance, bool * localContinueSignal) :
		id(IDs),
		distance(distance),
		timer(new Timer()),
		localContinueSignal(localContinueSignal)
	{
		IDs++ ;
		timer->startTimer() ;
		
		velocityStorage.push_back(this) ;
		assert(velocityStorage.at(id)->id == id) ; /* for debug builds only */
		
		if (velocityMonitorInit == false) {
			monitorVelocity() ;
		}
	}
	
	Velocity(const Distance * distance, bool * localContinueSignal, chrono::nanoseconds baseTimeUnitOverride) :
		id(IDs),
		distance(distance),
		timer(new Timer()),
		localContinueSignal(localContinueSignal),
		baseTimeUnit(baseTimeUnitOverride)
	{
		IDs++ ;
		timer->startTimer() ;
		
		velocityStorage.push_back(this) ;
		assert(velocityStorage.at(id)->id == id) ;
		
		if (velocityMonitorInit == false) {
			monitorVelocity() ;
		}
	}
	
	Velocity(const Velocity & other) = delete ;
	Velocity(Velocity && other) = delete ;

	~Velocity() {
	
		if (id != -1) {
			velocityStorage.at(id) = nullptr ;
		}
		
		id = -1 ;
		
		distance = nullptr ;
			
		if (timer != nullptr) {
			delete timer ;
			timer = nullptr ;
		}
	}
	
	Velocity & operator=(const Velocity & rhs) = delete ;
	Velocity & operator=(Velocity && rhs)  = delete ;

	double getValue() const {
		return lastVelocity * 100 ;
	}
	 
} ;

template<typename N>
bool Velocity<N>::velocityMonitorInit = false ;

template<typename N>
unsigned Velocity<N>::IDs = 0 ;

template<typename N>
vector<Velocity<N> *> Velocity<N>::velocityStorage = vector<Velocity<N> *>() ;

template<typename N>
BasicMutex * Velocity<N>::sharedVelMutex = new BasicMutex() ;

template<typename N>
void Velocity<N>::monitorVelocity() {
	
	auto velocityMonitor = [&] () -> void {
		while(*velocityMonitorContinueSignal) {
			calculateVelocity() ;
		}
	} ;
	
	std::thread thr(velocityMonitor) ;
	velocityMonitorInit = true ;
	thr.detach() ;	
}

template<typename N>
void Velocity<N>::calculateVelocity() {
	
    /* debug var */
	auto * vs = &velocityStorage ;
	/* end debug */

	for (auto i = 0 ; (i < velocityStorage.size()) && (*velocityMonitorContinueSignal) ; i++) {
		
		/* Debug var */
		auto vs = Velocity::getVelocityStorage() ;
		
		if (sharedVelMutex->isLocked() == true) {
			this_thread::sleep_for(defaultSleepTime) ;
			continue ;
		}
		else {
			sharedVelMutex->lock() ;
		}
		
		if ((velocityStorage.at(i) != nullptr) && (velocityStorage.at(i)->id != -1) && (velocityStorage.at(i)->localContinueSignal)) {

			if ((velocityStorage.at(i) != nullptr) && ((velocityStorage.at(i)->lastDistance != *velocityStorage.at(i)->distance) || (velocityStorage.at(i)->lastVelocity != 0))) {
				
				const N dist0 = *velocityStorage.at(i)->distance ;
				const auto time0 = velocityStorage.at(i)->timer->checkTimeElapsed() ;
				
				this_thread::sleep_for(velocityStorage.at(i)->baseTimeUnit) ;
				
				const N dist1 = *velocityStorage.at(i)->distance ;
				auto time1 = velocityStorage.at(i)->timer->checkTimeElapsed() ;
				
				const N totalDistance = dist1 - dist0 ;
				
				auto totalTime = chrono::duration_cast<chrono::milliseconds>(time1 - time0) ;
				
				auto timePassed = totalTime.count() ;
				
				double velocity = (totalDistance / timePassed) ;
				
				velocityStorage.at(i)->lastVelocity = velocity ;
				velocityStorage.at(i)->lastDistance = *velocityStorage.at(i)->distance ;
			
			}
			else {
                sharedVelMutex->unlock() ;
				this_thread::sleep_for(defaultSleepTime) ;
			}
		}
		else {
            sharedVelMutex->unlock() ;
			this_thread::sleep_for(defaultSleepTime) ;
		}
		sharedVelMutex->unlock() ;
	}
}

template<typename N>
ostream & operator<<(std::ostream & os, Velocity<N> * vel) {
	os << "Velocity: " << setprecision(3) << std::fixed << vel->getValue() ;
	return os ;
}

template<typename N>
ostream & operator<<(std::ostream & os, const Velocity<N> & vel) {
	os << "Velocity: " << setprecision(3) << std::fixed << vel.getValue() ;
	return os ;
}





#endif
