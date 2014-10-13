//
//  BasicConcurrency.h
//  SpriteFight
//
//  Created by Adam James Leuer on 7/4/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__BasicConcurrency__
#define __SpriteFight__BasicConcurrency__

#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

using namespace std ;

class BasicMutex : public mutex {
	
protected:
	
	bool locked ;
	
public:
	
	BasicMutex() : mutex(), locked(false) {}
	
	bool isLocked() { return locked ; }
	
	void lock();
	
    bool try_lock() _NOEXCEPT ;
	
    void unlock() ;
	
} ;

#endif /* defined(__SpriteFight__BasicConcurrency__) */
