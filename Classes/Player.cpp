/*
 * Player.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: vntraal
 */

#include "Player.h"

const float GRAVITY_Y = -1500.0;
const float MOVE_FORCE = 2500.0;
const float JUMP_FORCE = 850.0; // old 700
const float JUMP_CUT_OFF = 1400.0;
const float VELOCITY_FACTOR = 0.90; // old 0.90

Player::~Player() {
	CCLOG("Player Destructor");
	walkAnimation->release();
	stopAnimation->release();
	jumpAnimation->release();

}

Player* Player::create(const char *filename) {
	Player *p = new Player();
	if (p && p->initWithFile(filename)) {
		// Set to autorelease
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return NULL;
}

void Player::initPlayer(CCPoint initPoint) {
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
			"sprites/playerSheet.plist");
	onJump == false;
	velocity = ccp(0.0, 0.0);
	stop = false;
	activeShoots = CCArray::create();
	defineAnimations();
	CCLog("initPlayer");
	this->setPosition(initPoint);
	bool attackRecovery = false;
	this->health = 100;
	//this->setScaleX(3.22);
	//this->setScaleY(2.87);
	//this->setScale(1.333);
}

void Player::defineAnimations() {

	const char *name = "walk";
	char frameNameBuf[32] = { 0 };

	//walk animation
	CCArray *walkAnimFrames = CCArray::create();
	for (int i = 1; i <= 3; i++) {
		sprintf(frameNameBuf, "%s%d.png", name, i);
		walkAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						frameNameBuf));
	}

	CCAnimation *walkAnim = CCAnimation::createWithSpriteFrames(walkAnimFrames,
			0.09);
	walkAnimation = CCRepeatForever::create(CCAnimate::create(walkAnim));
	walkAnimation->retain();

	//stop animation
	CCArray *stopAnimFrames = CCArray::create();
	for (int i = 1; i <= 1; i++) {
		sprintf(frameNameBuf, "%s%d.png", name, i);
		stopAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						frameNameBuf));
	}

	CCAnimation *stopAnim = CCAnimation::createWithSpriteFrames(stopAnimFrames,
			0.15f);
	stopAnimation = CCRepeatForever::create(CCAnimate::create(stopAnim));
	stopAnimation->retain();

	//jump animation
	name = "jump";

	CCArray *jumpAnimFrames = CCArray::create();
	for (int i = 1; i <= 3; i++) {
		sprintf(frameNameBuf, "%s%d.png", name, i);
		jumpAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						frameNameBuf));
	}

	CCAnimation *jumpAnim = CCAnimation::createWithSpriteFrames(jumpAnimFrames,
			0.09f);
	jumpAnimation = CCRepeatForever::create(CCAnimate::create(jumpAnim));
	jumpAnimation->retain();
}

CCRect Player::collisionBoundingBox() {
	CCPoint diff = ccpSub(desiredPosition, this->getPosition());
	CCRect returnBoundingBox = this->boundingBox();
	returnBoundingBox.origin.x = returnBoundingBox.origin.x + diff.x;
	returnBoundingBox.origin.y = returnBoundingBox.origin.y + diff.y;
	return returnBoundingBox;
}

CCSprite* Player::fireLaser(float deltaXView) {
	//CCLog("Future Implementation");
	return NULL;
}

void Player::onExit() {
	CCLOG("Player on exit retain count %d", this->retainCount());
}

void Player::update(float dt) {
	CCPoint gravity = ccp(0.0, GRAVITY_Y);
	CCPoint gravityStep = ccpMult(gravity, dt);
	CCPoint forwardMove = ccp(MOVE_FORCE, 0.0);
	CCPoint backwardMove = ccp(-MOVE_FORCE, 0.0);
	CCPoint forwardStep = ccpMult(forwardMove, dt); //1
	CCPoint backwardStep = ccpMult(backwardMove, dt);

	velocity = ccpAdd(velocity, gravityStep);
	if (stop == true) {
		velocity = ccp(0, velocity.y); //2
	} else {
		velocity = ccp(velocity.x * VELOCITY_FACTOR, velocity.y); //2
	}

	CCPoint jumpForce = ccp(0.0, JUMP_FORCE);
	// The chunk of code below check if the player is jumping
	if (mightAsWellJump && onGround) {
		//jumping condition

		if (onJump == false) {
			//CCLog("onJump false %f\n", velocity.y);
			onJump = true;
			velocity = ccpAdd(velocity, jumpForce);
		} else {
			//CCLog("onJump true %f\n", velocity.y);
			onJump = false;
			mightAsWellJump = false;
			backwardMarch = false;
			velocity.x = 0;
			this->stopAllActions();
			this->runAction(this->stopAnimation);

		}

	} else if (!mightAsWellJump && velocity.y > JUMP_CUT_OFF) {
		CCLog("******* Jump cutoff ! *******");
		velocity = ccp(velocity.x, JUMP_CUT_OFF);
	}

	if (backwardMarch) {
		velocity = ccpAdd(velocity, backwardStep);
	}

	if (forwardMarch) {
		velocity = ccpAdd(velocity, forwardStep);
	}

	// limits the bondary of the speed
	CCPoint stepVelocity = ccpMult(velocity, dt);
	desiredPosition = ccpAdd(this->getPosition(), stepVelocity);

}

void Player::receiveAttackDelay(float dt) {
	this->attackRecovery = false;
}

void Player::receiveAttack(int damagePoints) {
	//player receives an attack from enemy
	//lauch a schedule to avoid another attack sequence
	if (this->attackRecovery == false) {
		this->health = this->health - damagePoints;
		this->scheduleOnce(schedule_selector(Player::receiveAttackDelay), 1);
		this->attackRecovery = true;
		if (this->health < 0) {
			this->health = 0;
		}
	}
}
