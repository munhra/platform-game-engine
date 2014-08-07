/*
 * LoadLevelEnemies.h
 *
 *  Created on: 30/08/2013
 *      Author: munhra
 */

#ifndef LOADLEVELENEMIES_H_
#define LOADLEVELENEMIES_H_

#include "util/SpecialTiles.h"
#include "util/PersistenceAux.h"
#include "enemies/MeeleEnemy.h"
#include "Player.h"
#include "cocos2d.h"

using namespace cocos2d;

class LoadLevelEnemies {
public:
	LoadLevelEnemies();
	virtual ~LoadLevelEnemies();
	static CCArray* getEnemiesListFromLayer(CCTMXTiledMap *tilemap,Player *player);

};

#endif /* LOADLEVELENEMIES_H_ */
