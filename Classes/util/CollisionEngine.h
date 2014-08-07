/*
 * CollisionEngine.h
 *
 *  Created on: 06/08/2013
 *      Author: munhra
 */

#ifndef COLLISIONENGINE_H_
#define COLLISIONENGINE_H_

#include "cocos2d.h"
#include "enemies/MeeleEnemy.h"
#include "Trap.h"
#include "util/CCXNumericData.h"

using namespace cocos2d;

class CollisionEngine : public CCObject {

public:
	virtual ~CollisionEngine();
	static CollisionEngine* create();
	void initCollisionEngine(CCTMXTiledMap *levelMap);
	void checkForAndResolveCollisions(MeeleEnemy *enemy);
	void checkForAndResolveCollisions(Trap *trap);

private:

	CCTMXTiledMap *map;
	CCTMXLayer *walls;

	CCArray* getSurroundingTilesAtPosition(CCPoint position, CCTMXLayer *layer);
	CCRect CCRectIntersection(CCRect r1, CCRect r2);
	CCPoint tileCoordForPosition(CCPoint position);
	CCRect tileRectFromTileCoords(CCPoint tileCoords);



};

#endif /* COLLISIONENGINE_H_ */
