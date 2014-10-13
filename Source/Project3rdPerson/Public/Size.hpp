//
//  Size.h
//  World
//
//  Created by Adam James Leuer on 5/13/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__Size__
#define __SpriteFight__Size__

#include <iostream>
#include <sstream>

#include "Position.hpp"
#include "Configuration.h"

template<typename N>
struct Area : public Position<N> {

private:

	N * w = &(this->x) ; /* Never assign w or h, only ever assign to the values they point to (*w or *h) */
	N * h = &(this->y) ;


	/**
	 * The size modifier. Each GameObject will have a default size based on the sprite texture used to represent them, which will
	 * be multiplied by size. By default size will be 1, leaving the output unchanged. To adjust the size of this object, simply change the value of
	 * size (for instance, to make this half the normal size, set size = 0.5).
	 */
	float sizeModifier ;
	
	void setWidth(N width) { *(this->w) = width ; }
	void setHeight(N height) { *(this->h) = height ; }
	
	N getX() const { return this->x ; } /* override these to private */
	
	N getY() const { return this->y ; }
	
	N getZ() const { return this->z ; }

public:


	Area() :
		Position<N>(),
		sizeModifier(1.0) {}

	Area(N w_, N h_, float modifier) :
		Position<N>(w_, h_),
		sizeModifier(modifier) {}
    
    Area(N w_, N h_) :
        Position<N>(w_, h_),
        sizeModifier(1) {}

	Area(const Area<N> & other) :
		Position<N>(other),
		sizeModifier(other.sizeModifier) {}

	Area(Area<N> && other) :
		Position<N>(std::move(other)),
		sizeModifier(other.sizeModifier) {}

	~Area() {}

	Area & operator=(const Area<N> & rhs) {
		this->Position<N>::operator=(rhs) ;
		sizeModifier = rhs.sizeModifier ;
		return *this ;
	}
	
	Area & operator=(Area<N> && rhs) {
		this->Position<N>::operator=(std::move(rhs)) ;
		sizeModifier = rhs.sizeModifier ;
		return *this ;
	}
	
	void setModifier(const float modifier) { this->sizeModifier = modifier ; }
	
	void setSize(N w, N h) {
		setWidth(w) ;
		setHeight(h) ;
	}
	
	void setSize(N w, N h, float modifier) {
		setWidth(w) ;
		setHeight(h) ;
		setModifier(modifier) ;
	}
	
	float getModifier() const { return sizeModifier ; }
	N getWidth() const { return (this->x * sizeModifier) ; }
	N getHeight() const { return (this->y * sizeModifier)  ; }
    
    virtual void rotate(Angle 𝛳) {
        this->Position<N>::rotate(𝛳) ;
        this->x = setUnsigned(this->x) ;
        this->y = setUnsigned(this->y) ;
    }
    
    template<typename M>
    bool overBounds(const BoundsCheck<M> & check, const Position<M> & pos, const Angle & a = Angle(0)) const {
        
        //if x coord + width is less than x min... return true
        //if y coord - width is greater than y min... return true
        //etc
        
        Area adjustedSize = *this ; //copy size then adjust for our currentrotation
        
        adjustedSize.rotate(a) ;
        
        Position<M> topLeft((pos.getX() - (adjustedSize.getWidth() / 2)), (pos.getY() - (adjustedSize.getHeight() / 2))) ;
        Position<M> topRight((pos.getX() + (adjustedSize.getWidth() / 2)), (pos.getY() - (adjustedSize.getHeight() / 2))) ;
        Position<M> botLeft((pos.getX() - (adjustedSize.getWidth() / 2)), (pos.getY() + (adjustedSize.getHeight() / 2))) ;
        Position<M> botRight((pos.getX() + (adjustedSize.getWidth() / 2)), (pos.getY() + (adjustedSize.getHeight() / 2))) ;
        
        
        if ((topLeft.getX() > check.max_X) || (topLeft.getY() > check.max_Y)) {
            return true ;
        }
        else if ((topRight.getX() < check.min_X) || (topRight.getY() > check.max_Y)) {
            return true ;
        }
        else if ((botLeft.getX() > check.max_X) || (botLeft.getY() < check.min_Y)) {
            return true ;
        }
        else if ((botRight.getX() < check.min_X) || (botRight.getY() < check.min_Y)) {
            return true ;
        }
        else {
            return false ;
        }
    }

} ;


#endif /* defined(__SpriteFight__Size__) */
