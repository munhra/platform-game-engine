/*
 * PlayerVault.h
 *
 *  Created on: 12/08/2013
 *      Author: munhra
 */

#ifndef PLAYERVAULT_H_
#define PLAYERVAULT_H_

#include "cocos2d.h"

using namespace cocos2d;

class PlayerVault: public CCObject {
public:

	static PlayerVault* create();
	virtual ~PlayerVault();

	// number of coins that the player have to be used on the store
	int coins;
	// multiply the health value by a factor, defailt is 1
	int armorType;
	// number of avaliable traps per level default is 3
	int traps;
	// last level accessed by the player
	int level;
	// score total number of coins collected, the coins
	// used on the store will not be subtracted from this total
	int score;
	// ship parts collected by the player, the total game ship parts
	// the total number of ship parts will be the same as the number of levels
	// this array will have let's say 60 positions, each position will be marked
	// as 1 if the part is collected and 0 if not.
	CCArray *collectedShipParts;

	// powerups that will be consumed by the player, these power ups can be
	// bought on the store or aquired during the game play, the player can have
	// at most 4 active powerups.
	bool magCoins; // valid for one level
	bool invencibility; //valid for one level
	bool skipLevel; // valid for one level
	bool coinsMultiplier; // valid for one level

};

#endif /* PLAYERVAULT_H_ */
