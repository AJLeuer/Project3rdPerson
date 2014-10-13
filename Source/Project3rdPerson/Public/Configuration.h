//
//  Configuration.h
//  World
//
//  Created by Adam James Leuer on 5/25/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__Configuration__
#define __SpriteFight__Configuration__

#include "Project3rdPerson.h"

#include <iostream>
#include <fstream>
#include <chrono>

#include "Util.hpp"

#include "DisplayData.h"

#include "DefaultConfig.h"


using namespace std ;



/**
 * This class will mainly be used for overriding default settings,
 * usually based on some form of user input.
 */
class Configuration {

private:

	static ifstream configFile ;

    static void doUserOverrides() ;

	static void adjustForHiDPI() ;


public:

    static bool isInit ;

    static void init() ;

	/**
	 * A floating point value used in the calculation of the on-screen size of
	 * objects. Takes into account that the user can change absolute resolution
	 */
	static double globalScalingValue() ;

} ;





#endif /* defined(__SpriteFight__Configuration__) */
