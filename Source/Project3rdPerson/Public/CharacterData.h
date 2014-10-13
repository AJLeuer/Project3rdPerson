//
//  CharacterData.h
//  World
//
//  Created by Adam James Leuer on 4/29/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__CharacterData__
#define __SpriteFight__CharacterData__


#include <iostream>
#include <ostream>

#include "BoundsCheck.hpp"
#include "GameRandom.hpp"

using namespace std ;

/**
 * A parent type that will define the basic functions and members for Damage and Health (and other similar data types
 * if we need them)
 */
struct CharacterData {
	
protected:
	
	unsigned long baseValue ;
	unsigned int modifier ;
	
public:
	
	CharacterData() :
		baseValue(0),
		modifier(1) {}
	
	CharacterData(unsigned long b) :
		baseValue(b),
		modifier(1) {}
	
	
	CharacterData(unsigned long b, unsigned m) :
		baseValue(b),
		modifier(m) {}
	
	
	CharacterData(const CharacterData & other) :
		baseValue(other.baseValue),
		modifier(other.modifier) {}
	
	CharacterData(CharacterData && other) :
		baseValue(other.baseValue),
		modifier(other.modifier) {}
	
	
	CharacterData & operator=(const CharacterData & rhs) {
		if (this != &rhs) {
			this->baseValue = rhs.baseValue ;
			this->modifier = rhs.modifier ;
		}
		return *this ;
	}
	
	CharacterData & operator=(CharacterData && rhs) {
		if (this != &rhs) {
			this->baseValue = rhs.baseValue ;
			this->modifier = rhs.modifier ;
		}
		return *this ;
	}
	
	bool operator==(CharacterData & rhs) {
		return (this->value() == rhs.value()) ;
	}
	
	bool operator!=(CharacterData & rhs) {
		return !(this->operator==(rhs)) ;
	}
	
	bool operator>(CharacterData & rhs) {
		return (this->value() > rhs.value()) ;
	}
	
	bool operator<(CharacterData & rhs) {
		return (this->value() < rhs.value()) ;
	}
	
	bool operator>=(CharacterData & rhs) {
		return (this->value() >= rhs.value()) ;
	}
	
	bool operator<=(CharacterData & rhs) {
		return (this->value() <= rhs.value()) ;
	}
	
	CharacterData & operator+(const CharacterData & rhs) {
		this->baseValue += rhs.baseValue ;
		this->modifier += rhs.modifier ;
		return *this ;
	}
	
	CharacterData & operator-(const CharacterData & rhs) {
		this->baseValue -= rhs.baseValue ;
		this->modifier -= rhs.modifier ;
		return *this ;
	}
	
	/**
	 * Override the << output stream operator
	 */
	inline
	friend ostream & operator<<(std::ostream & os, CharacterData & gmd) {
		os << gmd.value() ;
		return os ;
	}
	
	/**
	 * Override the << output stream operator
	 */
	inline
	friend ostream & operator<<(std::ostream & os, const CharacterData & gmd) {
		os << gmd.value() ;
		return os ;
	}
	
	
	/**
	 * @return The value of this CharacterData object (e.g. Health or Damage)
	 */
	unsigned long value() const {
		return baseValue * modifier ;
	}
	
	/**
	 * See value()
	 *
	 * @return The total amount of this CharacterData value (e.g. Health or Damage
	 */
	unsigned long operator()() {
		return value() ;
	}
	
} ;



/**
 * A data structure that will hold damage values
 */
struct Damage : public CharacterData {
	
public:
	
	Damage() :
		CharacterData() {}
	
	Damage(long b) :
		CharacterData(b) {}
	
	Damage(unsigned long b, unsigned m) :
		CharacterData(b, m) {}
	
	Damage(const Damage & other) :
		CharacterData(other) {}
	
	
} ;



/**
 * A data structure that will hold health values
 */
struct Health : public CharacterData {
	
public:
	
