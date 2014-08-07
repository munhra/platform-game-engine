/*
 * AnimatedTile.h
 *
 *  Created on: 04/09/2013
 *      Author: munhra
 */

#ifndef ANIMATEDTILE_H_
#define ANIMATEDTILE_H_

#include "cocos2d.h"
#include "scenes/GameLevelLayer.h"

using namespace cocos2d;

class AnimatedTile: public CCSprite {
public:
	virtual ~AnimatedTile();

	CCAction *defaultAnimation;
	CCAction *collisionAnimation;
	CCSequence *collisionSequence;
	CCTMXTiledMap* map;
	CCString* name;
	int animtype;

	bool hasCollision;
	static AnimatedTile* create(CCString* tilename);
	void initAnimatedTile(CCPoint initposition, const char* name,
			bool controlCollision, int tileanimtype, CCTMXTiledMap* tilemap);
	void doCollisionWithPlayer();
	virtual void onExit();

private:
	void defineAnimations(const char* name);
	void endCollisionCallBack(CCNode* sender);

};

#endif /* ANIMATEDTILE_H_ */
