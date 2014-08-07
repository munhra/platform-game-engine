/*
 * Trap.h
 *
 *  Created on: 16/10/2013
 *      Author: munhra
 */

#ifndef TRAP_H_
#define TRAP_H_

#include "cocos2d.h"

using namespace cocos2d;

class Trap : public CCSprite {

public:

	bool onGround;
	bool pickable;
	CCPoint velocity;
	CCPoint desiredPosition;

	CCAction *defaultAnimation;

	virtual ~Trap();
	static Trap* create();
	void initTrap(CCPoint initPoint);
	CCRect collisionBoundingBox();
	void update(float dt);
	virtual void onExit();

private:
	void defineAnimations();
	void pickDelay(float dt);
};

#endif /* TRAP_H_ */
