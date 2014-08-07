/*
 * HistoryBasicLayer.h
 *
 *  Created on: 24/12/2013
 *      Author: munhra
 */

#ifndef HISTORYBASICLAYER_H_
#define HISTORYBASICLAYER_H_

#include "cocos2d.h"
#include "SplScr2Scene.h"
#include "MenuScene.h"

using namespace cocos2d;

class HistoryBasicLayer : public cocos2d::CCLayer{
public:


	CCMenu *skipMenu;
	void createMenu();
	void menuSkipCallback(CCObject* pSender);

};

#endif /* HISTORYBASICLAYER_H_ */
