//
//  Util.h
//  World
//
//  Created by Adam James Leuer on 3/20/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef SpriteFight_Util_h
#define SpriteFight_Util_h


#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <cmath>


using namespace std ;

constexpr auto pi_const = 3.141592653589793238462643383279502884197169399375105820974944L ; /* needs UTF-8 support */

/**
 * Used to avoid ambiguity when calling various constructors
 * with integral values that might be confused for boolean
 */
enum class SafeBoolean {
	t,
	f
};

template<typename N>
const static bool checkIfFloatingPointType() {
	if (typeid(N) == typeid(long double)) {
		return true ;
	}
	if (typeid(N) == typeid(double)) {
		return true ;
	}
	if (typeid(N) == typeid(float)) {
		return true ;
	}
	else {
		return false ;
	}
}


/*
 * Code partial credit stackoverflow: http://stackoverflow.com/questions/4633177/c-how-to-wrap-a-float-to-the-interval-pi-pi
 * todo: reimplement
 */
template<typename M, typename N>
double Mod(M x_in, N y_in) {

	double x = static_cast<double>(x_in) ; /* x is ok */

	double y = static_cast<double>(y_in) ;

	static_assert(!std::numeric_limits<M>::is_exact , "Mod: floating-point type expected");
	static_assert(!std::numeric_limits<N>::is_exact , "Mod: floating-point type expected");

	if (0. == y)
		return x;

	double m = x - y * floor(x/y);

	// handle boundary cases resulted from floating-point cut off:

	if (y > 0)              // modulo range: [0..y)
	{
		if (m>=y)           // Mod(-1e-16             , 360.    ): m= 360.
			return 0;

		if (m<0 )
		{
			if (y+m == y)
				return 0  ; // just in case...
			else
				return y+m; // Mod(106.81415022205296 , _TWO_PI ): m= -1.421e-14
		}
	}
	else                    // modulo range: (y..0]
	{
		if (m<=y)           // Mod(1e-16              , -360.   ): m= -360.
			return 0;

		if (m>0 )
		{
			if (y+m == y)
				return 0  ; // just in case...
			else
				return y+m; // Mod(-106.81415022205296, -_TWO_PI): m= 1.421e-14
		}
	}

	return m;
}

/**
 * @param first The first value to average
 * @param second The second value to average
 *
 * @return The average of the two values
 */
template<typename N>
N average(N first, N second) {
	N sum = (first + second) ;
	double result = (static_cast<double>(sum) / static_cast<double>(2)) ;
	return static_cast<N>(result) ;
}

template<typename N>
N average(const vector<N> & numbers) {
	unsigned i = 0 ;
	N sum = 0 ;
	while(i < numbers.size()) {
		sum += numbers.at(i) ;
		i++ ;
	}
	N result = sum/i ;
	return result ;
}

template<typename T, template <typename, typename = std::allocator<T>> class Container>
T sumElements(const Container<T, std::allocator<T>> & cont) {

    T sum ;
    auto i = cont.begin() ;
    sum = *i ;

    for (i++ ; i != cont.end() ; i++) {
        sum += *i ;
    }

    return sum ;
}


template<typename N>
N setUnsigned(N n) {
	if (n < 0) {
		n = (n * -1) ;
	}
	return n ;
}

template<typename N>
N difference(N n0, N n1) {
	N saveSign = n1 / (setUnsigned(n1)) ;
	n1 = setUnsigned(n1) ;
}


template<typename T>
T pythag(T a, T b) {
	return sqrt((pow(a,2)) + (pow(b,2))) ;
}

inline float sinNeg(float n) {
	return (-1 * (sin(n))) ;
}

template<typename T>
T findSmallest_helper(unsigned long currSmallest, vector<T> cont) {
	//vector<T*> smallerElem = vector<T*>() ;
	auto size = cont.size() ;

	for (auto i = 0 ; i != cont.size() ; i++) {

		if (size == 1) {
			return cont.at(currSmallest) ;
		}
		if (cont.at(i) < cont.at(currSmallest)) {
			currSmallest = i ;
			size-- ;
		}
	}
	return cont.at(currSmallest) ;
}

template<typename T>
T findSmallest(vector<T> cont) {
	return findSmallest_helper(0, cont) ;
}

