/*
 * MeeleEnemy.cpp
 *  Created on: 06/08/2013
 *      Author: munhra
 */

#include "MeeleEnemy.h"
#include "Player.h"

using namespace cocos2d;

MeeleEnemy::~MeeleEnemy() {
	CCLOG("Meele Enemy Destructor");
}

MeeleEnemy* MeeleEnemy::create(CCString* filename, CCString* dificult,
		CCString* jumpForce, CCString* sight, CCString* speed,
		CCPoint initPosition, CCString* name, CCString* damage) {
	CCLOG("Creating the enemy \n");
	MeeleEnemy *enemy = new MeeleEnemy();

	CCString* enemyStopFrame = CCString::createWithFormat("%s_stop%d.png",
			name->getCString(), 1);

	if (enemy && enemy->initWithSpriteFrameName(enemyStopFrame->getCString())) {

		enemy->speed = speed->floatValue();
		enemy->jumpForce = jumpForce->floatValue();
		enemy->sight = sight->floatValue();
		enemy->dificult = dificult->floatValue();
		enemy->damage = damage->floatValue();
		enemy->initPosition = initPosition;
		enemy->name = name->getCString();
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

void MeeleEnemy::initMeeleEnemy(Player *playerReference) {

	player = playerReference;
	onJump == false;
	velocity = ccp(0.0, 0.0);
	stop = true;
	// missing animation frames
	defineAnimations();
	CCLog("initMeeleEnemy");
	this->setPosition(this->initPosition);
	attackSeqEnded = true;
	moveSeqEnded = true;
	trapped = false;
}

bool MeeleEnemy::doTrapped() {
	trapped = true;

}

bool MeeleEnemy::doScanForTarget() {
	if (ccpDistance(player->getPosition(), this->getPosition()) < this->sight) {
		return true;
	} else {
		return false;
	}
}

bool MeeleEnemy::doScanForAttack() {
	if (ccpDistance(player->getPosition(), this->getPosition()) < 50) {
		//CCLog("Hero Detected Attack...");
		return true;
	} else {
		return false;
	}

}

bool MeeleEnemy::doMoveToTarget() {
	//CCLog("Moving ...");
	//CCLog("Perform walk animation");

	if (moveSeqEnded == true) {
		this->runAction(this->moveSequence);
		moveSeqEnded = false;
	}

	if (player->getPosition().x > this->getPosition().x) {
		forwardMarch = true;
		backwardMarch = false;
		this->setFlipX(false);
	} else {
		forwardMarch = false;
		backwardMarch = true;
		this->setFlipX(true);
	}
}
void MeeleEnemy::doStop() {
	forwardMarch = false;
	backwardMarch = false;
	velocity.x = 0.0;
	stop = true;
	this->stopAllActions();
	attackSeqEnded = true;
	moveSeqEnded = true;
}

void MeeleEnemy::doAction() {
	forwardMarch = false;
	backwardMarch = false;
	if (attackSeqEnded == true) {
		this->runAction(this->attackSequence);
		attackSeqEnded = false;
		//playerCollision();
	}
}

void MeeleEnemy::defineAnimations() {

	// guide [name]_[animation_name]1.png
	CCLog("defineEnemyAnimations");
	// the complete name of the animation frame on the format [enemy->name]_[animation_name][framenumber]
	char frameNameBuf[32] = { 0 };
	// used to build the string [enemy->name]_[animation_name]
	char animationNameBuf[32] = { 0 };

	//walk animation
	sprintf(animationNameBuf, "%s_walk", this->name);
	CCArray *walkAnimFrames = CCArray::create();
	for (int i = 1; i <= 3; i++) {
		sprintf(frameNameBuf, "%s%d.png", animationNameBuf, i);
		walkAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						frameNameBuf));
	}

	CCAnimation *walkAnim = CCAnimation::createWithSpriteFrames(walkAnimFrames,
			0.15f);

	CCFiniteTimeAction *moveFiniteAnim = CCRepeat::create(
			CCAnimate::create(walkAnim), 1);

	CCFiniteTimeAction *endMoveCallBack = CCCallFuncN::create(this,
			callfuncN_selector(MeeleEnemy::endMoveCallBack));

	moveSequence = CCSequence::create(moveFiniteAnim, endMoveCallBack, NULL);

	moveSequence->retain();

	CCLog("defineEnemyWalk");

	//stop animation
	sprintf(animationNameBuf, "%s_stop", this->name);
	CCArray *stopAnimFrames = CCArray::create();
	for (int i = 1; i <= 1; i++) {
		sprintf(frameNameBuf, "%s%d.png", animationNameBuf, i);
		stopAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						frameNameBuf));
	}

	CCAnimation *stopAnim = CCAnimation::createWithSpriteFrames(stopAnimFrames,
			0.15f);
	stopAnimation = CCRepeatForever::create(CCAnimate::create(stopAnim));
	stopAnimation->retain();
	CCLog("defineEnemyStop");

	//attack animation
	sprintf(animationNameBuf, "%s_attack", this->name);
	CCArray *attackAnimFrames = CCArray::create();
	for (int i = 1; i <= 2; i++) {
		sprintf(frameNameBuf, "%s%d.png", animationNameBuf, i);
		attackAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						frameNameBuf));
	}

	CCAnimation *attackAnim = CCAnimation::createWithSpriteFrames(
			attackAnimFrames, 0.15f);
	attackAnim->setRestoreOriginalFrame(true);

	CCFiniteTimeAction *attackFiniteAnim = CCRepeat::create(
			CCAnimate::create(attackAnim), 1);

	CCFiniteTimeAction *endAttackCallBack = CCCallFuncN::create(this,
			callfuncN_selector(MeeleEnemy::endAttackCallBack));

	attackSequence = CCSequence::create(attackFiniteAnim, endAttackCallBack,
			NULL);

	attackSequence->retain();

	CCLog("defineEnemyAttack");

}

