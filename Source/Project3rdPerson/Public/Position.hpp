//
//  Header.h
//  World
//
//  Created by Adam James Leuer on 3/11/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//


#ifndef SpriteFight_Position_h
#define SpriteFight_Position_h


#include <complex>
#include <valarray>
#include <iostream>
#include <ostream>
#include <sstream>
#include <queue>
#include <vector>
#include <array>
#include <tuple>
#include <initializer_list>
#include <deque>

#include "Debug.h"
#include "Util.hpp"
#include "BoundsCheck.hpp"
#include "Velocity.hpp"
#include "GameRandom.hpp"
#include "BasicConcurrency.h"

#include "GlobalVar.h"

#define UP 0, -1, 0
#define DOWN 0, 1, 0
#define LEFT -1, 0, 0
#define RIGHT 1, 0, 0


using namespace std ;

enum Direction {
	north = 'n',
	south = 's',
	east = 'e',
	west = 'w',
	ne = north + east,
	se = south + east,
	sw = south + west,
	nw = north + west,
	noDirection //the best direction! (and also a base case in certain recursive algorithms)
} ;

/**
 * @brief A storage class for angular values. All underlying values are represented in degrees.
 *
 * @note Since the standard library trigonometric functions (i.e. sin(), cos(), etc.) expect
 * argument values expressed in radians, values passed to those functions should first be converted.
 * Angle provides the member function valInRadians() for just that purpose.
 */
class Angle {

protected:

	float value ;

public:

	Angle(const float angle) : value(angle) {
		value = Mod(value, 360.0f) ;
	}

	Angle(const Angle & other) : value(other.value) {
		value = Mod(value, 360.0f) ;
	}

    template<typename N>
    Angle(FastRand<N> randm) {
        value = randm(0, 360) ;
    }

	~Angle() {}

	Angle & operator=(const Angle & rhs) {
		if (this != &rhs) {
			this->value = Mod(rhs.value, 360.0f) ;
		}
		return *this ;
	}

	Angle & operator=(const float & f) {
		value = Mod(f, 360.0f) ;
		return *this ;
	}

	//operator float() const { return this->value ; }

	Angle operator+(const float otherAngle) const {
		Angle val(0) ;
		val.value = Mod((this->value + otherAngle), 360.0f) ;
		return val ;
	}

	Angle operator-(const float otherAngle) const {
		Angle val(0) ;
		val.value = Mod((this->value - otherAngle), 360.0f) ;
		return val ;
	}

	void operator+=(const float otherAngle) {
		this->value = Mod((value + otherAngle), 360.0f) ;
	}

	void operator-=(const float otherAngle) {
		this->value = Mod((value - otherAngle), 360.0f) ;
	}

	Angle operator+(const Angle otherAngle) const {
		Angle val(0) ;
		val.value = Mod((this->value + otherAngle.value), 360.0f) ;
		return val ;
	}

	Angle operator-(const Angle otherAngle) const {
		Angle val(0) ;
		val.value = Mod((this->value - otherAngle.value), 360.0f) ;
		return val ;
	}

	void operator+=(const Angle otherAngle) {
		this->value = Mod((value + otherAngle.value), 360.0f) ;
	}

	void operator-=(const Angle otherAngle) {
		this->value = Mod((value - otherAngle.value), 360.0f) ;
	}

	float val() {
		value = Mod(value, 360.0f) ;
		return value ;
	}

	float val_const() const {
		float val = value ;
		val = Mod(val, 360.0f) ;
		return val ;
	}

    float valInRadians() {
        return (convertToRadians<float>((val()))) ;
    }


} ;


/**
 * Position<> is a simple vector data type.
 *
 * Note: Classes with a Position data member will typically want to have a pointer,
 * instead of holding the Position locally. This is because many objects in the World
 * may not actually have a physcical Position in space, in which case they can just hold a
 * null pointer.
 */
template <typename N>
struct Position {

protected:

	N x ;
	N y ;

public:
	/**
     * Creates a Positionwith all coordinates initialized to 0
     */
	Position() : x(0), y(0) {}

	/**
     * Creates a Positionwith all coordinates initialized to 0
     */
	Position(const BoundsCheck<N> & check) : x(0), y(0) { this->checkBounds(check) ; }

	/**
     * Creates a Positionwith all coordinates initialized to n
     */
	Position(N n) : x(n), y(n) {}

	/**
     * Creates a Positionwith all coordinates initialized to n
     */
	Position(N n, const BoundsCheck<N> & check) : x(n), y(n) { this->checkBounds(check) ; }


	template<typename M>
	Position(M x, M y) : x(static_cast<N>(x)), y(static_cast<N>(y)) {}

	/**
     * Creates a Positionwith all coordinates randomized, with bounds set by check
     */
    template<typename R>
	Position(FastRand<R> rand) :
		x(rand.nextValue()),
		y(rand.nextValue()) {}

	/**
     * Creates a Positionwith all coordinates randomized, with bounds set by check
     */
    template<typename R>
	Position(FastRand<R> rand, const BoundsCheck<N> & check) :
		x(rand.nextValue(check.min_X, check.max_X)),
		y(rand.nextValue(check.min_Y, check.max_Y))
	{
		checkBounds(check) ;
	}

    /**
     * Copy constructor for Position
     */
    Position(const Position & other) : Position(other.x, other.y) {}

	/**
     * Copy constructor for Position
     */
    Position(const Position & other, const BoundsCheck<N> & check) : Position(other.x, other.y)  {
		checkBounds(check) ;
	}

	/**
     * Move constructor for Position
     */
    Position(Position && other) : Position(other.x, other.y) {}

	/**
     * Move constructor for Position
     */
    Position(Position && other, const BoundsCheck<N> & check) : Position(other.x, other.y) {
		checkBounds(check) ;
	}

	/**
     * Creates a Position with coordinates initialized to the
     * given arguments
     *
     * @param x The x coordinate
     * @param y The y coordinate
     */
	Position(N x, N y) : x(x), y(y) {}

