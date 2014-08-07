/*
 * SplScr1Scene.cpp
 *
 *  Created on: 25/07/2013
 *      Author: munhra
 */

#include "LevelFailedScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "GameLevelLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* LevelFailedScene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	LevelFailedScene *layer = LevelFailedScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelFailedScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}

	CCLabelTTF* pLabel = CCLabelTTF::create("Level Failed !!!", "Thonburi", 34);

	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition(ccp(size.width / 2, size.height - 300));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	CCMoveBy *slideIn = CCMoveBy::create(0.5,
			ccp(size.width / 2, size.height - 400));

	CCMenuItemImage *replay = CCMenuItemImage::create("reload.png",
			"reload.png", "reload.png", this,
			menu_selector(LevelFailedScene::reloadGamePlayScene));

	CCMenuItemImage *gomenu = CCMenuItemImage::create("menu.png", "menu.png",
			"menu.png", this, menu_selector(LevelFailedScene::gotoMenu));

	CCArray *menuItems = CCArray::create();
	menuItems->addObject(replay);
	menuItems->addObject(gomenu);

	CCMenu *menu = CCMenu::createWithArray(menuItems);
	menu->setPosition(ccp(0, 0));
	menu->alignItemsHorizontally();
	this->addChild(menu);

	menu->runAction(slideIn);

	return true;
}

void LevelFailedScene::reloadGamePlayScene(CCObject *sender) {
	CCLOG("reloadGamePlayScene");
	//CCDirector::sharedDirector()->replaceScene(
	//		CCTransitionZoomFlipX::create(0.5, GameLevel::scene(GameLevel::levelNumber)));

	//CCDirector::sharedDirector()->replaceScene(GameLevel::scene(GameLevel::levelNumber));
}

void LevelFailedScene::gotoMenu(CCObject *sender) {
	CCLOG("gotoMenu");
	//CCDirector::sharedDirector()->replaceScene(
	//		CCTransitionZoomFlipX::create(0.5, MenuScene::scene()));

	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());

}
