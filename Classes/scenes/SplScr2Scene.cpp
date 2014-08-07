/*
 * SplScr2Scene.cpp
 *
 *  Created on: 25/07/2013
 *      Author: munhra
 */

#include "SplScr2Scene.h"
#include "MenuScene.h"
#include "LevelSelectionScene.h"
#include "HistoryScr.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* SplScr2Scene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	SplScr2Scene *layer = SplScr2Scene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SplScr2Scene::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}

	CCLabelTTF* pLabel = CCLabelTTF::create("Splash Screen 2", "Thonburi", 34);

	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition(ccp(size.width / 2, size.height / 2 - 20));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	this->schedule(schedule_selector(SplScr2Scene::changeScene), 2.0);

	return true;
}

void SplScr2Scene::changeScene(float dt) {
	CCLOG("%s \n", "Change Scene to menu");
	CCDirector::sharedDirector()->replaceScene(HistoryScr::scene());
	//CCDirector::sharedDirector()->replaceScene(
	//	CCTransitionZoomFlipX::create(0.5, LevelSelectionScene::scene()));
}