    /**
     * Creates a Position with coordinates initialized to the
     * given arguments
     *
     * @param x The x coordinate
     * @param y The y coordinate
     */
	Position(N x, N y, const BoundsCheck<N> & check) : x(x), y(y) {
		this->checkBounds(check) ;
	}

    Position(FastRand<N> & randm) {
        x = randm(BoundsCheck<N>::defaultCheck.min_X, BoundsCheck<N>::defaultCheck.max_X) ;
        y = randm(BoundsCheck<N>::defaultCheck.min_Y, BoundsCheck<N>::defaultCheck.max_Y) ;
    }

    /**
     * Destructor for Position
     */
    virtual ~Position() {}


    /**
     * Assigment operator (copy).
     */
    virtual Position & operator=(const Position & rhs) {

		this->x = rhs.x ;
		this->y = rhs.y ;

        return *this;
    }


	/**
     * Assigment operator (move)
     */
    virtual Position & operator=(Position && rhs) {

		this->x = rhs.x ;
		this->y = rhs.y ;

		return(*this) ;
    }


	virtual bool operator==(const Position & rhs) const {
		if ((this->x == rhs.x) && (this->y == rhs.y)) {
			return true ;
		}
		else {
			return false ;
		}
	}

	virtual bool operator==(Position & rhs) const {
		if ((this->x == rhs.x) && (this->y == rhs.y)) {
			return true ;
		}
		else {
			return false ;
		}
	}

	virtual bool operator!=(const Position & rhs) const {
		return !(this->operator==(rhs)) ;
	}

	virtual bool operator!=(Position & rhs) {
		return !(this->operator==(rhs)) ;
	}

	virtual Position operator+(const Position & rhs) const {

        Position temp = Position(this->x, this->y) ;

		temp.x = temp.x + rhs.x ;
		temp.y = temp.y + rhs.y ;

		return temp ;
	}

	virtual Position operator-(const Position & rhs) const {

        Position temp = Position(this->x, this->y) ;

		temp.x = temp.x - rhs.x ;
		temp.y = temp.y - rhs.y ;

		return temp ;
	}

	virtual Position operator*(const N n) const {

        Position temp = Position(x, y) ;

		temp.x = temp.x * n ;
		temp.y = temp.y * n ;

		return temp ;
	}

	virtual Position operator/(const N n) const {

        Position temp = Position(x, y) ;

		temp.x = temp.x / n ;
		temp.y = temp.y / n ;

		return temp ;
	}


	virtual void normalize() {
		auto distance = pythag<float>(x, y) ;
		if (distance != 0) {
			x = (x / distance) ;
		}
		if (distance != 0) {
			y = (y / distance) ;
		}
	}

	template<typename O, typename P>
    friend const Position<P> * operator+(const Position<P> & lhs, const Position<O> * rhs) {

		P x = lhs.x + rhs->x ;
		P y = lhs.y + rhs->y ;

		return new Position<P>(x, y) ;
	}

	template<typename O, typename P>
    friend const Position<P> * operator-(const Position<P> & lhs, const Position<O> * rhs) {

		P x = lhs.x - rhs->x ;
		P y = lhs.y - rhs->y ;

		return new Position<P>(x, y) ;
	}

	friend ostream & operator<<(std::ostream & os, const Position<N> * pos) {
		os << "Position: X = " << pos->x << ", Y = " << pos->y  << '\n' ;
		return os ;
	}

	friend ostream & operator<<(std::ostream & os, const Position<N> & pos) {
		os << "Position: X = " << pos.x << ", Y = " << pos.y << '\n' ;
		return os ;
	}

	/**
	 * Sets x, y, and z to the given values.
	 */
	virtual void setAll(const N x, const N y) {
		this->x = x ;
		this->y = y ;
	}

	virtual void setAll(const N x, const N y, const BoundsCheck<N> & check) {
		setAll(x, y) ;
		checkBounds(&check) ;
	}

	virtual void setAll(const Position<N> & other) {
		setAll(other.x, other.y) ;
	}

	virtual void setAll(const Position<N> & other, const BoundsCheck<N> & check) {
		setAll(other.x, other.y) ;
		checkBounds(&check) ;
	}

	virtual void setAll(const N n) { setAll(n, n) ; }

	virtual void setAll(const N n, const BoundsCheck<N> & check) { setAll(n, n, check) ; }

	virtual void setAllZero() { setAll(0) ; }


	N getX() const { return this->x ; }

	N getY() const { return this->y ; }

	/**
	 * @return x as an integer
	 */
	int getIntX() const { return roundF<N, int>(x) ; }

	/**
	 * @return y as an integer
	 */
	int getIntY() const { return roundF<N, int>(y) ; }

	virtual void setX(const N x) { setAll(x, this->y) ; }

	virtual void setX(const N x, const BoundsCheck<N> & check) { setX(x) ; checkBounds(check) ; }

	virtual void setY(const N y) { setAll(this->x, y) ; }

	virtual void setY(const N y, const BoundsCheck<N> & check) { setY(y) ; checkBounds(check) ; }


	virtual void x_plus_one() { setX(x++) ; }

	virtual void x_plus_one(const BoundsCheck<N> & check) { setX(x++) ; checkBounds(check) ; }

	virtual void x_minus_one() { setX(x--) ; }

	virtual void x_minus_one(const BoundsCheck<N> & check) { setX(x--) ; checkBounds(check) ; }


	virtual void y_plus_one() { setY(y++) ; }

	virtual void y_plus_one(const BoundsCheck<N> & check) { setY(y++) ; checkBounds(check) ; }

	virtual void y_minus_one() { setY(y--) ; }

	virtual void y_minus_one(const BoundsCheck<N> & check) { setY(y--) ; checkBounds(check) ; }


	/**
	 * Increments or decrements the x, y and z values according to
	 * the arguments passed in. Use negative values to decrement. Passing
	 * 0 for any argument will keep the x, y, or z value the same.
	 *
	 * @param delta_x The change in x value
	 * @param delta_y The change in y value
	 * @param delta_z The change in z value
	 */
	virtual void modify(N delta_x, N delta_y) {
		auto tempX = this->x ;
		auto tempY = this->y ;

		tempX += delta_x ;
		tempY += delta_y ;

		setAll(tempX, tempY) ;
	}

