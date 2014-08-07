/*
 * HistoryScr3.h
 *
 *  Created on: 23/12/2013
 *      Author: munhra
 */

#ifndef HISTORYSCR3_H_
#define HISTORYSCR3_H_

#include "cocos2d.h"
#include "util/StarsField.h"
#include "HistoryBasicLayer.h"

using namespace cocos2d;

class HistoryScr3: public HistoryBasicLayer {
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC (HistoryScr3);

	virtual void onEnterTransitionDidFinish();

private:

	CCSize winSize;
	CCSprite *planetGround;
	CCSprite *stone;
	CCSprite *tree;
	CCSprite *cloud1;
	CCSprite *cloud2;
	CCSprite *cloud3;

	CCSprite *ship_engine;
	CCSprite *ship_tail1;
	CCSprite *ship_tail2;
	CCSprite *ship_control;
	CCSprite *ship_base;
	CCSprite *ship_middle;

	CCSprite *message1;

	void generatePlanetBG();
	void generateTree();
	void generateClouds();
	void applyTransition(CCNode *node);
	void endMoveTranslation(CCNode* sender);
	void prepareShip();
	void applyTranslation(float duration, CCNode *sender, float yEndPosition);
	void generateMessage(int number);
	void endMoveMessage(CCNode* sender);
	void showMessage(CCNode *sender);
	void gotoMenu(CCNode* sender);

};

#endif /* HISTORYSCR3_H_ */
