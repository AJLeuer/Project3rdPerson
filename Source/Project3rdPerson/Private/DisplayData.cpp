
#include "Project3rdPerson.h"

#include "Util.hpp"

#include "DisplayData.h"


bool DisplayData::isInit = false ;

bool DisplayData::hiDPI_referenceVal ;

float DisplayData::displayScalingFactor_referenceVal ;

void DisplayData::init() {
	
	/* init displayScalingFactor_referenceVal */
	calculateDisplayScalingFactor() ;
	
	/* init hiDPI_referenceVal */
	hiDPI_referenceVal = ((displayScalingFactor_referenceVal == 2.0) ? true : false) ;
	
	isInit = true ;
	
}

bool DisplayData::hiDPI() {
	
	if (isInit == false) {
		init() ;
		return DisplayData::hiDPI_referenceVal ;
	}
	else {
		return DisplayData::hiDPI_referenceVal ;
	}
	
}

float DisplayData::getDisplayScalingFactor() {
	
	if (isInit == false) {
		init() ;
		return DisplayData::displayScalingFactor_referenceVal ;
	}
	else {
		return displayScalingFactor_referenceVal ;
	}
	
}

