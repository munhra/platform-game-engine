/*
 * AnimatedTile.cpp
 *
 *  Created on: 04/09/2013
 *      Author: munhra
 */

#include "AnimatedTile.h"

AnimatedTile::~AnimatedTile() {
	CCLOG("Calling animated tile destructor !");
}

void AnimatedTile::defineAnimations(const char* name) {
	// define default tile animation
	CCArray *defaultAnimFrames = CCArray::create();
	for (int i = 1; i <= 4; i++) {
		CCLOG("Creating framename with name %s\n", name);
		CCString* framename = CCString::createWithFormat("%s%d.png", name, i);
		CCLOG("Frame name %s", framename->getCString());

		defaultAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						framename->getCString()));
	}

	CCAnimation *defaultAnim = CCAnimation::createWithSpriteFrames(
			defaultAnimFrames, 0.09f);
	defaultAnim->setRestoreOriginalFrame(true);
	defaultAnimation = CCRepeatForever::create(CCAnimate::create(defaultAnim));
	defaultAnimation->retain();

	this->runAction(this->defaultAnimation);

	CCLog("Define Default Animation");

	//Colision animation if it has collision
	if (hasCollision == true) {

		CCArray *collisiontAnimFrames = CCArray::create();
		for (int i = 1; i <= 4; i++) {
			CCLOG("Creating collision framename with name %s\n", name);
			CCString* framename = CCString::createWithFormat("%s_collision%d.png", name, i);
			CCLOG("Collision Frame name %s", framename->getCString());

			collisiontAnimFrames->addObject(
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
							framename->getCString()));
		}

		CCAnimation *collisionAnim = CCAnimation::createWithSpriteFrames(
				collisiontAnimFrames, 0.09f);
		collisionAnim->setRestoreOriginalFrame(true);

		CCFiniteTimeAction *collisionFiniteAnim = CCRepeat::create(
				CCAnimate::create(collisionAnim), 1);

		CCFiniteTimeAction *endCollisionCallBack = CCCallFuncN::create(this,
				callfuncN_selector(AnimatedTile::endCollisionCallBack));

		collisionSequence = CCSequence::create(collisionFiniteAnim,
				endCollisionCallBack, NULL);

		collisionSequence->retain();
	}
}

AnimatedTile* AnimatedTile::create(CCString* tilename) {
	CCLOG("Creating the animated tile %s\n", tilename->getCString());
	CCString* tileframe = CCString::createWithFormat("%s%d.png", tilename->getCString(), 1);
	CCLOG("Creating the animated frame %s\n", tileframe->getCString());
	AnimatedTile *animatedTile = new AnimatedTile();
	if (animatedTile
			&& animatedTile->initWithSpriteFrameName(tileframe->getCString())) {
		animatedTile->autorelease();
		return animatedTile;
	}
	CC_SAFE_DELETE(animatedTile);
	return NULL;
}

void AnimatedTile::initAnimatedTile(CCPoint initposition, const char* name,
		bool controlCollision, int tileanimtype, CCTMXTiledMap* tilemap) {
	this->map = tilemap;
	this->animtype = tileanimtype;
	this->name = CCString::create(name);
	CCLOG("init the animated tile \n");
	this->hasCollision = controlCollision;
	this->setPosition(initposition);
	CCLOG("define animations \n");
	this->defineAnimations(name);

}

void AnimatedTile::doCollisionWithPlayer() {
	//CCLOG("doCollisionWithPlayer");
	if (collisionSequence) {
		if (hasCollision == true) {
			//CCLOG("Play collision sequence");
			this->stopAllActions();
			this->runAction(this->collisionSequence);
		} else {
			//CCLOG("This tile has no collision properties");
		}
	}
}

void AnimatedTile::endCollisionCallBack(CCNode* sender) {
	CCLOG("endCollisionCallBack");
	map->removeChild(sender, true);
}

void AnimatedTile::onExit() {
	CCLOG("animatedTile onExit");

	if (defaultAnimation) {
		CCLOG("onExit AnimatedTile defaultanimation recCount %d",
				defaultAnimation->retainCount());
		defaultAnimation->release();
	}

	if (collisionSequence) {
		CCLOG("onExit Collision Sequence recCount %d",
				collisionSequence->retainCount());
		collisionSequence->release();
	}

}