	/**
	 * Increments or decrements the x, y and z values according to
	 * the arguments passed in. Use negative values to decrement. Passing
	 * 0 for any argument will keep the x, y, or z value the same.
	 *
	 * @param delta_x The change in x value
	 * @param delta_y The change in y value
	 * @param delta_z The change in z value
	 */
	virtual void modify(N delta_x, N delta_y, const BoundsCheck<N> & check) {
		auto tempX = this->x ;
		auto tempY = this->y ;

		tempX += delta_x ;
		tempY += delta_y ;

		setAll(tempX, tempY, check) ;
	}

	virtual void moveHere(N x, N y) {
		setAll(x, y) ;
	}

	virtual void moveHere(N x, N y, const BoundsCheck<N> & check) {
		moveHere(x, y) ;
		checkBounds(check) ;
	}

	virtual void moveHere(const Position<N> & other) {
		setAll(other.x, other.y) ;
	}

	virtual void moveHere(const Position<N> & other, const BoundsCheck<N> & check) {
		moveHere(other) ;
		checkBounds(check) ;
	}

    virtual void rotate(Angle 𝛳) {
        const N prevX = x ;
        const N prevY = y ;

        x = (prevX * cos(𝛳.valInRadians())) - (prevY * sin(𝛳.valInRadians())) ;
        y = (prevX * sin(𝛳.valInRadians())) + (prevY * cos(𝛳.valInRadians())) ;
    }

	static N calcDistance(const Position & here, const Position & there) {
		N dx = here.x - there.x ;
		N dy = here.y - there.y ;
		N nx = setUnsigned(dx) ;
		N ny = setUnsigned(dy) ;
		N dist = pythag(nx, ny) ;
		return dist ;
	}

	std::string toString() const {
		stringstream ss ;
		ss << this ;
		return ss.str() ;
	}


	void checkBounds(const BoundsCheck<N> * check) {

		if ((this->x) >= check->max_X) {
			{
			/* Debug code */
			DebugOutput << "An X value was over the global limit. Reducing value... \n" ;
			/* End Debug code */
			}
			this->x = check->max_X /*- objWidth*/ - 1 ;
		}
		if (this->x < check->min_X) {
			{
			/* Debug code */
			DebugOutput << "An X value was under the global minimum. Increasing value... \n" ;
			/* End Debug code */
			}
			this->x = check->min_X /*+ objWidth*/ ;
		}
		if ((this->y) >= check->max_Y) {
			{
			/* Debug code */
			DebugOutput << "A Y value was over the global limit. Reducing value... \n" ;
			/* End Debug code */
			}
			this->y = check->max_Y /*- objHeight*/ - 1 ;
		}
		if (this->y < check->min_Y) {
			{
			/* Debug code */
			DebugOutput << "A Y value was under the global minimum. Increasing value... \n" ;
			/* End Debug code */
			}
			this->y = check->min_Y ;
		}
	}

	void checkBounds(const BoundsCheck<N> & check) {

		if ((this->x) >= check.max_X) {
			{
				/* Debug code */
				DebugOutput << "An X value was over the global limit. Reducing value... \n" ;
				/* End Debug code */
			}
			this->x = check.max_X - 1 ;
		}
		if (this->x < check.min_X) {
			{
				/* Debug code */
				DebugOutput << "An X value was under the global minimum. Increasing value... \n" ;
				/* End Debug code */
			}
			this->x = check.min_X ;
		}
		if ((this->y) >= check.max_Y) {
			{
				/* Debug code */
				DebugOutput << "A Y value was over the global limit. Reducing value... \n" ;
				/* End Debug code */
			}
			this->y = check.max_Y - 1 ;
		}
		if (this->y < check.min_Y) {
			{
				/* Debug code */
				DebugOutput << "A Y value was under the global minimum. Increasing value... \n" ;
				/* End Debug code */
			}
			this->y = check.min_Y ;
		}
	}

	bool overBounds(const BoundsCheck<N> & check) const {
        if (overXBounds(& check) || overYBounds(& check)) {
            return true ;
        }
		else {
			return false ;
		}
	}

	bool overXBounds(const BoundsCheck<N> * check) const {
		if (((this->x) >= check->max_X) || ((this->x) < check->min_X)) {
			return true ;
		}
		else {
			return false ;
		}
	}

	bool overYBounds(const BoundsCheck<N> * check) const {
		if (((this->y) >= check->max_Y) || ((this->y) < check->min_Y)) {
			return true ;
		}
		else {
			return false ;
		}
	}

} ;




/**
 * Similar to Position, but also holds copies of each of its previous states.
 */
template<typename N>
struct Pos2 : public Position<N> {

protected:

    /**
     * A data storage type that holds a copy of an objects previous position, plus
     * the difference in time between when the object existed at one position, and when it
     * existed at the next
     */
    typedef std::pair<Position<N>, chrono::nanoseconds> PastPositionAndTimeDifferential ;

	/**
	 * A vector container storing all the previous positions of this object,
	 * with the most recent positions at the end of the vector, and the initial position at
	 * the front. See archive().
	 */
	deque<PastPositionAndTimeDifferential> * pastPositions ;

    Timer timer ;

	/**
	 * Saves our current state
	 */
	void archive() {
        //currently causing all kinds of bugs, commenting this out until time to fix
		/*
		if (timeFlow == TimeFlow::forward) { //only archive while moving forward in time
            chrono::nanoseconds time = timer.checkTimeElapsed() ;
			timer.reset() ; //reset the timer to zero

			Position<N> archived(this->x, this->y) ; //archived will just hold this, without the pastPositions (no infinite recursion here!)

			if (pastPositions->size() > 10000) { //once we go over a certain size, we'll delete the oldest to save space
				pastPositions->pop_front() ;
			}
			pastPositions->push_back({archived, time}) ;
		}
        */
	}

public:

	/**
     * Creates a Pos2 with all coordinates initialized to 0
     */
	Pos2() : Position<N>(0, 0), pastPositions(new deque<PastPositionAndTimeDifferential>)
    {
        timer.startTimer() ;
    }

