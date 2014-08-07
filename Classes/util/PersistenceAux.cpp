/*
 * PersistenceAux.cpp
 *
 *  Created on: 12/08/2013
 *      Author: munhra
 */

#include "PersistenceAux.h"
#include "stdio.h"
#include "stdlib.h"

CCDictionary* PersistenceAux::staticGameData;

PersistenceAux::~PersistenceAux() {
	CCLOG("Destruct PersistenceAux");
}

/*
 * Returns all the static game data, regarding to enemies, ship parts, animated tiles
 */
CCDictionary* PersistenceAux::getStaticGameData() {
	return PersistenceAux::staticGameData;
}

/*
 * Returns only the static game data regarding to the enemies
 */
CCDictionary* PersistenceAux::getEnemyData() {
	CCLOG("Dictionary size %d \n", PersistenceAux::staticGameData->count());
	return (CCDictionary *) PersistenceAux::staticGameData->objectForKey(
			"enemies");
}

/*
 * Load the static game data from the plist file to dictionary
 */
void PersistenceAux::loadStaticGameData() {
	CCLOG("loadStaticGameData \n");
	PersistenceAux::staticGameData = CCDictionary::createWithContentsOfFile(
			"data/gameStaticData.plist");
	CCLOG("Dictionary size %d \n", PersistenceAux::staticGameData->count());
	PersistenceAux::staticGameData->retain();
}

/*
 * Load the game save data from the disk to player vault object
 */
PlayerVault* PersistenceAux::loadGameData() {

	PlayerVault* vault = PlayerVault::create();

	if (firstRun()) {
		CCLOG("PersistenceAux FirstRun");
		// default values for the first run
		vault->level = 1;
		vault->armorType = 1;
		vault->coins = 0;
		vault->traps = 3;
		vault->score = 0;
		vault->collectedShipParts = CCArray::createWithCapacity(60);

		for (int ii = 0; ii < 60; ii++) {
			vault->collectedShipParts->addObject(CCInteger::create(0));
		}

	} else {
		// values that were previous saved on a last game
		CCLOG("PersistenceAux not FirstRun");
		vault->level = CCUserDefault::sharedUserDefault()->getIntegerForKey(
				"level");
		vault->armorType = CCUserDefault::sharedUserDefault()->getIntegerForKey(
				"armorType");
		vault->coins = CCUserDefault::sharedUserDefault()->getIntegerForKey(
				"coins");
		vault->traps = CCUserDefault::sharedUserDefault()->getIntegerForKey(
				"traps");
		vault->score = CCUserDefault::sharedUserDefault()->getIntegerForKey(
				"score");

		vault->collectedShipParts = CCArray::createWithCapacity(60);

		for (int ii = 0; ii < 60; ii++) {
			CCString* partname = new CCString();
			partname->initWithFormat("level_ship_part%d", ii);

			vault->collectedShipParts->addObject(
					CCInteger::create(
							CCUserDefault::sharedUserDefault()->getIntegerForKey(
									partname->getCString())));

		}

	}

	return vault;
}

/*
 * Save the game data from a player vault object to the file system
 */
void PersistenceAux::saveGameData(PlayerVault* gamedata, bool shippart) {

	CCUserDefault::sharedUserDefault()->setIntegerForKey("level",
			gamedata->level);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("coins",
			gamedata->coins);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("armorType",
			gamedata->armorType);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("traps",
			gamedata->traps);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("score",
			gamedata->score);

	if (shippart == true) {
		//save the shippart ...
		CCString* partname = new CCString();
		partname->initWithFormat("level_ship_part%d", gamedata->level);
		CCUserDefault::sharedUserDefault()->setIntegerForKey(partname->getCString(),1);

	}
	CCLOG("Ship Parts Saved");

}

bool PersistenceAux::firstRun() {
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey("userdata")) {
		//this is the first run as there is no userdata, so set
		//the userdata to true indicating that the game has been played once
		CCUserDefault::sharedUserDefault()->setBoolForKey("userdata", true);
		return true;
	} else {
		// this is not the first run as there is data stored.
		return false;
	}

}

