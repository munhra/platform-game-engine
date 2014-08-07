/*
 * PersistenceAux.h
 *
 *  Created on: 12/08/2013
 *      Author: munhra
 */

#ifndef PERSISTENCEAUX_H_
#define PERSISTENCEAUX_H_

#include "cocos2d.h"
#include "PlayerVault.h"

using namespace cocos2d;

class PersistenceAux {

public:

	virtual ~PersistenceAux();

	static CCDictionary *staticGameData;
	static PlayerVault* loadGameData();
	static bool firstRun();
	static void saveGameData(PlayerVault* gamedata, bool shippart);
	static CCDictionary* getStaticGameData();
	static CCDictionary* getEnemyData();
	static void loadStaticGameData();

private:

};

#endif /* PERSISTENCEAUX_H_ */