	Pos2(const Position<N> & pos) : Position<N>(pos), pastPositions(new deque<PastPositionAndTimeDifferential>)
    {
        timer.startTimer() ;
    }

	Pos2(const Position<N> & pos, const BoundsCheck<N> & check) : Position<N>(pos, check), pastPositions(new deque<PastPositionAndTimeDifferential>)
    {
        timer.startTimer() ;
    }

	/**
     * Creates a Pos2 with all coordinates initialized to 0
     */
	Pos2(const BoundsCheck<N> & check) : Position<N>(check), pastPositions(new deque<PastPositionAndTimeDifferential>)
    {
       timer.startTimer() ;
    }

	/**
     * Creates a Pos2 with all coordinates initialized to n
     */
	Pos2(N n) : Position<N>(n), pastPositions(new deque<PastPositionAndTimeDifferential>)
    {
       timer.startTimer() ;
    }

	/**
     * Creates a Pos2 with all coordinates initialized to n
     */
	Pos2(N n, const BoundsCheck<N> & check) : Position<N>(n, check), pastPositions(new deque<PastPositionAndTimeDifferential>)
    {
        timer.startTimer() ;
    }

	/**
     * Creates a Pos2 all coordinates randomized, with bounds set by check
     */
    template<typename R>
	Pos2(FastRand<R> & rand) :
		Position<N>(rand),
		pastPositions(new deque<PastPositionAndTimeDifferential>)
    {
        timer.startTimer() ;
    }

	/**
     * Creates a Pos2 all coordinates randomized, with bounds set by check
     */
    template<typename R>
	Pos2(FastRand<R> & rand, const BoundsCheck<N> & check) :
		Position<N>(rand, check),
		pastPositions(new deque<PastPositionAndTimeDifferential>)
    {
        timer.startTimer() ;
    }

	/**
     * Copy constructor for Pos2
     */
    Pos2(const Pos2 & other) : Position<N>(other)  {
		if (other.pastPositions != nullptr) {
			this->pastPositions = new deque<PastPositionAndTimeDifferential>(*other.pastPositions) ;
		}
        timer = Timer() ;
        timer.startTimer() ;
	}

	/**
     * Copy constructor for Pos2
     */
    Pos2(const Pos2 & other, const BoundsCheck<N> & check) : Position<N>(other, check)  {
		if (other.pastPositions != nullptr) {
			this->pastPositions = new deque<PastPositionAndTimeDifferential>(*other.pastPositions) ;
		}
        timer = Timer() ;
        timer.startTimer() ;
	}

	/**
     * Move constructor for Pos2
     */
    Pos2(Pos2 && other) : Position<N>(std::move(other)) {

		{
		/* Debug code */
		DebugOutput << "Warning: Pos2 move constructor called. The argument's pastPositions are now null. \n" ;
		/* End Debug code */
		}

		pastPositions = other.pastPositions ;
        timer = std::move(other.timer) ;

		other.pastPositions = nullptr ;
	}

	/**
     * Move constructor for Position
     */
    Pos2(Pos2 && other, const BoundsCheck<N> & check) : Position<N>(std::move(other), check) {

		{
		/* Debug code */
		DebugOutput << "Warning: Pos2 move constructor called. The argument's pastPositions are now null. \n" ;
		/* End Debug code */
		}

		pastPositions = other.pastPositions ;
        timer = std::move(other.timer) ;

		other.pastPositions = nullptr ;
	}

	/**
     * Creates a Pos2 with coordinates initialized to the
     * given arguments
     *
     * @param x The x coordinate
     * @param y The y coordinate
     * @param z The z coordinate
     */
	Pos2(N x, N y) : Position<N>(x, y), pastPositions(new deque<PastPositionAndTimeDifferential>) {
        timer.startTimer() ;
    }

	/**
     * Creates a Pos2 with coordinates initialized to the
     * given arguments
     *
     * @param x The x coordinate
     * @param y The y coordinate
     * @param z The z coordinate
     */
	Pos2(N x, N y, const BoundsCheck<N> & check) : Position<N>(x, y, check), pastPositions(new deque<PastPositionAndTimeDifferential>) {
        timer.startTimer() ;
    }

	/**
     * Destructor for Position
     */
    virtual ~Pos2() {

		{
		/* Debug code */
		DebugOutput << "Warning: Pos2 destructor called. This instance's pastPositions were deleted \n" ;
		/* End Debug code */
		}

        timer.stopTimer() ;

		if (pastPositions != nullptr) {
			delete pastPositions ;
		}
	}

	/**
     * Assigment operator (copy).
	 *
     */
    Pos2 & operator=(const Pos2 & rhs) {

		{
        /* Debug code */
        DebugOutput << "Warning, assignment operator (copy) for Pos2 called. This may cause a performance hit. \n" ;
        /* End Debug code */
		}

		if (pastPositions != nullptr) {
			delete pastPositions ;
		}

		pastPositions = nullptr ;

	    this->Position<N>::operator=(std::move(rhs)) ;

        pastPositions = new deque<PastPositionAndTimeDifferential>() ;

        timer = Timer() ;
        timer.startTimer() ;

		for (auto i = rhs.pastPositions->begin() ; i != rhs.pastPositions->end() ; i++) {
			this->pastPositions->push_back(PastPositionAndTimeDifferential(*i)) ; //push_back()
		}

        return *this;
    }

	/**
     * Assigment operator (move)
     */
    Pos2 & operator=(Pos2 && rhs) {

		{
		/* Debug code */
		DebugOutput << "Warning, assignment operator (move) for Pos2 called. This may cause unexpected behavior. \n" ;
		/* End Debug code */
		}

		this->Position<N>::operator=(std::move(rhs)) ;

		this->pastPositions = rhs.pastPositions ;
        timer = std::move(rhs.timer) ;

		rhs.pastPositions = nullptr ;

		return(*this) ;
    }

