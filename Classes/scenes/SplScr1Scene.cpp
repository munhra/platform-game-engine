/*
 * SplScr1Scene.cpp
 *
 *  Created on: 25/07/2013
 *      Author: munhra
 */

#include "scenes/SplScr1Scene.h"
#include "scenes/SplScr2Scene.h"
#include "scenes/HistoryScr.h"
#include "scenes/HistoryScr3.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* SplScr1Scene::scene() {
	CCScene *scene = CCScene::create();
	SplScr1Scene *layer = SplScr1Scene::create();
	scene->addChild(layer);
	return scene;
}

bool SplScr1Scene::init() {
	if (!CCLayer::init()) {
		return false;
	}

	winSize = CCDirector::sharedDirector()->getWinSize();

	prepareLogo();
	this->schedule(schedule_selector(SplScr1Scene::changeScene), 3.5);
	return true;
}

void SplScr1Scene::changeScene(float dt) {
	CCLOG("%s \n", "Change Scene to history screen");
	//CCDirector::sharedDirector()->replaceScene(
	//CCTransitionZoomFlipX::create(0.5, SplScr2Scene::scene()));
	//CCDirector::sharedDirector()->replaceScene(HistoryScr::scene());
	CCDirector::sharedDirector()->replaceScene(SplScr2Scene::scene());
	//CCDirector::sharedDirector()->replaceScene(HistoryScr3::scene());

}

void SplScr1Scene::prepareLogo() {

	// Definitions

	computer = CCSprite::createWithSpriteFrameName("comp1.png");
	computer->setPosition(ccp(winSize.width * 0.20, winSize.height / 2));
	this->addChild(computer);

	company = CCSprite::createWithSpriteFrameName("munhra_soft.png");
	company->setPosition(ccp(winSize.width * 0.60, winSize.height * 0.65));
	this->addChild(company);

	slogan = CCSprite::createWithSpriteFrameName("company.png");
	slogan->setPosition(ccp(winSize.width * 0.63, winSize.height * 0.50));
	this->addChild(slogan);

	cursor = CCSprite::createWithSpriteFrameName("cursor.png");
	cursor->setPosition(ccp(winSize.width * 0.67, winSize.height * 0.43));
	this->addChild(cursor);

	// Effects
	CCBlink *cursorBlink = CCBlink::create(4, 10);
	cursor->runAction(cursorBlink);

	//CCTintTo *compTint = CCTintTo::create(0.5, 255, 255, 255);
	//computer->runAction(compTint);

	defineComputerAnim();

}

void SplScr1Scene::defineComputerAnim() {

	//Computer animation
	CCArray *compAnimFrames = CCArray::create();

	for (int i = 1; i <= 2; i++) {
		CCString* framename = CCString::createWithFormat("comp%d.png", i);

		compAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						framename->getCString()));
	}

	CCAnimation *compAnim = CCAnimation::createWithSpriteFrames(
			compAnimFrames, 1.0);

	compAnim->setRestoreOriginalFrame(true);

	CCAction *compActionAnim = CCRepeatForever::create(
			CCAnimate::create(compAnim));

	computer->runAction(compActionAnim);

}
