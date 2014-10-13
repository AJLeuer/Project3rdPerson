//
//  BasicConcurrency.cpp
//  SpriteFight
//
//  Created by Adam James Leuer on 7/4/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Project3rdPerson.h"

#include "BasicConcurrency.h"

void BasicMutex::lock() {
	this->mutex::lock() ;
	locked = true ;
}

bool BasicMutex::try_lock() _NOEXCEPT {
	this->locked = this->mutex::try_lock() ;
	return this->locked ;
}

void BasicMutex::unlock() {
	this->mutex::unlock() ;
	locked = false ;
}