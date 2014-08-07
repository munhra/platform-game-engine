/*
 * LoadLevelEnemies.cpp
 *
 *  Created on: 30/08/2013
 *      Author: munhra
 */

#include "LoadLevelEnemies.h"
#include "MeeleEnemy.h"

using namespace cocos2d;

LoadLevelEnemies::LoadLevelEnemies() {
	// TODO Auto-generated constructor stub

}

LoadLevelEnemies::~LoadLevelEnemies() {
	// TODO Auto-generated destructor stub
}

/**
 * Returns an array of enemies (Meele Enemies) with all the animations already defined by this loader,
 * this array will be used on the game play scene to draw the enemies and to handle the update
 */

CCArray* LoadLevelEnemies::getEnemiesListFromLayer(CCTMXTiledMap *tilemap,
		Player *player) {

	CCTMXLayer* layer = tilemap->layerNamed("enemies");

	CCSize layersize = layer->getLayerSize();

	CCLOG("%s \n", "setEnemiesTilesInformation");
	CCArray *enemieArray = CCArray::create();
	CCDictionary* enemiesDictionary = PersistenceAux::getEnemyData();
	CCLOG("Enemy data loaded");
	for (int x = 0; x < layersize.width; x++) {
		for (int y = 0; y < layersize.height; y++) {
			unsigned int tmpgid = layer->tileGIDAt(ccp(x, y));
			if (tmpgid != 0) {
				CCSprite* tile = layer->tileAt(ccp(x, y));
				CCRect box = tile->boundingBox();
				CCPoint boxsize = ccp(box.size.width, box.size.height);
				CCPoint tilePosition = ccpAdd(tile->getPosition(),
						ccpMult(boxsize, 0.5));
				layer->removeTileAt(ccp(x, y));

				// create the enemy directly
				CCDictionary* tileProperties = tilemap->propertiesForGID(
						tmpgid);
				CCLOG("%s \n", "dictionary for enemies properties");
				CCString* enemyName = (CCString*) tileProperties->objectForKey(
						"name");
				CCLOG("Enemy name %s \n", enemyName->getCString());
				CCDictionary* enemyProperties =
						(CCDictionary *) enemiesDictionary->objectForKey(
								enemyName->getCString());
				CCLOG("Enemy prop. Dictionary size %d \n",
						enemyProperties->count());
				CCLOG("Enemy Position x %d \n", tilePosition.x);

				CCLOG("************** PLIST ****************** \n");
				CCLOG("SPEED %s",
						((CCString*) enemyProperties->objectForKey("speed"))->getCString());
				CCLOG("JUMPFORCE %s",
						((CCString*) enemyProperties->objectForKey("jump"))->getCString());
				CCLOG("SIGHT %s",
						((CCString*) enemyProperties->objectForKey("sight"))->getCString());
				CCLOG("DIFICULT %s",
						((CCString*) enemyProperties->objectForKey("dificult"))->getCString());
				CCLOG("DEFAULT IMAGE %s",
						((CCString*) enemyProperties->objectForKey(
								"defaultimage"))->getCString());
				CCLOG("************** PLIST END ****************** \n");

				MeeleEnemy* enemy = MeeleEnemy::create(
						(CCString*) enemyProperties->objectForKey(
								"defaultimage"),
						(CCString*) enemyProperties->objectForKey("dificult"),
						(CCString*) enemyProperties->objectForKey("jump"),
						(CCString*) enemyProperties->objectForKey("sight"),
						(CCString*) enemyProperties->objectForKey("speed"),
						tilePosition, enemyName,
						(CCString*) enemyProperties->objectForKey("damage")
				);
				CCLOG("%s \n", "Initializing enemies");
				enemy->initMeeleEnemy(player);
				CCLOG("%s \n", "Add enemies to enemy array");
				enemieArray->addObject(enemy);
			}
		}
	}
	return enemieArray;
}


