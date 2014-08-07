/*
 * HistoryScr2.h
 *
 *  Created on: 16/12/2013
 *      Author: munhra
 */

#ifndef HISTORYSCR2_H_
#define HISTORYSCR2_H_

#include "cocos2d.h"
#include "util/CCParallaxNodeExtras.h"
#include "util/StarsField.h"
#include "HistoryBasicLayer.h"

using namespace cocos2d;

class HistoryScr2: public HistoryBasicLayer {
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC (HistoryScr2);

	virtual void onEnterTransitionDidFinish();

private:

	CCSprite *ship_engine;
	CCSprite *ship_tail1;
	CCSprite *ship_tail2;
	CCSprite *ship_control;
	CCSprite *ship_base;
	CCSprite *ship_middle;

	CCSprite *planet;
	CCSprite *shipWreck;


	StarsField* starsField;

	CCSize winSize;
	float sprtRotation;

	CCSprite *message1;
   	CCSprite *message2;

	void update(float dt);

	void initParallax();
	void updateParallax(float dt);
	void generateStars();
	void prepareShip();
	CCSprite *createSmoke();
	void endRotateSprt(CCNode* sender);
	void applyRotation(CCNode* sender);
	void applyTranslation(float duration, CCNode *sender);
	void generateMessage(int number);
	void endMoveMessage(CCNode* sender);
	void showPlanet(float dt);
	void endMovePlanet(CCNode *sender);
	void endMoveShipWrk(CCNode *sender);

};

#endif /* HISTORYSCR2_H_ */
