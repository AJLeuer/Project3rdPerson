//
//  Configuration.cpp
//  World
//
//  Created by Adam James Leuer on 5/25/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Project3rdPerson.h"

#include "Configuration.h"

#include "Position.hpp"

using namespace std ;

/* Many of these values will be overridden */

//define extern values from DefaultConfig.h as well
bool debugToSTDOutput = true ;

/* May be larger than window size to give us buffer space outside the window margins */
unsigned globalMaxX() { return RESOLUTION_X_BASE_VALUE * DisplayData::getDisplayScalingFactor() ; }
unsigned globalMaxY()   { return RESOLUTION_Y_BASE_VALUE * DisplayData::getDisplayScalingFactor() ; }

//will probably be changed from default
unsigned RESOLUTION_X_BASE_VALUE = DEFAULT_W_MAX_X  ;
unsigned RESOLUTION_Y_BASE_VALUE = DEFAULT_W_MAX_Y  ;

/* Default values, will most likely be changed by Configuration::init() */
unsigned windowSizeX() {
    return (RESOLUTION_X_BASE_VALUE * DisplayData::getDisplayScalingFactor()) ;
}

unsigned windowSizeY() {
    return (RESOLUTION_Y_BASE_VALUE * DisplayData::getDisplayScalingFactor()) ;
}

Resolution<unsigned> * currentResolution() { return new Resolution<unsigned>(windowSizeX(), windowSizeY()) ; }

Resolution<unsigned> * currentResolutionBaseValue() { return new Resolution<unsigned>(RESOLUTION_X_BASE_VALUE, RESOLUTION_Y_BASE_VALUE) ; }

int WINDOW_ARGS = 0 ; /* will always need proper initialization to check for DPI changes */

int defaultMoveDistance = 6 ;

chrono::nanoseconds refreshTime = one_millisecond ;

chrono::milliseconds defaultSleepTime = chrono::milliseconds(240) ;

char   JUMP_KEY		  =         ' ' ;
char * MOVE_UP_KEY    = (char *)"W" ;
char * MOVE_DOWN_KEY  = (char *)"S" ;
char * MOVE_LEFT_KEY  = (char *)"A" ;
char * MOVE_RIGHT_KEY = (char *)"D" ;

bool Configuration::isInit = false ;

ifstream Configuration::configFile("/Settings/Setting.cfg") ;


void Configuration::init() {

	/* make any user requested changes from values in default config */
    doUserOverrides() ;

	adjustForHiDPI() ;

    isInit = true ;
}

void Configuration::doUserOverrides() {
	//todo
	//e.g. user may want to change LOGICAL_WINDOW_SIZE
}


void Configuration::adjustForHiDPI() {
	if (DisplayData::hiDPI()) {
		WINDOW_ARGS = 0 ;
	}
	else {
		/* No change to window size */
		WINDOW_ARGS = 0 ;
	}
}

double Configuration::globalScalingValue() {

	if (isInit == false) {
		init() ;
	}

	/* calculate the factor that when multiplied by our base resolution
	 gives the current resolution - everything else needs to be multiplied
	 by that same factor */
	Resolution<unsigned> refResolution(MAX_X_REFERENCE_VAL, MAX_Y_REFERENCE_VAL) ;
	auto currentRes = currentResolutionBaseValue() ;
	double factor = *currentRes / refResolution ;
	delete currentRes ;

	return factor ;
}
