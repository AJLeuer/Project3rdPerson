//
//  AssetFileIO.cpp
//  World
//
//  Created by Adam James Leuer on 4/27/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#include "Project3rdPerson.h"

#include "AssetFileIO.h"

using namespace std ;

vector<AssetFile> * AssetFile::asteroidImageFilenames = new vector<AssetFile> {
	{"Asteroid0_Brown.png", "/Assets/Asteroids/Asteroid0_Brown.png", AssetType::asteroid, Colors::brown},
	{"Asteroid0_Gray.png",  "/Assets/Asteroids/Asteroid0_Gray.png",	 AssetType::asteroid, Colors::brown}
} ;

vector<AssetFile> * AssetFile::backgroundImageFilenames = new vector<AssetFile> {
	{"Space 0.png", "/Assets/Backgrounds/Space 0.png", AssetType::background, Colors::various}
} ;

vector<AssetFile> * AssetFile::explosionImageFilenames = new vector<AssetFile> {
    {"Explosion0_Blue.png",		"/Assets/Explosions/Explosion0_Blue.png",		AssetType::explosion, Colors::blue},
	{"Explosion0_Green.png",	"/Assets/Explosions/Explosion0_Green.png",		AssetType::explosion, Colors::green},
	{"Explosion0_Red.png",		"/Assets/Explosions/Explosion0_Red.png",		AssetType::explosion, Colors::red}
} ;

vector<AssetFile> * AssetFile::powerupImageFilenames = new vector<AssetFile> {

	{"EngineThrust0.png", "/Assets/Powerups/EngineThrust0.png", AssetType::powerup, Colors::transparent},
	{"Bolt_Gold.png",     "/Assets/Powerups/Bolt_Gold.png",     AssetType::powerup, Colors::gold},
	{"Pill_Blue.png",     "/Assets/Powerups/Pill_Blue.png",		AssetType::powerup, Colors::blue},
	{"Pill_Green.png",    "/Assets/Powerups/Pill_Green.png",	AssetType::powerup, Colors::blue},
	{"Shield_Silver.png", "/Assets/Powerups/Shield_Silver.png", AssetType::powerup, Colors::silver}
} ;

vector<AssetFile> * AssetFile::projectileImageFilenames = new vector<AssetFile> {
    {"LaserBlast0_Green.png",   "/Assets/Projectiles/LaserBlast0_Green.png",	AssetType::projectile, Colors::green},
	{"LaserBlast0_Red.png",		"/Assets/Projectiles/LaserBlast0_Red.png",		AssetType::projectile, Colors::red},
	{"LaserBlast1_Blue.png",	"/Assets/Projectiles/LaserBlast1_Blue.png",		AssetType::projectile, Colors::blue},
	{"LaserBlast1_Green.png",	"/Assets/Projectiles/LaserBlast1_Green.png",	AssetType::projectile, Colors::green},
	{"LaserBlast2_Blue.png",	"/Assets/Projectiles/LaserBlast2_Blue.png",		AssetType::projectile, Colors::blue},
	{"LaserBlast2_Red.png",		"/Assets/Projectiles/LaserBlast2_Red.png",		AssetType::projectile, Colors::red}
} ;

vector<AssetFile> * AssetFile::shieldImageFilenames = new vector<AssetFile> {
    {"Shield_Hi.png",			"/Assets/Shields/Shield_Hi.png",			AssetType::shield, Colors::transparent},
	{"Shield_Low.png",			"/Assets/Shields/Shield_Low.png",			AssetType::shield, Colors::transparent},
	{"Shield_Med.png",			"/Assets/Shields/Shield_Med.png",			AssetType::shield, Colors::transparent}
} ;

vector<AssetFile> * AssetFile::playerShipImageFilenames = new vector<AssetFile> {
	{"Saucer_Red.png",  "/Assets/Ships/Saucer_Red.png",  AssetType::playerShip, Colors::red},
	{"Ship0_Blue.png",  "/Assets/Ships/Ship0_Blue.png",  AssetType::playerShip, Colors::blue},
	{"Ship0_Red.png",   "/Assets/Ships/Ship0_Red.png",	 AssetType::playerShip, Colors::red},
	{"Ship1_Green.png", "/Assets/Ships/Ship1_Green.png", AssetType::playerShip, Colors::green},
	{"Ship2_Blue.png",  "/Assets/Ships/Ship2_Blue.png",	 AssetType::playerShip, Colors::blue}

} ;