	Health() :
		CharacterData() {}
	
	Health(long b) :
		CharacterData(b) {}
	
	Health(unsigned long b, unsigned m) :
		CharacterData(b, m) {}
	
	Health(const Health & other) :
		CharacterData(other) {}
	
	
} ;



/* Below are a few enums we can use in various ways through the game.
 Note for all enums here: the value -1 essentially can be considered as essentially
 as an equivalent to NULL */
enum class Colors {
	undefined = -1,
	green,
	blue,
	purple,
	red,
	orange,
	brown,
	gray,
	silver,
	gold,
	transparent,
	various,
	//add more here
	last //always last
};

inline Colors getRandomColor() {
	FastRand<unsigned> randm(0, static_cast<unsigned>(Colors::last)) ;
	//auto c = static_cast<Colors>( ;)
	return Colors::blue ;
}

enum class Alert {
	
	noalert = -1,
	danger = 0,
	nearbyEnemy = 1,
	lowHealth = 2,
	lowEnergy = 3, /*i.e. for abilities*/
	lowResource = 4,
	nearbyMoney = 5,
	nearbyBoost = 6
	//add more here
	
} ;

enum class CharacterState {
	nocs = -1,
	/*typically for player and NPCs*/
	normal = 0,
	inCombat = 1,
	inDialogue = 2,
	idle = 3
	
} ;

enum class DoA {
	nodoa = -1,
	dead = 0,
	alive = 1
	
} ;

enum class Reaction {
	
	noreact = -100,
	/*typically npc*/
	loyal = 2,
	friendly = 1,
	neutral = 0,
	unfriendly = (-friendly),
	hostile = (-loyal)
	//add more here
} ;


inline
std::ostream & operator<<(std::ostream & os, const Alert & alt) {
	switch (alt) {
		case Alert::noalert:
			os << "No alert";
			break ;
		case Alert::danger:
			os << "Danger" ;
			break;
		case Alert::nearbyEnemy:
			os << "Enemy nearby" ;
			break ;
		case Alert::lowHealth:
			os << "Health low" ;
			break ;
		case Alert::lowEnergy:
			os << "Energy low" ;
			break ;
		case Alert::lowResource:
			os << "Resource low" ;
			break ;
		case Alert::nearbyMoney:
			os << "Money nearby" ;
			break ;
		case Alert::nearbyBoost:
			os << "Nearby boost" ;
			break ;
	}
	return os ;
}

inline
std::ostream & operator<<(std::ostream & os, const CharacterState & cs) {
	switch (cs) {
		case CharacterState::nocs:
			os << "No character state";
			break ;
		case CharacterState::idle:
			os << "Idle" ;
			break;
		case CharacterState::inCombat:
			os << "In combat" ;
			break ;
		case CharacterState::inDialogue:
			os << "In dialogue" ;
			break ;
		case CharacterState::normal:
			os << "Normal" ;
			break ;
		default:
			break;
	}
	return os ;
}

inline
std::ostream & operator<<(std::ostream & os, const DoA & doa) {
	switch (doa) {
		case DoA::nodoa:
			os << "No DoA value" ;
			break ;
		case DoA::alive:
			os << "Alive" ;
			break;
		case DoA::dead:
			os << "Dead" ;
			break ;
		default:
			break;
	}
	return os ;
}

inline
std::ostream & operator<<(std::ostream & os, const Reaction & react) {
	switch (react) {
		case Reaction::noreact:
			os << "No reaction" ;
			break ;
		case Reaction::loyal:
			os << "Loyal" ;
			break ;
		case Reaction::friendly:
			os << "Friendly" ;
			break ;
		case Reaction::neutral:
			os << "Neutral" ;
			break ;
		case Reaction::unfriendly:
			os << "Unfriendly" ;
			break ;
		case Reaction::hostile:
			os << "Hostile" ;
			break ;
	}
	return os;
}


#endif /* defined(__SpriteFight__CharacterData__) */

