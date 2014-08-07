/*
 * MeeleEnemy.h
 *
 *  Created on: 06/08/2013
 *      Author: munhra
 */

#ifndef MEELEENEMY_H_
#define MEELEENEMY_H_

#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;

class MeeleEnemy: public CCSprite {

public:

	virtual ~MeeleEnemy();

	CCPoint velocity;
	CCPoint desiredPosition;

	bool onGround;
	bool forwardMarch;
	bool backwardMarch;
	bool shoot;
	bool stop;
	bool mightAsWellJump;
	bool onJump;
	bool killEnemy;
	bool trapped;

	// plist parameters

	float sight;
	float speed;
	float dificult;
	float jumpForce;
	float damage;
	CCPoint initPosition;
	const char *name;

	CCAction *stopAnimation;
	CCAction *jumpAnimation;
	CCAction *deathAnimation;
	CCAction *attackAnimation;

	CCSequence *attackSequence;
	bool attackSeqEnded;

	CCSequence *moveSequence;
	bool moveSeqEnded;

	Player *player;

	static MeeleEnemy* create(CCString* filename, CCString* dificult,
			CCString* jumpForce, CCString* sight, CCString* speed, CCPoint initPosition,
			CCString* name, CCString* damage);

	CCRect collisionBoundingBox();
	void update(float dt);
	void initMeeleEnemy(Player *playerReference);
	bool doScanForTarget();
	bool doScanForAttack();
	bool doMoveToTarget();
	void doStop();
	void doAction();
	bool doTrapped();
	virtual void onExit();

private:
	//enemyProperties
	void defineAnimations();
	//void playerCollision();
	void endAttackCallBack(CCNode* sender);
	void endMoveCallBack(CCNode* sender);

};

#endif /* MEELEENEMY_H_ */
