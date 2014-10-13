//
//  Debug.h
//  World
//
//  Created by Adam James Leuer on 4/6/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__Debug__
#define __SpriteFight__Debug__

#include <iostream>
#include <ostream>
#include <fstream>

#include "Configuration.h"


using namespace std ;

class Debug : public ostream {

private:

	ostream * out ;
	bool file_output ;
	mutex dbgMutex ;
	mutex dbgMutex1 ;
	mutex dbgMutex2 ;



public:
	Debug(ostream * _out) : out(_out) {

	/* if DEBUG_MODE is not set, setting badbit prevents Debug from outputting anything */
	#ifndef DEBUG_MODE
	out->std::__1::ios_base::setstate(std::ios_base::badbit) ;
	#endif
	}


	template <typename T>
	Debug & operator <<(const T & data) ;

	Debug & operator<<(std::ostream & (*ptr)(std::ostream&)) {
		//#ifdef DEBUG_MODE
		dbgMutex.lock() ;
		(*out) << ptr;
		dbgMutex.unlock() ;
		return *this ;
		//#endif
	}

	Debug & operator<<(Debug & (*ptr)(Debug &)) {
		//#ifdef DEBUG_MODE
		dbgMutex1.lock() ;
		return ptr(*this);
		dbgMutex1.unlock() ;
		//#endif
	}

	ostream & get_ostream() { return *(this->out) ; }

	static Debug * debugOutput ;

	static void init() ;

	/* Use for whatever */
	static unsigned debugCounter ;

} ;

template <typename T>
Debug & Debug::operator<<(const T & data) {
	//#ifdef DEBUG_MODE
	dbgMutex2.lock() ;
	*out << data ;
	dbgMutex2.unlock() ;
	return *this ;
	//#endif
}



#define DebugOutput *(Debug::debugOutput)

#endif /* defined(__SpriteFight__Debug__) */
