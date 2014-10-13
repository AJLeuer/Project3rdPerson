//
//  BaseInterface.h
//  World
//
//  Created by Adam James Leuer on 3/11/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__GameInterface__
#define __SpriteFight__GameInterface__

#include <iostream>

#include "GameState.hpp"

#include "Configuration.h"


/**
 * The pure virtual base class that will serve as an interface to every object in the game world. It defines all methods by
 * which any class can talk to another. Since KeyInputRegister expects an instance of GameInterface for member function calls, 
 * of Any class that wishes to make its its methods available for callback from input events should add a pure
 * virtual version of said functions to GameInterface, inherit from GameInterface, and implement.
 */
class GameInterface {

 
public:

	/**
	 * An implementing class can define a default function by overloading its () operator
	 */
	virtual void operator()() = 0 ;
	
	virtual void update() = 0 ;
	
	virtual void moveUp() = 0 ;
	virtual void moveDown() = 0 ;
	virtual void moveRight() = 0 ;
	virtual void moveLeft() = 0 ;
    
    virtual void orientationDependentLeftRightMove() = 0 ;
    virtual void orientationDependentRightLeftMove() = 0 ;
    
    virtual void rotateClockwise() = 0 ;
    virtual void rotateCounterClockwise() = 0 ;
    
	virtual void jump() = 0 ;
	
	virtual void fire() = 0 ;
	
	
};

#endif /* defined(__SpriteFight__GameInterface__) */
