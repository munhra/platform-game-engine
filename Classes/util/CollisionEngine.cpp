/*
 * CollisionEngine.cpp
 *
 *  Created on: 06/08/2013
 *      Author: munhra
 */

#include "util/CollisionEngine.h"

CollisionEngine::~CollisionEngine() {
	CCLOG("CollisionEngine engine Destructor");
}

CollisionEngine* CollisionEngine::create() {
	CCLOG("Create Collision Engine");
	CollisionEngine *cengine = new CollisionEngine();
	if (cengine) {
		cengine->autorelease();
		return cengine;
	}
	CC_SAFE_DELETE (cengine);
	return NULL;
}

void CollisionEngine::initCollisionEngine(CCTMXTiledMap *levelMap) {
	CCLog("initCollisionEngine");
	this->map = levelMap;
	this->walls = map->layerNamed("walls");
	CCLog("initCollisionEngine finished");
}

void CollisionEngine::checkForAndResolveCollisions(Trap *trap){

	CCArray *tiles = getSurroundingTilesAtPosition(trap->getPosition(), walls);

		trap->onGround = false;

		for (int tileIndx = 0; tileIndx < tiles->count(); tileIndx++) {

			CCRect pRect = trap->collisionBoundingBox();
			CCDictionary *dic = (CCDictionary *) tiles->objectAtIndex(tileIndx);
			CCXNumericData *tgidData = (CCXNumericData *) dic->objectForKey("gid");
			if (tgidData->getIntValue() > 0) {

				CCXNumericData *rectOrgXData = (CCXNumericData *) dic->objectForKey(
						"x");
				CCXNumericData *rectOrgYData = (CCXNumericData *) dic->objectForKey(
						"y");

				CCRect tileRect = CCRectMake(rectOrgXData->getFloatValue(),
						rectOrgYData->getFloatValue(), map->getTileSize().width,
						map->getTileSize().height);

				// the colision is not detected.
				if (trap->collisionBoundingBox().intersectsRect(tileRect)) {
					CCRect intersection = CCRectIntersection(pRect, tileRect);
					if (tileIndx == 0) {
						//tile is directly below player
						trap->desiredPosition = ccp(trap->desiredPosition.x,
								trap->desiredPosition.y
										+ intersection.size.height);
						trap->velocity = ccp(trap->velocity.x, 0.0);
						trap->onGround = true;
						//this->player->mightAsWellJump = false;
					} else if (tileIndx == 1) {
						//tile is directly above player
						trap->desiredPosition = ccp(trap->desiredPosition.x,
								trap->desiredPosition.y
										- intersection.size.height);
						trap->velocity = ccp(trap->velocity.x, 0.0);
					} else if (tileIndx == 2) {
						//tile is left of player
						trap->desiredPosition = ccp(
								trap->desiredPosition.x + intersection.size.width,
								trap->desiredPosition.y);
						//CCLOG("left collision stopAllActions %f\n",intersection.size.width);
						trap->velocity.x = 0;
					} else if (tileIndx == 3) {
						//tile is right of player
						trap->desiredPosition = ccp(
								trap->desiredPosition.x - intersection.size.width,
								trap->desiredPosition.y);
						trap->velocity.x = 0;
					} else {
						if (intersection.size.width > intersection.size.height) {
							//tile is diagonal, but resolving collision vertially
							trap->velocity = ccp(trap->velocity.x, 0.0); //////Here
							float resolutionHeight;
							if (tileIndx > 5) {
								resolutionHeight = intersection.size.height;
								trap->onGround = true; //////Here
								//this->player->mightAsWellJump = false;
							} else {
								resolutionHeight = -intersection.size.height;
							}
							trap->desiredPosition = ccp(trap->desiredPosition.x,
									trap->desiredPosition.y + resolutionHeight);

						} else {
							float resolutionWidth;
							if (tileIndx == 6 || tileIndx == 4) {
								resolutionWidth = intersection.size.width;
							} else {
								resolutionWidth = -intersection.size.width;
							}
							trap->desiredPosition = ccp(
									trap->desiredPosition.x + resolutionWidth,
									trap->desiredPosition.y);
						}
					}
				}
			}
		}
		trap->setPosition(trap->desiredPosition);

}

