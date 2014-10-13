//
//  AssetFileIO.h
//  World
//
//  Created by Adam James Leuer on 4/27/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __Util__AssetFileIO__
#define __Util__AssetFileIO__


#include <iostream>
#include <vector>

#include <dirent.h>

#include "Util.hpp"
#include "BoundsCheck.hpp"
#include "GameRandom.hpp"

#include "CharacterData.h"
#include "GameState.hpp"

#include "Configuration.h"

using namespace std ;

enum class AssetType {
	asteroid,
	background,
    explosion,
	powerup,
    projectile,
    shield,
    playerShip,
	enemyShip,
    shipDamage,
	UI
	//what else do we need?
	//add more here
} ;

struct AssetFile {

protected:

	friend class AssetFileIO ;

	string filePath ;

public:

    static vector<AssetFile> * asteroidImageFilenames ;
	static vector<AssetFile> * backgroundImageFilenames ;
    static vector<AssetFile> * explosionImageFilenames ;
	static vector<AssetFile> * powerupImageFilenames ;
    static vector<AssetFile> * projectileImageFilenames ;
    static vector<AssetFile> * shieldImageFilenames ;
	static vector<AssetFile> * playerShipImageFilenames ;
	static vector<AssetFile> * enemyShipImageFilenames ;
    static vector<AssetFile> * shipDamageImageFilenames ;
	static vector<AssetFile> * UIImageFilenames ;

    static vector< vector<AssetFile> * > * allAssetFiles ;

	string fileName ;
	AssetType type ;
	Colors color ;
	//other fields?

    AssetFile() :
        AssetFile(UIImageFilenames->at(0)) {}

	AssetFile(string fileName, string filePath, AssetType type, Colors color) :
		fileName(fileName), filePath(filePath), type(type), color(color) {}

	AssetFile(const AssetFile & other) :
		fileName(other.fileName), filePath(other.filePath), type(other.type), color(other.color) {}

	AssetFile(const string & existingFilename) ;

    AssetFile(FastRand<int> randm, AssetType type) ;

	~AssetFile() {}

	AssetFile & operator = (const AssetFile & rhs) ;

	AssetFile & operator = (const string & str) ;

} ;

/**
 * This class will store the names and directory info of all file assets used in the program.
 * Add the names of any new files added to AssetFileIO.cpp
 */
class AssetFileIO {



public:

	static Texture * getTextureFromFilename(Renderer * renderer, const AssetFile & file, AssetType type) ;
	static string & getImageFilename(vector<AssetFile>::size_type index, AssetType type) ;

	static AssetFile getRandomImageFile(AssetType type) ;

	/**
	 * In addition to finding the AssetType corresponding to the given string,
	 * getAssetTypeFrom() also serves to check that the string, which
	 * will presumably be used to initialize a GameObject or other in-game actor's
	 * texture, is in fact valid. It will throw an exception if it is not.
	 *
	 * @return The AssetType corresponding to imageFilename
	 */
	static AssetType getAssetTypeFromImageFile(const string & imageFilename) ;
};











#endif /* defined(__Util__AssetFileIO__) */
