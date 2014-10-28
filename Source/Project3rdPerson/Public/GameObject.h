//
//  GameObject.h
//  World
//
//  Created by Adam James Leuer on 3/11/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __SpriteFight__GameObject__
#define __SpriteFight__GameObject__

#include "Project3rdPerson.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <cmath>

#include "Debug.h"
#include "Util.hpp"
#include "Util2.h"
#include "Size.hpp"
#include "GameRandom.hpp"
#include "Timer.hpp"
#include "AssetFileIO.h"

#include "GraphicsData.hpp"

#include "ForwardDecl.h"
#include "Position.hpp"
#include "BoundsCheck.hpp"
#include "GameMap.hpp"
#include "GameState.hpp"
#include "GameInterface.h"

#include "Configuration.h"
#include "Input.hpp"

using namespace::std ;

typedef std::pair<Position<float>, chrono::nanoseconds> PastPositionAndTimeDifferential ;

/**
 * @brief The base class from which all other classes in the world
 *		  will inherit. This class will handle the assignment of a unique ID to each GameObject.
 *
 * @see Character
 */
class GameObject : public GameInterface {


private:


	static unsigned IDs ;

	static bool map_is_init ;

	/**
	 * Pointers to all extant GameObjects. WorldController will actually inialize this during its init(), by simply syncing
	 * allGameObjects to the same vector pointed by WorldController::gameObjects. In practice the two should almost always be the same
	 */
	static vector<GameObject*> * allGameObjects ;

	bool markedForDeletion = false ;

	/**
	 * @brief Handles thread starting duties. Should always be called by the function that calls
	 *        the threaded function. Ended by calling endThreading()
	 *
	 * @param wait Whether to wait on this thread to finish
	 * @param functionPointer Pointer to the instance member function to run on a thread.
	 */
	void startThreading(void (GameObject::*functionPointer)(), bool wait) ;

	/**
	 * @brief Handles thread duties. In some case will be called by the threaded function once it has completed,
	 *        don't call if joinThreads() will be called.
	 *
	 * @param join whether to call join() on this thread first
	 */
	void endThreading(bool join) ;

	friend class WorldController ;
	friend struct GameState ;

protected:

	int ID ;

    GraphicsData<float, int> * graphicsData ;

    bool onMap = false ;

	//Vectr<float> vectr ;

	const GameObject * ally = nullptr ;

    void update() ;

	/**
	 * Holds pointers to GameObjects like allGameObjects, but is 2D and the placement of each GameObject in map
	 * corresponds to the x and y coordinate of its Position. Is synced with WorldController's map.
	 */
	static GameMap<GameObject> * map ;

	static FastRand<int> goRand ;

	static void checkForMarkedDeletions() ;

	/**
	 * Erases the GameObject pointer matching the given ID from the allGameObjects container.
	 */
	static void eraseByID(unsigned ID) ;

    friend class Weapon ;

public:

	/**
	 * @note Pointers to all extant GameObjects. WorldController will actually inialize this during its init(), by simply syncing
	 * allGameObjects to the same vector pointed by WorldController::gameObjects. In practice the two should almost always be the same.
	 * Only classes that *absolutely* must have write access to allGameObjects should it access via this method. All others should call
	 * GameState::getGameObjects().
	 */
	static vector<GameObject*> * & getAllGameObjects() { return GameObject::allGameObjects ; }


    /**
     * @return The current map of GameObjects
     */
	static const GameMap<GameObject> * getMap() { return GameObject::map ; }

    static void allDoDefaultBehaviors(const TimeFlow & tf) ;


	/**
	 * Creates a new GameObject
	 */
	GameObject() ;

	/**
	 * Copy constructor for GameObject. The new instance has its own unique ID.
	 *
	 * @param other The GameObject to be copied
	 */
	GameObject(const GameObject & other) ;

	/**
	 * Move constructor for GameObject. The new instance the same ID.
	 *
	 * @param other The GameObject to be moved
	 */
	GameObject(GameObject && other) ;