	/**
     * Assigment operator (copy). Treats rhs as this Pos2 object's current position, and pushes back its previous state
	 * onto pastPositions.
     */
    Pos2 & operator=(const Position<N> & rhs) {

		{
        /* Debug code */
        DebugOutput << "Warning, assignment operator (copy) for Pos2 called. This may cause unexpected behavior. \n" ;
        /* End Debug code */
		}

        setAll(rhs) ;

        /* no need to make any changes to timer */

        return *this;
    }

	/**
     * Assigment operator (move)
     */
    Pos2 & operator=(Position<N> && rhs) {

		{
		/* Debug code */
		DebugOutput << "Warning, assignment operator (move) for Pos2 called. This may cause unexpected behavior. \n" ;
		/* End Debug code */
		}

		setAll(rhs) ;

        /* no need to make any changes to timer */

        return *this ;
    }

	bool operator==(const Pos2 & rhs) const {
		return Position<N>::operator==(rhs) ;
	}

	bool operator==(Pos2 & rhs) const {
		return Position<N>::operator==(rhs) ;
	}

	bool operator==(const Position<N> & rhs) const {
		return Position<N>::operator==(rhs) ;
	}

	bool operator==(Position<N> & rhs) const {
		return Position<N>::operator==(rhs) ;
	}

	bool operator!=(Pos2 & rhs) const {
		return Position<N>::operator!=(rhs) ;
	}

	bool operator!=(const Pos2 & rhs) const {
		return Position<N>::operator!=(rhs) ;
	}

	bool operator!=(Position<N> & rhs) const {
		return Position<N>::operator!=(rhs) ;
	}

	bool operator!=(const Position<N> & rhs) const  {
		return Position<N>::operator!=(rhs) ;
	}

	Pos2 operator+(const Pos2 & rhs) const  {
		return Position<N>::operator+(rhs) ;
	}

	Position<N> operator+(const Position<N> & rhs) const override {
		Pos2 pos2 = Position<N>::operator+(rhs) ;
		return pos2 ;
	}

	Pos2 operator-(const Pos2 & rhs) const {
		return Position<N>::operator-(rhs) ;
	}

	Position<N> operator-(const Position<N> & rhs) const override {
		return Position<N>::operator-(rhs) ;
	}


	Position<N> operator*(const N n) const override {

        Pos2 temp(this->x, this->y) ;

		temp.x = temp.x * n ;
		temp.y = temp.y * n ;

		return temp ;
	}

    Position<N> operator/(const N n) const override {

        Pos2 temp(this->x, this->y) ;

		temp.x = temp.x / n ;
		temp.y = temp.y / n ;

		return temp ;
	}

	/**
	 * @return The size of the past positions archive
	 */
	size_t archivedPositionsCount() {
		return pastPositions->size() ;
	}

	/**
	 * @return Pop the last added Position from the queue
	 */
	PastPositionAndTimeDifferential popLastArchivedPosition() {
		size_t size = pastPositions->size() ; //debug var, delete this
		PastPositionAndTimeDifferential pop = pastPositions->back() ;
		pastPositions->pop_back() ;
		return pop ;
	}

	const deque<PastPositionAndTimeDifferential> * getHistory() {
		return pastPositions ;
	}

	void setAll(const N x, const N y) override {
		archive() ;
		this->Position<N>::setAll(x, y) ;
	}

	void setAll(const N x, const N y, const BoundsCheck<N> & check) override {
		archive() ;
		Position<N>::setAll(x, y, check) ;
	}

	void setAll(const Position<N> & other) override {
		setAll(other.getX(), other.getY()) ;
	}

	void setAll(const Position<N> & other, const BoundsCheck<N> & check) override {
		setAll(other.getX(), other.getY(), check) ;
	}

	void setAll(const N n) override { setAll(n, n) ; }

	void setAll(const N n, const BoundsCheck<N> & check) override { setAll(n, n, check) ; }

	void setAllZero() override { setAll(0) ; }


	void setX(const N x) override { setAll(x, this->y) ; }

	void setX(const N x, const BoundsCheck<N> & check) override { setX(x) ; this->checkBounds(check) ; }

	void setY(const N y) override { setAll(this->x, y) ; }

	void setY(const N y, const BoundsCheck<N> & check) override { setY(y) ; this->checkBounds(check) ; }


	void x_plus_one() override { setX(this->x++) ; }

	void x_plus_one(const BoundsCheck<N> & check) override { setX(this->x++) ; this->checkBounds(check) ; }

	void x_minus_one() { setX(this->x--) ; }

	void x_minus_one(const BoundsCheck<N> & check) override { setX(this->x--) ; this->checkBounds(check) ; }


	void y_plus_one() override { setY(this->y++) ; }

	void y_plus_one(const BoundsCheck<N> & check) override { setY(this->y++) ; this->checkBounds(check) ; }

	void y_minus_one() override { setY(this->y--) ; }

	void y_minus_one(const BoundsCheck<N> & check) override { setY(this->y--) ; this->checkBounds(check) ; }

	void moveRight() { setAll((this->x+1), this->y) ; }
	void moveLeft() { setAll((this->x-1), this->y) ; }
	void moveUp() { setAll(this->x, (this->y+1)) ; }
	void moveDown() { setAll(this->x, (this->y-1)) ; }

	void moveUpRight() { setAll((this->x+1), (this->y+1)) ; }
	void moveUpLeft() { setAll((this->x-1), (this->y+1)) ; }
	void moveDownRight() { setAll((this->x+1), (this->y-1)) ; }
	void moveDownLeft() { setAll((this->x-1), (this->y-1)) ; }

	/**
	 * Increments or decrements the x, y and z values according to
	 * the arguments passed in. Use negative values to decrement. Passing
	 * 0 for any argument will keep the x, y, or z value the same.
	 *
	 * @param delta_x The change in x value
	 * @param delta_y The change in y value
	 */
	void modify(N delta_x, N delta_y) override {
		auto tempX = this->x ;
		auto tempY = this->y ;

		tempX += delta_x ;
		tempY += delta_y ;

		setAll(tempX, tempY) ;
	}

