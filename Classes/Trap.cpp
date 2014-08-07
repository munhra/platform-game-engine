/*
 * Trap.cpp
 *
 *  Created on: 16/10/2013
 *      Author: munhra
 */

#include "Trap.h"

using namespace cocos2d;

Trap::~Trap() {
	CCLOG("Trap destructor \n");
}

Trap* Trap::create() {

	CCLOG("Creating the Trap \n");

	CCString* cageFrm1 = CCString::create("cage1.png");

	Trap *trap = new Trap();
	if (trap && trap->initWithSpriteFrameName(cageFrm1->getCString())) {
		// Set to autorelease
		trap->autorelease();
		return trap;
	}
	CC_SAFE_DELETE(trap);
	return NULL;
}

void Trap::initTrap(CCPoint initPosition) {
	CCLOG("initTrap \n");
	defineAnimations();
	pickable = false;
	this->setPosition(initPosition);
	this->scheduleOnce(schedule_selector(Trap::pickDelay), 1.0);
}

void Trap::pickDelay(float dt){
	CCLOG("Free to be picked");
	pickable = true;
}

void Trap::update(float dt) {
	//CCLOG("update \n");

	CCPoint gravity = ccp(0.0, -500.0);
	CCPoint gravityStep = ccpMult(gravity, dt);

	velocity = ccpAdd(velocity, gravityStep);
	velocity = ccp(velocity.x * 0.80, velocity.y); //2

	CCPoint stepVelocity = ccpMult(velocity, dt);
	desiredPosition = ccpAdd(this->getPosition(), stepVelocity);
}

void Trap::onExit() {
	CCLOG("onExit \n");
	if (defaultAnimation) {
		CCLOG("onExit trap defaultanimation recCount %d",
				defaultAnimation->retainCount());
		defaultAnimation->release();
	}
}

void Trap::defineAnimations() {
	CCLOG("defineAnimations \n");

	CCArray *defaultAnimFrames = CCArray::create();
	for (int i = 1; i <= 3; i++) {
		CCLOG("Creating framename with name cage");
		CCString* framename = CCString::createWithFormat("cage%d.png", i);
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
}

CCRect Trap::collisionBoundingBox() {
	CCPoint diff = ccpSub(desiredPosition, this->getPosition());
	CCRect returnBoundingBox = this->boundingBox();
	returnBoundingBox.origin.x = returnBoundingBox.origin.x + diff.x;
	returnBoundingBox.origin.y = returnBoundingBox.origin.y + diff.y;
	return returnBoundingBox;
}