	/**
	 * Creates an object with the given UTF-8 symbol (preferably just
	 * one character) as its icon
	 *
	 * @param imageFile The file to be used as the Texture for this GameObject
     * @param pos This GameObject's Position<float>
	 */
	GameObject(const AssetFile & imageFile, float sizeModifier, const Position<float> & pos, const Angle rotation, bool visible, SafeBoolean monitorVelocity, bool boundsChecking) ;

    /**
	 * Constructs a randomized GameObject. The client has to option to simply leave the argument randSeed as
	 * 0, in which case the constructor will generate its own random number.
	 *
	 * @param rand A seed to initialize the random number generator
	 */
	GameObject(FastRand<int> & rand, AssetType type, bool visible) ; //increase fastRand limit (currently 1) to maximum number
																								   //of values represented by enum class FileType

	/**
	 * Destructor for GameObject
	 */
	virtual ~GameObject() ;

	/**
	 * Assignment operator overload (copy) for GameObject. The object copied
	 * to will have its own unique ID.
	 *
	 * @param rhs The right hand side argument (which will be copied)
	 */
	virtual GameObject & operator=(const GameObject & rhs) ;

	/**
	 * Assignment operator overload (move) for GameObject. The object copied
	 * to will have the same ID.
	 *
	 * @param rhs The right hand side argument (which will be moved)
	 */
	virtual GameObject & operator=(GameObject && rhs) ;


	/**
	 * Overloads operator() for GameObject. Possibly will be used to
	 * call notify(). TBD.
	 */
	virtual void operator()() ;


	/**
	 * Overloads the overload of operator(). For the most part the details of
	 * this function will be handled by inheriting classes.
	 *
	 * @param other A reference to another GameObject
	 */
	virtual void operator()(GameObject * other) ;

	/**
	 * Overloads the overload of operator(). For the most part the details of
	 * this function will be handled by inheriting classes.
	 *
	 * @param other A reference to another GameObject
     * @return whether this GameObject ID is equal to ID of other
	 */
	bool operator==(GameObject & other) const ;

	/**
	 * Overloads the overload of operator(). For the most part the details of
	 * this function will be handled by inheriting classes.
	 *
	 * @param other A reference to another GameObject
	 * @return whether this GameObject ID is equal to ID of other
	 */
	bool operator==(const GameObject & other) const ;

    void markForDeletion(bool mark = true) { markedForDeletion = mark ; }

    bool isMarkedForDeletion() { return markedForDeletion  ;  }

	/**
	 * @return this ID
	 */
	unsigned getID() { return this->ID ; }

	/**
	 * Every sub-type of GameObject should implement this to perform some
	 * function of their choosing. Will typically be called by other classes with a
	 * reference to this GameObject.
	 */
	virtual void notify() ;

	/**
	 * Writes a formatted text description of this GameObject into the desired output stream
	 */
	virtual void textDescription(ostream * writeTo) const ;

    void placeOnMap() ;

    void moveOnMap(const Position<float> * toNewLoc) ;

    void eraseFromMap() ;

	/**
	 * Moves this GameObject to the Position<float> moveTo. All other movement
	 * functions should call this.
	 *
	 * @param to The Position<float> where this GameObject is to move
	 */
	void moveTo(Position<float> * to) ;

	/**
	 * Moves this GameObject to the Position<float> moveTo. All other movement
	 * functions should call this.
	 *
	 * @param to The Position<float> where this GameObject is to move
	 */
	void moveTo(Position<float> to) ;

	void moveTo(float x, float y, float z) { moveTo(Position<float>(x, y)) ; }

    void moveX(float x) ;
    void moveY(float y) ;

	virtual void moveUp() ;
	virtual void moveDown() ;
	virtual void moveRight();
	virtual void moveLeft();

    void orientationDependentLeftRightMove() ;
    void orientationDependentRightLeftMove() ;

    virtual void rotateClockwise() override { graphicsData->rotateClockwise() ; }
    virtual void rotateCounterClockwise() override { graphicsData->rotateCounterClockwise() ; } ;

    virtual void moveRandomDirection() ;

	void jump() ;

    /**
	 * Moves this GameObject by changing its Position<float> x and y coordinates according to the
	 * Vectr of its last move
	 *
	 */
    void move() ;

    size_t archivedPositionsCount() { Pos2<float> * pos = (Pos2<float> *)graphicsData->getRawMutablePosition() ; return pos->archivedPositionsCount() ; }

