
#ifdef __APPLE__

#include "Project3rdPerson.h"

#include "Util.hpp"

#include "DisplayData.h"


void DisplayData::calculateDisplayScalingFactor() {
	float displayScale = 1.0 ;
    
    //todo fix
	/*
    if ([[NSScreen mainScreen] respondsToSelector:@selector(backingScaleFactor)]) {
        screens = [NSScreen screens];
        for (int i = 0; i < [screens count]; i++) {
            float s = [[screens objectAtIndex:i] backingScaleFactor];
            if (s > displayScale)
                displayScale = s;
        }
    } */
    displayScalingFactor_referenceVal = displayScale ;
}

#endif