void MeeleEnemy::endAttackCallBack(CCNode* sender) {
	attackSeqEnded = true;
}

void MeeleEnemy::endMoveCallBack(CCNode* sender) {
	moveSeqEnded = true;
}

CCRect MeeleEnemy::collisionBoundingBox() {
	CCPoint diff = ccpSub(desiredPosition, this->getPosition());
	CCRect returnBoundingBox = this->boundingBox();
	returnBoundingBox.origin.x = returnBoundingBox.origin.x + diff.x;
	returnBoundingBox.origin.y = returnBoundingBox.origin.y + diff.y;
	return returnBoundingBox;
}

void MeeleEnemy::onExit() {
	CCLOG("On exit enemy retain count %d", this->retainCount());
	CCLOG("attackSequence retain counter %d", attackSequence->retainCount());
	moveSequence->release();
	stopAnimation->release();
	attackSequence->release();
}

/*
void MeeleEnemy::playerCollision(){
	CCRect enemyRect = this->boundingBox();
	//CCRect playerRect = this->player->getTextureRect();
	if (this->player->collisionBoundingBox().intersectsRect(
			enemyRect) == true) {
		//include this parameter on the plist
		this->player->receiveAttack(5);
	}
}*/

void MeeleEnemy::update(float dt) {
	CCPoint gravity = ccp(0.0, -500.0);
	CCPoint gravityStep = ccpMult(gravity, dt);

	CCPoint forwardMove = ccp(this->speed, 0.0);
	CCPoint backwardMove = ccp(-this->speed, 0.0);

	CCPoint forwardStep = ccpMult(forwardMove, dt); //1
	CCPoint backwardStep = ccpMult(backwardMove, dt);

	velocity = ccpAdd(velocity, gravityStep);
	velocity = ccp(velocity.x * 0.80, velocity.y); //2

	if (backwardMarch) {
		CCPoint jumpForce = ccp(0.0, this->jumpForce);
		float jumpCutoff = 150.0;
		// The chunk of code below check if the player is jumping
		if (mightAsWellJump && onGround) {
			//jumping condition

			if (onJump == false) {
				CCLog("onJump false %f\n", velocity.y);
				onJump = true;
				velocity = ccpAdd(velocity, jumpForce);
			} else {
				CCLog("onJump true %f\n", velocity.y);
				onJump = false;
				mightAsWellJump = false;
				backwardMarch = false;
				velocity.x = 0;
				this->stopAllActions();
				attackSeqEnded = true;
				moveSeqEnded = true;
				this->runAction(this->stopAnimation);

			}

			//velocity = ccpAdd(velocity, jumpForce);
		} else if (!mightAsWellJump && velocity.y > jumpCutoff) {
			velocity = ccp(velocity.x, jumpCutoff);
		}
		velocity = ccpAdd(velocity, backwardStep);
	}

	if (forwardMarch) {
		CCPoint jumpForce = ccp(0.0, this->jumpForce);
		float jumpCutoff = 150.0;
		// The chunk of code below check if the player is jumping
		if (mightAsWellJump && onGround) {
			//jumping condition
			//CCLog("mightAsWellJump && onGround velocity y %f\n",velocity.y);

			if (onJump == false) {
				CCLog("onJump false %f\n", velocity.y);
				onJump = true;
				velocity = ccpAdd(velocity, jumpForce);
			} else {
				CCLog("onJump true %f\n", velocity.y);
				onJump = false;
				mightAsWellJump = false;
				forwardMarch = false;
				velocity.x = 0;
				this->stopAllActions();
				attackSeqEnded = true;
				moveSeqEnded = true;
				this->runAction(this->stopAnimation);

			}

		} else if (!mightAsWellJump && velocity.y > jumpCutoff) {
			velocity = ccp(velocity.x, jumpCutoff);
			CCLog("mightAsWellJump && onGround velocity y %f\n", velocity.y);
		}
		velocity = ccpAdd(velocity, forwardStep);
	}

	// limits the bondary of the speed
	CCPoint stepVelocity = ccpMult(velocity, dt);
	desiredPosition = ccpAdd(this->getPosition(), stepVelocity);
	if (trapped == false) {
		if (doScanForTarget()) {
			if (doScanForAttack()) {
				doAction();
			} else {
				doMoveToTarget();
			}
		} else {
			doStop();
		}
	}else{
		doStop();
	}

	//playerCollision();

}

