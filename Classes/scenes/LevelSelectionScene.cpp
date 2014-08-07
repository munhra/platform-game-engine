/*
 * LevelSelectionScene.cpp
 *
 *  Created on: 17/09/2013
 *      Author: munhra
 */

#include "scenes/LevelSelectionScene.h"
#include "scenes/GameLevelLayer.h"

using namespace cocos2d;

CCScene* LevelSelectionScene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	LevelSelectionScene *layer = LevelSelectionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelSelectionScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}

	CCLOG("Set blue sky");
	CCLayerColor *blueSky = CCLayerColor::create(ccc4(100, 100, 250, 255));
	this->addChild(blueSky);

	CCLabelTTF* pLabel = CCLabelTTF::create("Level Selection", "Thonburi", 34);

	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition(ccp(size.width / 2, size.height - 40));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	createMenu();

	return true;
}

void LevelSelectionScene::selectLevel(CCObject *sender) {
	CCLOG("Button clicked !! %d", ((CCMenuItemImage *) sender)->getTag());
	GameLevel::levelNumber = ((CCMenuItemImage *) sender)->getTag() + 1;
	CCDirector::sharedDirector()->replaceScene(
			GameLevel::scene(((CCMenuItemImage *) sender)->getTag() + 1));
}

void LevelSelectionScene::createMenu() {
	CCLOG("Create memu !");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCArray *menuItems = CCArray::create();
	for (int ii = 0; ii < 24; ii++) {
		CCMenuItemImage *levelMenuItem = CCMenuItemImage::create(
				"button_up.png", "button_down.png", "button_disabled.png", this,
				menu_selector(LevelSelectionScene::selectLevel));
		levelMenuItem->setTag(ii);
		levelMenuItem->setScale(0.95);
		menuItems->addObject(levelMenuItem);
	}

	CCMoveBy *slideIn = CCMoveBy::create(0.5,
			ccp(size.width * 0.155, -size.height * 0.12));

	CCMenu *selectionMenu = CCMenu::createWithArray(menuItems);
	selectionMenu->setScale(0.3);
	selectionMenu->alignItemsInRows(3, 3, 3, 3, 3, 3, 3, 3);
	selectionMenu->setPosition(ccp(0, 0));
	this->addChild(selectionMenu);
	selectionMenu->runAction(slideIn);

}