vector<AssetFile> * AssetFile::enemyShipImageFilenames = new vector<AssetFile> {
	{"Enemy_Ship0_Blue.png",   "/Assets/Ships/Enemy_Ship0_Blue.png",	AssetType::enemyShip, Colors::blue},
	{"Enemy_Ship0_Orange.png", "/Assets/Ships/Enemy_Ship0_Orange.png",  AssetType::enemyShip, Colors::orange},
	{"Enemy_Ship2_Blue.png",   "/Assets/Ships/Enemy_Ship2_Blue.png",	AssetType::enemyShip, Colors::blue},
	{"Enemy_Ship2_Green.png",  "/Assets/Ships/Enemy_Ship2_Green.png",	AssetType::enemyShip, Colors::green}
} ;

vector<AssetFile> * AssetFile::shipDamageImageFilenames = new vector<AssetFile> {
    {"Ship0_Damage0.png", "/Assets/Ship Damage/Ship0_Damage0.png", AssetType::shipDamage, Colors::transparent},
	{"Ship0_Damage1.png", "/Assets/Ship Damage/Ship0_Damage1.png", AssetType::shipDamage, Colors::transparent},
	{"Ship0_Damage2.png", "/Assets/Ship Damage/Ship0_Damage2.png", AssetType::shipDamage, Colors::transparent},
	{"Ship1_Damage1.png", "/Assets/Ship Damage/Ship1_Damage1.png", AssetType::shipDamage, Colors::transparent},
	{"Ship1_Damage2.png", "/Assets/Ship Damage/Ship1_Damage2.png", AssetType::shipDamage, Colors::transparent},
	{"Ship2_Damage0.png", "/Assets/Ship Damage/Ship2_Damage0.png", AssetType::shipDamage, Colors::transparent},
	{"Ship2_Damage1.png", "/Assets/Ship Damage/Ship2_Damage1.png", AssetType::shipDamage, Colors::transparent},
	{"Ship2_Damage2.png", "/Assets/Ship Damage/Ship2_Damage2.png", AssetType::shipDamage, Colors::transparent},
    //todo add the rest
} ;

vector<AssetFile> * AssetFile::UIImageFilenames = new vector<AssetFile> {
	{"Button_Blue.png",		"/Assets/UI/Button_Blue.png",	AssetType::UI, Colors::blue},
	{"Button_Green.png",	"/Assets/UI/Button_Green.png",	AssetType::UI, Colors::green},
	{"Button_Purple.png",	"/Assets/UI/Button_Purple.png",	AssetType::UI, Colors::purple},
	{"Button_Red.png",		"/Assets/UI/Button_Red.png",	AssetType::UI, Colors::red}
} ;


vector< vector<AssetFile> * > * AssetFile::allAssetFiles = new vector< vector<AssetFile> * > {
    asteroidImageFilenames,
	backgroundImageFilenames,
    explosionImageFilenames,
	powerupImageFilenames,
    projectileImageFilenames,
    shieldImageFilenames,
	playerShipImageFilenames,
	enemyShipImageFilenames,
    shipDamageImageFilenames,
	UIImageFilenames
	/* Add any more here */
} ;

AssetFile::AssetFile(const string & existingFilename) {
	
	bool found = false ;
	for (auto i = 0 ; i < allAssetFiles->size() ; i++) {
		for (auto j = 0 ; j < allAssetFiles->at(i)->size() ; j++) {
			if (allAssetFiles->at(i)->at(j).fileName == existingFilename) {
				*this = allAssetFiles->at(i)->at(j) ;
				found = true ;
				break ;
			}
		}
	}
	if (!found) {
		cerr << "No such file found" << endl ;
		throw exception() ;
	}
}

AssetFile::AssetFile(FastRand<int> randm, AssetType type) {

	bool match = false ;
	vector<AssetFile> * files = nullptr ;
	
	for (auto n = 0 ; n < allAssetFiles->size() ; n++) {
		if (allAssetFiles->at(n)->at(0).type == type) {
			files = allAssetFiles->at(n) ;
			match = true ;
		}
	}
	if (match) {
		auto index = randm.nextValue(0, files->size() -1) ;
		*this = files->at(index) ;
	}
	else {
		stringstream ss ;
		ss << "Warning: the random constructor for AssetFile was unable to match the given AssetType. This AssetFile will not be correctly initiialized." << '\n' ;
		DebugOutput << ss.rdbuf() ;
	}
}