void CollisionEngine::checkForAndResolveCollisions(MeeleEnemy *enemy) {

	CCArray *tiles = getSurroundingTilesAtPosition(enemy->getPosition(), walls);

	enemy->onGround = false;

	for (int tileIndx = 0; tileIndx < tiles->count(); tileIndx++) {

		CCRect pRect = enemy->collisionBoundingBox();
		CCDictionary *dic = (CCDictionary *) tiles->objectAtIndex(tileIndx);
		CCXNumericData *tgidData = (CCXNumericData *) dic->objectForKey("gid");
		if (tgidData->getIntValue() > 0) {

			CCXNumericData *rectOrgXData = (CCXNumericData *) dic->objectForKey(
					"x");
			CCXNumericData *rectOrgYData = (CCXNumericData *) dic->objectForKey(
					"y");

			CCRect tileRect = CCRectMake(rectOrgXData->getFloatValue(),
					rectOrgYData->getFloatValue(), map->getTileSize().width,
					map->getTileSize().height);

			// the colision is not detected.
			if (enemy->collisionBoundingBox().intersectsRect(tileRect)) {
				CCRect intersection = CCRectIntersection(pRect, tileRect);
				if (tileIndx == 0) {
					//tile is directly below player
					enemy->desiredPosition = ccp(enemy->desiredPosition.x,
							enemy->desiredPosition.y
									+ intersection.size.height);
					enemy->velocity = ccp(enemy->velocity.x, 0.0);
					enemy->onGround = true;
					//this->player->mightAsWellJump = false;
				} else if (tileIndx == 1) {
					//tile is directly above player
					enemy->desiredPosition = ccp(enemy->desiredPosition.x,
							enemy->desiredPosition.y
									- intersection.size.height);
					enemy->velocity = ccp(enemy->velocity.x, 0.0);
				} else if (tileIndx == 2) {
					//tile is left of player
					enemy->desiredPosition = ccp(
							enemy->desiredPosition.x + intersection.size.width,
							enemy->desiredPosition.y);
					//CCLOG("left collision stopAllActions %f\n",intersection.size.width);
					enemy->backwardMarch = false;
					enemy->velocity.x = 0;
					//p->stopAllActions();
					//p->runAction(p->stopAnimation);
				} else if (tileIndx == 3) {
					//tile is right of player
					enemy->desiredPosition = ccp(
							enemy->desiredPosition.x - intersection.size.width,
							enemy->desiredPosition.y);
					//CCLOG("right collision stopAllActions %f\n",intersection.size.width);
					enemy->forwardMarch = false;
					enemy->velocity.x = 0;
					//p->stopAllActions();
					//p->runAction(p->stopAnimation);
				} else {
					if (intersection.size.width > intersection.size.height) {
						//tile is diagonal, but resolving collision vertially
						enemy->velocity = ccp(enemy->velocity.x, 0.0); //////Here
						float resolutionHeight;
						if (tileIndx > 5) {
							resolutionHeight = intersection.size.height;
							enemy->onGround = true; //////Here
							//this->player->mightAsWellJump = false;
						} else {
							resolutionHeight = -intersection.size.height;
						}
						enemy->desiredPosition = ccp(enemy->desiredPosition.x,
								enemy->desiredPosition.y + resolutionHeight);

					} else {
						float resolutionWidth;
						if (tileIndx == 6 || tileIndx == 4) {
							resolutionWidth = intersection.size.width;
						} else {
							resolutionWidth = -intersection.size.width;
						}
						enemy->desiredPosition = ccp(
								enemy->desiredPosition.x + resolutionWidth,
								enemy->desiredPosition.y);
					}
				}
			}
		}
	}
	enemy->setPosition(enemy->desiredPosition);

}

CCPoint CollisionEngine::tileCoordForPosition(CCPoint position) {

	float x = floor(position.x / this->map->getTileSize().width);
	float levelHeightInPixels = map->getMapSize().height
			* map->getTileSize().height;
	float y = floor(
			(levelHeightInPixels - position.y) / map->getTileSize().height);
	return ccp(x, y);
}

CCRect CollisionEngine::tileRectFromTileCoords(CCPoint tileCoords) {

	float levelHeightInPixels = this->map->getMapSize().height
			* map->getTileSize().height;
	CCPoint origin = ccp(tileCoords.x * map->getTileSize().width,
			levelHeightInPixels
					- ((tileCoords.y + 1) * map->getTileSize().height));
	return CCRectMake(origin.x, origin.y, map->getTileSize().width,
			map->getTileSize().height);
}

CCRect CollisionEngine::CCRectIntersection(CCRect r1, CCRect r2) {

	CCRect intersection;
	intersection = CCRectMake(std::max(r1.getMinX(), r2.getMinX()),
			std::max(r1.getMinY(), r2.getMinY()), 0, 0);
	intersection.size.width = std::min(r1.getMaxX(), r2.getMaxX())
			- intersection.getMinX();
	intersection.size.height = std::min(r1.getMaxY(), r2.getMaxY())
			- intersection.getMinY();

	return intersection;

}

CCArray* CollisionEngine::getSurroundingTilesAtPosition(CCPoint position,
		CCTMXLayer *layer) {

	CCPoint plPos = tileCoordForPosition(position);
	CCArray *gids = CCArray::create();

	for (int i = 0; i < 9; i++) {
		int c = i % 3;
		int r = (int) (i / 3);
		CCPoint tilePos = ccp(plPos.x + (c - 1), plPos.y + (r - 1));
		// fall into a hole
		if (tilePos.y > (map->getMapSize().height - 1)) {

			// kill the enemy here

			//this->gameOver(false);
			return NULL;
		}

		int tgid = layer->tileGIDAt(tilePos);

		CCRect tileRect = tileRectFromTileCoords(tilePos);

		CCDictionary *tileDict = CCDictionary::create();

		CCXNumericData *tilePosData = CCXNumericData::create();
		CCXNumericData *tgidData = CCXNumericData::create();
		CCXNumericData *rectOrgXData = CCXNumericData::create();
		CCXNumericData *rectOrgYData = CCXNumericData::create();

		tilePosData->setPoint(tilePos);
		tgidData->setIntValue(tgid);
		rectOrgXData->setFloatValue(tileRect.origin.x);
		rectOrgYData->setFloatValue(tileRect.origin.y);
		tileDict->setObject(tgidData, "gid");
		tileDict->setObject(rectOrgXData, "x");
		tileDict->setObject(rectOrgYData, "y");
		tileDict->setObject(tilePosData, "tilePos");

		gids->addObject(tileDict);
	}

	gids->removeObjectAtIndex(4);
	gids->insertObject(gids->objectAtIndex(2), 6);
	gids->removeObjectAtIndex(2);
	gids->exchangeObjectAtIndex(4, 6);
	gids->exchangeObjectAtIndex(0, 4);

	return gids;

}
