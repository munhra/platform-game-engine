/*
 * HistoryBasicLayer.cpp
 *
 *  Created on: 24/12/2013
 *      Author: munhra
 */

#include "HistoryBasicLayer.h"

void HistoryBasicLayer::createMenu() {

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *skipMenuItem = CCMenuItemImage::create(
			"userinterface/skip_up.png", "userinterface/skip_down.png", this,
			menu_selector(HistoryBasicLayer::menuSkipCallback));

	skipMenu = CCMenu::create(skipMenuItem, NULL);
	skipMenu->setPosition(ccp(size.width * 0.75, size.height * 0.005));
	skipMenu->setScale(0.75);
	this->addChild(skipMenu, 1);
}

void HistoryBasicLayer::menuSkipCallback(CCObject* pSender) {
	CCLOG("Skip to main menu");
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}