	/**
	 * Increments or decrements the x, y and z values according to
	 * the arguments passed in. Use negative values to decrement. Passing
	 * 0 for any argument will keep the x, y, or z value the same.
	 *
	 * @param delta_x The change in x value
	 * @param delta_y The change in y value
	 * @param delta_z The change in z value
	 */
	void modify(N delta_x, N delta_y, const BoundsCheck<N> & check) override {
		auto tempX = this->x ;
		auto tempY = this->y ;

		tempX += delta_x ;
		tempY += delta_y ;

		setAll(tempX, tempY, check) ;
	}

	void moveHere(N x, N y) override {
		setAll(x, y) ;
	}

	void moveHere(N x, N y, const BoundsCheck<N> & check) override {
		moveHere(x, y) ;
		this->checkBounds(check) ;
	}

	void moveHere(const Position<N> & other) override {
		setAll(other.getX(), other.getY()) ;
	}

	void moveHere(const Position<N> & other, const BoundsCheck<N> & check) override {
		moveHere(other) ;
		this->Position<N>::checkBounds(check) ;
	}

} ;


/**
 * This class provides facilities for storing an object's current vector,
 * predicting its next Position, monitoring its speed, maintaining a record of its
 * last two Positions (for more detailed record keeping of past Positions, see Pos2),
 * and more.
 *
 * Note: do not use with unsigned ints
 */
template<typename N>
struct Vectr : public Position<float> {

protected:

	static BasicMutex * sharedVelMutex ;

    /**
     * The Position preceding the most recent Position
     */
    Position<N> last ;

    /**
     * The Position most recently visited
     */
	Position<N> mostRecent ;

    /**
     * A pointer to the current Position
     */
	const Position<N> * current ;

    /**
     * The non-normalized distance between the current Position and mostRecent Position
     */
    N absDistanceMoved = 0 ;

	N * totalDistanceMoved ;

	/**
	 * Monitors velocity
	 */
	Velocity<N> * velocity ;

	/* The current rotation of this vector */
	Angle currentRotation = 0.0 ;


	bool sharedVelBool = true ;

	/* x, y, and z here (the one we inherited) will be used as deltas that we can add to current to calculate next */
	Vectr(const Position<float> & overrideCurrData, const Position<N> * current_, SafeBoolean tf) ;

	void update() ;


public:

    Vectr() ;
    Vectr(Angle rotation, SafeBoolean tf) ;
	Vectr(FastRand<N> randm) ;
	Vectr(float headingX, float headingY, Angle rotation, SafeBoolean tf) ;
	Vectr(float headingX, float headingY, Position<N> * current_, Angle rotation, SafeBoolean tf) ;
	Vectr(const Position<N> * current_, Angle rotation, SafeBoolean tf) ;
	Vectr(const Vectr<N> & other) ;
	Vectr(Vectr<N> && other) ;
	~Vectr() ;

	Vectr & operator=(Vectr<N> && rhs) ;

	/**
	 * Rotate the number of degrees equal to the difference between
	 * this vectors current rotation, and the given angle 𝛳
	 */
	void setVectorAndOrientation(Angle 𝛳) ;

	/**
	 * Rotate the number of degrees equal to the difference between
	 * this vectors current rotation, and the given angle 𝛳
	 */
	void rotateVectorAndOrientation(Angle 𝛳) ;

    void rotateVector(Angle 𝛳) ;

    void rotateOrientation(Angle 𝛳) ;

	Vectr & copy(const Vectr & other, const Position * newCurrent) ;
    Vectr copy() const ;

	const Velocity<N> * getVelocity() const { return this->velocity ; }

	const Angle * getOrientation() const { return & currentRotation ; }

	Angle copyOrientation() const { return currentRotation ; }

    void modifyOrientation(const Angle & angleOffset) { currentRotation += angleOffset ; }

	void overrideCurrentOrientation(const Angle & newAngle) { currentRotation = newAngle; }

	const Position * getCurrent() const { return current ; }

	const Position getLast() const { return this->last ; }

	void updateAndNormalize() ;

	N getLastMoveDistance() const { return absDistanceMoved ; }

	Velocity<N> & calculateVelocity() ;

	Position<N> calculateNextPosition(float modifier = 1.0) ;

	Position<N> calculateNextPositionChecked(float modifier = 1.0, const BoundsCheck<N> & = BoundsCheck<N>::defaultCheck) ;


	Position<N> calculateReverseNextPosition(float modifier = 1.0, const BoundsCheck<N> & = BoundsCheck<N>::defaultCheck) ;


	Position<N> calculateReverseXPosition(float modifier = 1.0, const BoundsCheck<N> & = BoundsCheck<N>::defaultCheck) ;


	Position<N> calculateReverseYPosition(float modifier = 1.0, const BoundsCheck<N> & = BoundsCheck<N>::defaultCheck) ;


} ;

template<typename N>
BasicMutex * Vectr<N>::sharedVelMutex = Velocity<N>::sharedVelMutex ;

template<typename N>
Vectr<N>::Vectr() :
    Position<float>(0, -1), /* default direction is up */
	current(nullptr),
    totalDistanceMoved(new N()),
	velocity(nullptr),
    currentRotation(0.0){}

template<typename N>
Vectr<N>::Vectr(Angle rotation, SafeBoolean tf) :
    Position<float>(0, -1), /* default direction is up */
    current(nullptr),
    totalDistanceMoved(new N()),
    velocity(nullptr),
    currentRotation(rotation)
{
	if (tf == SafeBoolean::t) {
		velocity = new Velocity<N>(totalDistanceMoved, &sharedVelBool) ;
	}
	else { // if (tf == SafeBoolean::f)
		velocity = nullptr ;
	}
}

template<typename N>
Vectr<N>::Vectr(FastRand<N> randm) :
	Position<float>(randm(), randm()),
	current(nullptr),
	totalDistanceMoved(new N()),
	velocity(nullptr)
{
	FastRand<float> randmf(0, 360) ;
	currentRotation = randmf() ;
}

