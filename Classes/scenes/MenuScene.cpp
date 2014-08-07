/*
 * MenuScene.cpp
 *
 *  Created on: 25/07/2013
 *      Author: munhra
 */

#include "MenuScene.h"
#include "GameLevelLayer.h"
#include "SimpleAudioEngine.h"
#include "StoreBridge/cocos2dx_StoreController.h"
#include "util/PersistenceAux.h"
#include "LevelSelectionScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MenuScene::scene() {
	CCScene *scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

void MenuScene::setCurrencyBalanceLabel() {
	CCLOG("%s \n", "Update Store Balance");
}

bool MenuScene::init() {

	if (!CCLayer::init()) {
		return false;
	}

	PersistenceAux::loadStaticGameData();
	cocos2dx_StoreController::storeOpening();
	winSize = CCDirector::sharedDirector()->getWinSize();
	prepareBG();
	prepareButtons();
	return true;
}

void MenuScene::storeTestCallBack(CCObject* pSender) {
	CCLOG("%s \n", "Store Pressed");
	cocos2dx_StoreController::buyMarketItem("android.test.purchased");
}

void MenuScene::menuCloseCallback(CCObject* pSender) {
	CCLOG("%s \n", "Press Start");
	CCDirector::sharedDirector()->replaceScene(LevelSelectionScene::scene());
}

void MenuScene::prepareButtons() {

	CCMenuItemImage *newgameItem = CCMenuItemImage::create(
			"userinterface/newgame_up.png", "userinterface/newgame_down.png",
			this, menu_selector(MenuScene::newGameButtonCBK));
	newgameItem->setPosition(
			ccp(winSize.width * 0.38, winSize.height / 2 - 80));

	CCMenuItemImage *continuegameItem = CCMenuItemImage::create(
			"userinterface/continue_up.png", "userinterface/continue_down.png",
			this, menu_selector(MenuScene::continueButtonCBK));
	continuegameItem->setPosition(
			ccp(winSize.width * 0.38 + continuegameItem->getContentSize().width,
					winSize.height / 2 - 80));

	CCMenu* pMenu = CCMenu::create(newgameItem, continuegameItem, NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(pMenu, 1);

}

void MenuScene::prepareBG() {

	CCLayerColor *menuBG = CCLayerColor::create(ccc4(247, 233, 176, 255));
	this->addChild(menuBG);

	bgGround = CCSprite::createWithSpriteFrameName("menuGround.png");
	bgGround->setPosition(
			ccp(winSize.width / 2, bgGround->getContentSize().height / 2));
	this->addChild(bgGround);

	spaceGuy = CCSprite::createWithSpriteFrameName("spaceman.png");
	spaceGuy->setPosition(
			ccp(winSize.width * 0.1, bgGround->getContentSize().height * 2));
	this->addChild(spaceGuy);

	gameLogo = CCSprite::createWithSpriteFrameName("crashedLogo.png");
	gameLogo->setPosition(ccp(winSize.width / 2, winSize.height * 0.76));
	this->addChild(gameLogo);

}

void MenuScene::newGameButtonCBK(CCObject *pSender) {
	CCLOG("NewGameButton");
	CCDirector::sharedDirector()->replaceScene(LevelSelectionScene::scene());

}

void MenuScene::continueButtonCBK(CCObject *pSender) {
	CCLOG("ContinueGameButton");

}

void MenuScene::nextScreenButtonCBK(CCObject *pSender) {
	CCLOG("NextScreenButton");

}

void MenuScene::storeButtonCBK(CCObject *pSender) {
	CCLOG("StoreScreenButton");
}

void MenuScene::tutorialButtonCBK(CCObject *pSender) {
	CCLOG("TutorialScreenButton");
}