	PastPositionAndTimeDifferential getReverseMove() ;

	/**
	 * Moves this GameObject by changing its Position<float> x and y coordinates according to the
	 * Vectr of its last move
	 *
	 * @note If graphicsData.getBoundsCheck() == nullptr, move() will skip bounds checking
	 */
	void move(float distanceModifier) ;

	/**
	 * Moves this GameObject by changing its Position<float> x and y coordinates according to the given
	 * Vectr
	 *
	 * @note If bc = nullptr, move() will skip bounds checking
	 *
	 * @param newDirection The new vector specifying the direction of travel
	 */
	virtual void move(Vectr<float> & direction, float distanceModifier = defaultMoveDistance) ;

    void rotateDiff(const Angle & orientation) { graphicsData->setVectorAndOrientation(orientation) ; }

	/**
	 * Similar to move(), but instead of stopping when reaching the bounds of the gamespace,
	 * the GameObject reverses course
	 */
	void wander() ;

	/**
	 * Each GameObject can implement this to enable its default behaviors to run
	 * on a loop on a separate thread
	 */
	virtual void doDefaultBehavior(bool initialCall = false) ;

	virtual void aiBehaviors() ;

	virtual void attack(GameObject * enemy) ;

	virtual void findNearbyAlly(int searchDistanceX, int searchDistanceY) ;

	virtual void allyWith(const GameObject *) ;

	/**
	 * @return This GameObject's Colors
	 */
	Colors getColor() const { return graphicsData->getAssetFile()->color ; }

	/**
	 * @return This GameObject's Position<float>
	 */
	const Position<float> * getPosition() const { return this->graphicsData->getRawMutablePosition() ; }

	/**
	 * @return This GameObject's Position history (Pos2)
	 */
	const Pos2<float> * getPositionHistory() const { return (Pos2<float> *)graphicsData->getRawMutablePosition()  ; } //todo uncomment and fix

	/**
	 * @return This GameObject's vector in 3-D space
	 */
	const Vectr<float> * getVector() { return graphicsData->getVector() ; }

    /**
     * @note Use only when no other options are available
     */
    Position<float> * getRawMutablePosition() { return this->graphicsData->getRawMutablePosition() ; }

	/**
	 * @note Use only when no other options are available
	 */
	Vectr<float> * getRawMutableVector() { return graphicsData->getRawMutableVector() ; }

	/**
	 * Sets this GameObject's sprite to the specified file
	 *
	 * @param imageFileName The filename and path of the sprite image
	 */
	void setImageFile(string imageFileName) ;

	//void setTexture(Texture * texture) { this->graphicsData.setTexture(texture) ; }

	//void setSize(int w, int h) { size.setWidth(w) ; size.setHeight(h) ; }

	/**
	 * @return This GameObject's textureImageFile, i.e. the file path of its texture (usually in png format)
	 */
	const AssetFile * getImageFile() const ;

	/**
	 * @return This GameObject's texture, or nullptr if this isVisible() is false
	 */
	Texture * getTexture() const ;

	const Area<int> * getSize() const { return graphicsData->getSizePtr() ; }

	/**
	 * @return This GameObject's asset type
	 */
	AssetType getType() const { return graphicsData->getAssetFile()->type ; }

	void setVisibility(bool visible) { this->graphicsData->setVisibility(visible) ; }
	bool isVisible() const { return this->graphicsData->isVisible() ; }

    bool overBounds() ;

	/**
	 * Turns this GameObject invisible for nano nanoseconds
	 *
	 * @param nano The length of time to remain invisible
	 */
	void timedTurnInvisible(std::chrono::nanoseconds nano) ;

	/**
	 * Override the << output stream operator
	 */
	friend ostream & operator<<(std::ostream & os, const GameObject & gameObj) ;

	/**
	 * Similar to textDescription(), but returns a new string instead of writing to one passed to it
	 */
	string toString() const ;

	/**
	 * @note Provides no functionality. Implemented only to fullfill the requirements of GameInterface
	 * interface. See PlayerCharacter::fire() for a functional implementation
	 */
	virtual void fire() ;


} ;



#endif /* defined(__SpriteFight__GameObject__) */