template<typename N>
Vectr<N>::Vectr(float headingX, float headingY, Angle rotation, SafeBoolean tf) :
	Position<float>(headingX, headingY),
	current(nullptr),
	totalDistanceMoved(new N),
    currentRotation(rotation)
{
	if (tf == SafeBoolean::t) {
		velocity = new Velocity<N>(totalDistanceMoved, &sharedVelBool) ;
	}
	else { // if (tf == SafeBoolean::f)
		velocity = nullptr ;
	}
}

template<typename N>
Vectr<N>::Vectr(float headingX, float headingY, Position<N> * current_, Angle rotation, SafeBoolean tf) :
	Position<float>(headingX, headingY),
	current(current_),
	totalDistanceMoved(new N),
    currentRotation(rotation)
{
	if (tf == SafeBoolean::t) {
		velocity = new Velocity<N>(totalDistanceMoved, &sharedVelBool) ;
	}
	else { // if (tf == SafeBoolean::f)
		velocity = nullptr ;
	}
}

template<typename N>
Vectr<N>::Vectr(const Position<N> * current_, Angle rotation, SafeBoolean tf) :
	Position<float>(0, -1),
    last(*current_),
	mostRecent(*current_),
    current(current_),
	totalDistanceMoved(new N),
    currentRotation(rotation)
{
	if (tf == SafeBoolean::t) {
		velocity = new Velocity<N>(totalDistanceMoved, &sharedVelBool) ;
	}
	else { // if (tf == SafeBoolean::f)
		velocity = nullptr ;
	}
}


template<typename N>
Vectr<N>::Vectr(const Vectr<N> & other) :
	Position<float>(other),
    last(Position<N>(other.last)),
	mostRecent(Position<N>(other.mostRecent)),
	current(other.current),
    absDistanceMoved(other.absDistanceMoved),
	totalDistanceMoved(new N(*other.totalDistanceMoved)),
	currentRotation(other.currentRotation)
{
	if (other.velocity != nullptr) {
		velocity = new Velocity<N>(totalDistanceMoved, &sharedVelBool) ;
	}
	else { // if (tf == SafeBoolean::f)
		velocity = nullptr ;
	}
}


template<typename N>
Vectr<N>::Vectr(Vectr<N> && other) :
	Position<float>(std::move(other)),
    last(std::move(other.last)),
	mostRecent(std::move(other.mostRecent)), current(other.current),
    absDistanceMoved(other.absDistanceMoved),
	totalDistanceMoved(other.totalDistanceMoved),
	velocity(other.velocity),
	currentRotation(std::move(other.currentRotation))
{
	other.current = nullptr ;
	other.totalDistanceMoved = nullptr ;
	other.velocity = nullptr ;
}

template<typename N>
Vectr<N>::~Vectr()
{
	/* check if we're running a velocity monitor first */
	if (velocity != nullptr) {
		sharedVelMutex->lock() ;
	}

	sharedVelBool = false ;

	this->current = nullptr ;

	if (velocity != nullptr) {
		delete velocity;
	}

	if (totalDistanceMoved != nullptr) {
		delete totalDistanceMoved ;
	}

	if (velocity != nullptr) {
		sharedVelMutex->unlock() ;
	}
}


template<typename N>
Vectr<N> & Vectr<N>::operator=(Vectr<N> && rhs) {
	if (this != &rhs) {

		this->Position<float>::operator=(std::move(rhs)) ;
        this->last = Position<N>(rhs.last) ;
		this->mostRecent = Position<N>(rhs.mostRecent) ;
		this->current = rhs.current ;
        this->absDistanceMoved = rhs.absDistanceMoved ;
		this->totalDistanceMoved = rhs.totalDistanceMoved ;
		this->velocity = rhs.velocity ;
		this->currentRotation = std::move(rhs.currentRotation) ;

		rhs.current = nullptr ;
		rhs.totalDistanceMoved = nullptr ;
		rhs.velocity = nullptr ;
	}
	return *this ;
}

template<typename N>
void Vectr<N>::setVectorAndOrientation(Angle 𝛳) {

    normalize() ;

    this->Position<N>::rotate(𝛳) ;

	this->currentRotation = 𝛳 ; //i.e. (currentRotation + abs𝛳) % 360

	assert((currentRotation.val() == 𝛳.val())) ; /* debug code, remove */

	/* we should still be normalized here */
}

template<typename N>
void Vectr<N>::rotateVectorAndOrientation(Angle 𝛳) {

	normalize() ;

	this->Position<N>::rotate(𝛳) ;

	this->currentRotation += 𝛳 ; //i.e. (currentRotation + abs𝛳) % 360

	/* we should still be normalized here */
}

template<typename N>
void Vectr<N>::rotateVector(Angle 𝛳) {

    normalize() ;

    this->Position<N>::rotate(𝛳) ;
}

template<typename N>
void Vectr<N>::rotateOrientation(Angle 𝛳) {
    this->currentRotation += 𝛳 ;
    //i.e. (currentRotation + abs𝛳) % 360
}

template<typename N>
Vectr<N> & Vectr<N>::copy(const Vectr & other, const Position * newCurrent) {

	this->Position<float>::operator=(other) ;

	this->last = Position<N>(other.last) ;
	this->mostRecent = Position<N>(other.mostRecent) ;
	this->current = newCurrent ;
	this->absDistanceMoved = other.absDistanceMoved ;
	this->totalDistanceMoved = new N(*other.totalDistanceMoved) ;
	this->currentRotation = other.currentRotation ;

	if (other.velocity != nullptr) {
		this->velocity = new Velocity<N>(this->totalDistanceMoved, &this->sharedVelBool) ;
	}
	else {
		this->velocity = nullptr ;
	}

	return *this ;
}

template<typename N>
Vectr<N> Vectr<N>::copy() const {

	Vectr<N> newVect ;
	newVect.copyVect(*this) ;

    return std::move(newVect) ;
}

template<typename N>
ostream & operator<<(std::ostream & os, const Vectr<N> * vec) {
	os << "Vector: X = " << vec->x << ", Y = " << vec->y << ", Z = " << vec->z << '\n' ;
	return os ;
}