template<typename T>
T findLargest_helper(unsigned long currLargest, vector<T> cont) {
	auto size = cont.size() ;

	for (auto i = 0 ; i != cont.size() ; i++) {

		if (size == 1) {
			return cont.at(currLargest) ;
		}
		if (cont.at(i) > cont.at(currLargest)) {
			currLargest = i ;
			size-- ;
		}
	}
	return cont.at(currLargest) ;
}

template<typename T>
T findLargest(vector<T> cont) {
	return findLargest_helper(0, cont) ;
}

template<typename N>
N ceilling(N n1, N n2) {
	if (n1 >= n2) {
		return n1 ;
	}
	else {
		return n2 ;
	}
}

template<typename N>
N floor(N n1, N n2) {
	if (n1 <= n2) {
		return n1 ;
	}
	else {
		return n2 ;
	}
}


/**
 * Rounds a float or double to an int or long
 */
template<typename F = float, typename I = int> // F = some float or double, I = some unsigned, int, long, etc
I roundF(F value) {
    if ((typeid(F) == typeid(unsigned)) || (typeid(F) == typeid(int)) || (typeid(F) == typeid(long)))  {
        return value ;
    }
    else {
        F temp = (value >= 0.0f) ? (floor(value + 0.5f)) : (ceil(value - 0.5f)) ;
        I round = static_cast<I>(temp) ;

		/* catch a weird problem where this was returning a negative value from a posititive input */
		if ((value >= 0) && (round < 0)) {
			round = (round * -1) ;
		}

        return round ;
    }
}

template<typename I = int, class FloatPosition>
FloatPosition roundF(FloatPosition & pos) {
    if ((typeid(pos.x) == typeid(unsigned)) || (typeid(pos.x) == typeid(int)) || (typeid(pos.x) == typeid(long)))  {
        return pos ;
    }
    else {
        I tempX = roundFI(pos.getX()) ;
        I tempY = roundFI(pos.getY()) ;
        I tempZ = roundFI(pos.getZ()) ;
        return FloatPosition(tempX, tempY, tempZ) ;
    }
}



template<typename I = int, class FloatPosition>
FloatPosition roundF(FloatPosition * pos) {
    if ((typeid(pos->x) == typeid(unsigned)) || (typeid(pos->x) == typeid(int)) || (typeid(pos->x) == typeid(long)))  {
        return pos ;
    }
    else {
        I tempX = roundFI(pos->getX()) ;
        I tempY = roundFI(pos->getY()) ;
        I tempZ = roundFI(pos->getZ()) ;
        return FloatPosition(tempX, tempY, tempZ) ;
    }
}

template<typename I = int, class FloatPosition>
FloatPosition * roundF(FloatPosition * pos) {
    if ((typeid(pos->x) == typeid(unsigned)) || (typeid(pos->x) == typeid(int)) || (typeid(pos->x) == typeid(long)))  {
        return pos ;
    }
    else {
        I tempX = roundFI(pos->getX()) ;
        I tempY = roundFI(pos->getY()) ;
        I tempZ = roundFI(pos->getZ()) ;
        return new FloatPosition(tempX, tempY, tempZ) ;
    }
}

template<typename Radians = double>
double convertToDegrees(const Radians angle_rad) {
	double angle_in_radians = static_cast<double>(angle_rad) ;
	double angle_in_degrees = angle_in_radians * (180.0L / pi_const) ;
	return angle_in_degrees ;
}

template<typename Degrees = double>
double convertToRadians(const Degrees angle_deg) {
	double angle_in_degrees = static_cast<double>(angle_deg) ;
	double angle_in_radians = angle_in_degrees / (180.0L / pi_const) ;
	return angle_in_radians ;
}


inline unsigned termWidth() {
	unsigned r = atoi(getenv("COLUMNS")) ;
	return r ;
}

inline unsigned termHeight() {
	unsigned r = atoi(getenv("LINES")) ;
	return r ;
}

/**
 * Overloads operator + for std::string to allow
 * appending any type T
 *
 * @param rhs The text to append
 */
template<class T>
string operator+(const string & str, const T & rhs) {
	string app = to_string(rhs) ;
	string ret = str ;
	ret += app ;
	return ret ;
}

inline string operator +(const string & str, const char * rhs) {
	string app(rhs) ;
	string ret = str ;
	ret += app ;
	return ret ;
}

/* powerup. other */
extern char * basicAlphabet ;

const string generateName(unsigned int length) ;





#endif