AssetFile & AssetFile::operator = (const AssetFile & rhs) {
	if (this != &rhs) {
		this->fileName = rhs.fileName ;
		this->filePath = rhs.filePath ;
		this->type = rhs.type ;
		this->color = rhs.color ;
	}
	return *this ;
}


AssetFile & AssetFile::operator = (const string & str) {
	if (this->fileName != str) {
		*this = AssetFile(str) ;
	}
	return *this ;
}

Texture * AssetFileIO::getTextureFromFilename(Renderer * renderer, const AssetFile & file, AssetType type)  {
	bool noMatch = true ;
	switch (type) {
		case AssetType::asteroid:
		{
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::asteroidImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::asteroidImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
		}
		case AssetType::background:
		{
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::backgroundImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::backgroundImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
		}
        case AssetType::explosion:
        {
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::explosionImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::explosionImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
        }
		case AssetType::powerup:
		{
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::powerupImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::powerupImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
		}
        case AssetType::projectile:
        {
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::projectileImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::projectileImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
        }
        case AssetType::shield:
        {
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::shieldImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::shieldImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
        }
		case AssetType::playerShip:
		{
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::playerShipImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::playerShipImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
		}
		case AssetType::enemyShip:
		{
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::enemyShipImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::enemyShipImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
		}
        case AssetType::shipDamage:
        {
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::shipDamageImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::shipDamageImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
        }
		case AssetType::UI:
		{
			//check the string given to make sure it's a match
			for (auto i = 0 ; i < AssetFile::UIImageFilenames->size() ; i++) {
				if (file.fileName == AssetFile::UIImageFilenames->at(i).fileName) {
					noMatch = false ;
					break ;
				}
			}
			break ;
		}
	}
	//throw an except if it's not
	if (noMatch) {
		cerr << "No file matching given filename \n" ;
		throw exception() ;
	}
	//otherwise, return the requested surface
	Texture * img = 0 ;
	
	{
		/* debug code */
		stringstream ss ;
		ss << "Checking for IMG or SDL errors after IMG_LoadTexture(): " << "<IMG error here" << '\n' ;
		DebugOutput << ss.rdbuf() ;
		/* end debug code */
	}
	
	return img ;
}

AssetFile AssetFileIO::getRandomImageFile(AssetType type) {
	
    FastRand<vector<AssetFile>::size_type> rnd(0, AssetFile::allAssetFiles->size()-1) ; //not used
	
	switch (type) {
		case AssetType::asteroid:
		{
			rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::asteroidImageFilenames->size() -1) ;
			return AssetFile::asteroidImageFilenames->at(rnd()) ;
		}
		case AssetType::background:
		{
			rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::backgroundImageFilenames->size() -1) ;
			return AssetFile::backgroundImageFilenames->at(rnd()) ;
		}
        case AssetType::explosion:
        {
			rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::explosionImageFilenames->size() -1) ;
			return AssetFile::explosionImageFilenames->at(rnd()) ;
        }
		case AssetType::powerup:
		{
			rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::powerupImageFilenames->size() -1) ;
			return AssetFile::powerupImageFilenames->at(rnd()) ;
		}
        case AssetType::projectile:
        {
			rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::projectileImageFilenames->size() -1) ;
			return AssetFile::projectileImageFilenames->at(rnd()) ;
        }
        case AssetType::shield:
        {
			rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::shieldImageFilenames->size() -1) ;
			return AssetFile::shieldImageFilenames->at(rnd()) ;
        }
		case AssetType::playerShip:
		{
			rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::playerShipImageFilenames->size() -1) ;
			return AssetFile::playerShipImageFilenames->at(rnd()) ;
		}
		case AssetType::enemyShip:
		{
			rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::enemyShipImageFilenames->size() -1) ;
			return AssetFile::enemyShipImageFilenames->at(rnd()) ;
		}
        case AssetType::shipDamage:
        {
            rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::shipDamageImageFilenames->size() -1) ;
			return AssetFile::shipDamageImageFilenames->at(rnd()) ;
        }
		case AssetType::UI:
		{
			rnd = FastRand<vector<AssetFile>::size_type>(0, AssetFile::UIImageFilenames->size() -1) ;
			return AssetFile::UIImageFilenames->at(rnd()) ;
		}
	}
}