template<typename N>
ostream & operator<<(std::ostream & os, const Vectr<N> & vec) {
	os << "Vector: X = " << vec.x << ", Y = " << vec.y << ", Z = " << vec.z << '\n' ;
	return os ;
}


template<typename N>
void Vectr<N>::update() {

	if ((current != nullptr) && (mostRecent != *current)) { //only if we've moved...

        absDistanceMoved = calcEuclidianDistance(mostRecent, *current) ;
		*totalDistanceMoved += absDistanceMoved ;

		Position<N> temp = ((*current) - mostRecent) ;               /*  uses Position operator- overload to subtract
                                                                      our x, y, and z (which are offset values) from those
                                                                      stored in current, giving our new location  */
		setAll(temp.getX(), temp.getY()) ;
        last = mostRecent ;
		mostRecent = std::move((Position<N>(*this->current))) ;
	}

}

template<typename N>
void Vectr<N>::updateAndNormalize() {
	update() ;
	normalize() ;
}

template<typename N>
Velocity<N> & Vectr<N>::calculateVelocity() {
	return this->velocity ;
}

template<typename N>
Position<N> Vectr<N>::calculateNextPosition(float modifier) {

	normalize() ;

	auto stor = *this * modifier ;

	N nx ;
	N ny ;
	N nz ;

	nx = (current)->getX() + stor.getX() ;
	ny = (current)->getY() + stor.getY() ;

	Position<N> next(nx, ny) ;

	return next ;
}

template<typename N>
Position<N> Vectr<N>::calculateNextPositionChecked(float modifier, const BoundsCheck<N> & check) {

	normalize() ;

	auto stor = *this * modifier ;

	N nx ;
	N ny ;
	N nz ;

	nx = (current)->getX() + stor.getX() ;
	ny = (current)->getY() + stor.getY() ;

	Position<N> next(nx, ny, check) ;

	return next ;
}

template<typename N>
Position<N> Vectr<N>::calculateReverseNextPosition(float modifier, const BoundsCheck<N> & check) {
	x = (x * -1) ;
	y = (y * -1) ;
	return calculateNextPosition(modifier, check) ;
}

template<typename N>
Position<N> Vectr<N>::calculateReverseXPosition(float modifier, const BoundsCheck<N> & check) {
	x = (x * -1) ;
	return calculateNextPositionChecked(modifier, check) ;
}

template<typename N>
Position<N> Vectr<N>::calculateReverseYPosition(float modifier, const BoundsCheck<N> & check) {
	y = (y * -1) ;
	return calculateNextPositionChecked(modifier, check) ;
}

template<typename N>
Position<N> & operator+=(Position<N> & rhs, const Position<N> & lhs) {
	rhs.setX(rhs.getX() + lhs.getX()) ;
	rhs.setY(rhs.getY() + lhs.getY()) ;
	return rhs ;
}

template<typename N>
Position<N> & operator-=(Position<N> & lhs, const Position<N> & rhs) {
	lhs.setX(lhs.getX() - rhs.getX()) ;
	lhs.setY(lhs.getY() - rhs.getY()) ;
	return lhs ;
}

/*
template<typename N>
Vectr<N> & operator+=(Vectr<N> & rhs, Position<N> & lhs) {
    rhs.setX(rhs.getX() + lhs.getX()) ;
    rhs.setY(rhs.getY() + lhs.getY()) ;
    return rhs ;
}

template<typename N>
Vectr<N> & operator-=(Vectr<N> & rhs, Position<N> & lhs) {
    rhs.setX(rhs.getX() - lhs.getX()) ;
    rhs.setY(rhs.getY() - lhs.getY()) ;
    return rhs ;
}

*/


/**
 * Translates a Position from within the World to a Position
 * equivelent within the boundaries of the current screen.
 * Gets the current GLOBAL_max_Position (and min) from World
 * to calculate the ratio
 *
 * @param inSpriteFight The Position from within the World
 */
template<typename T>
extern Position<T> transPosition(const Position<T> & inSpriteFight) {

	auto worldXSize = globalMaxX() /*- GameObject::GLOBAL_min_X*/ ;
	auto worldYSize = globalMaxY() /*- GameObject::GLOBAL_min_Y*/ ;

	T tempX = inSpriteFight.getX() /*+ (worldXSize - GameObject::GLOBAL_max_X)*/ ;
	T tempY = inSpriteFight.getY() /*+ (worldYSize - GameObject::GLOBAL_max_Y)*/ ;

	unsigned tw = termWidth() ;
	unsigned th = termHeight() ;

	T x = (tw * tempX)/worldXSize ;
	T y = (th * tempY)/worldYSize ;

	return Position<T>(x, y) ;
}

template<typename N>
struct Resolution : public Position<N> {

private:

	N getZ() const { return 0 ; }

	virtual void setZ(const N z) {}

public:

	Resolution() :
		Position<N>(0, 0) {}

	Resolution(N x, N y) :
		Position<N>(x, y) {}

	Resolution(const Resolution & other) :
		Position<N>(other) {}

	Resolution(Resolution && other) :
		Position<N>(std::move(other)) {}

	Resolution & operator=(const Resolution & rhs) {
		if (this != &rhs) {
			this->Position<N>::operator=(rhs) ;
		}
		return *this ;
	}

	~Resolution() {}

	Resolution & operator=(Resolution && rhs) {
		if (this != &rhs) {
			this->Position<N>::operator=(std::move(rhs)) ;
		}
		return *this ;
	}

	double operator/(const Resolution & rhs) const {

        double x_quotient = (static_cast<double>(this->getX()) / static_cast<double>(rhs.getX())) ;
		double y_quotient = (static_cast<double>(this->getY()) / static_cast<double>(rhs.getY())) ;

		double avrg = average<double>(x_quotient, y_quotient) ;

		return avrg ;
	}

	friend ostream & operator<<(std::ostream & os, const Resolution<N> * pos) {
		os << pos->x << "x" << pos->y << '\n' ;
		return os ;
	}

	friend ostream & operator<<(std::ostream & os, const Resolution<N> & pos) {
		os << pos.x << "x" << pos.y << '\n' ;
		return os ;
	}

} ;





















#endif
