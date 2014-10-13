//
//  DisplayData.h
//  SpriteFight
//
//  Created by Adam James Leuer on 6/28/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef SpriteFight_DisplayData_h
#define SpriteFight_DisplayData_h

/**
 * Holds information about the resolution and scaling of the current display
 */
struct DisplayData {
	
private:
	
	static bool isInit ;
	
	/* Using several extra layers of indirection to help
	 ensure everything is properly initialized at runtime */
	static bool hiDPI_referenceVal ;
	
	/**
	 * The display scaling factor.
	 * For example, if the system is running in Retina mode,
	 * this value will be 2.0
	 */
	static float displayScalingFactor_referenceVal ;
	
	/* Using several extra layers of indirection to help
	 ensure everything is properly initialized at runtime */
	//static float displayScalingFactor_referenceVal ;
	
	static void init() ;
	
	/**
	 * Used once to initialize displayScalingFactor
	 * For the sake of efficiency, reference displayScalingFactor
	 * instead of calling this.
	 */
	static void calculateDisplayScalingFactor() ; /* should only call this once ideally, just reference displayScalingFactor afterwards */
	
	
public:
	
	
	/**
	 * Check if we're running in Retina mode
	 */
	static bool hiDPI() ;
	
	/**
	 * The display scaling factor.
	 * For example, if the system is running in Retina mode,
	 * this value will be 2.0
	 */
	static float getDisplayScalingFactor() ;
	
} ;




#endif
