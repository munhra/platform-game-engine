/*
 * HistoryScr.cpp
 *
 *  Created on: 16/12/2013
 *      Author: munhra
 */

#include "HistoryScr2.h"
#include "HistoryScr3.h"
#include "scenes/SplScr2Scene.h"

CCScene* HistoryScr2::scene() {
	CCScene *scene = CCScene::create();
	HistoryScr2 *layer = HistoryScr2::create();
	scene->addChild(layer);
	return scene;
}

bool HistoryScr2::init() {

	if (!CCLayer::init()) {
		return false;
	}

	sprtRotation = 90;

	CCLayerColor *blueSky = CCLayerColor::create(ccc4(100, 100, 250, 255));
	this->addChild(blueSky, -2);

	winSize = CCDirector::sharedDirector()->getWinSize();

	starsField = StarsField::create();
	starsField->initStarsField();
	this->addChild(starsField);

	this->schedule(schedule_selector(HistoryScr2::update));

	prepareShip();

	generateMessage(1);

	this->scheduleOnce(schedule_selector(HistoryScr2::showPlanet), 7);

	createMenu();

	return true;
}

void HistoryScr2::showPlanet(float dt) {
	CCLOG("%s \n", "Show Planet");
	planet = CCSprite::createWithSpriteFrameName("planet.png");
	planet->setPosition(ccp(winSize.width / 2, -winSize.height));
	this->addChild(planet);

	CCFiniteTimeAction *planetMove = CCMoveTo::create(2,
			ccp(winSize.width / 2, winSize.height / 32));

	CCFiniteTimeAction *endMovePlanetCallBack = CCCallFuncN::create(this,
			callfuncN_selector(HistoryScr2::endMovePlanet));

	CCSequence *movePlanetSequence = CCSequence::create(planetMove,
			endMovePlanetCallBack, NULL);

	planet->runAction(movePlanetSequence);
}

void HistoryScr2::endMovePlanet(CCNode *sender) {
	CCLOG("End move planet !!");
	generateMessage(2);
	shipWreck = CCSprite::createWithSpriteFrameName("shipzoomout.png");
	shipWreck->setPosition(ccp(winSize.width * 0.25, winSize.height * 0.75));
	shipWreck->setScale(0.7);

	this->addChild(shipWreck);

	CCFiniteTimeAction *shipWrkMove = CCMoveTo::create(2,
			planet->getPosition());

	CCFiniteTimeAction *endMoveShipWrkCallBack = CCCallFuncN::create(this,
			callfuncN_selector(HistoryScr2::endMoveShipWrk));

	CCSequence *moveShipWrkSequence = CCSequence::create(shipWrkMove,
			endMoveShipWrkCallBack, NULL);

	shipWreck->runAction(moveShipWrkSequence);

}

void HistoryScr2::endMoveShipWrk(CCNode *sender) {
	CCLOG("End move ship wrk");
	//change to last scene

	//CCDirector::sharedDirector()->replaceScene(HistoryScr3::scene());

	CCDirector::sharedDirector()->replaceScene(
			CCTransitionFade::create(2, HistoryScr3::scene(),
					ccc3(255, 255, 255)));

}

void HistoryScr2::generateMessage(int number) {

	CCFiniteTimeAction *messageMove;
	CCFiniteTimeAction *message2Move;
	CCFiniteTimeAction *endMoveMessageCallBack;
	CCSequence *moveMessageSequence;

	switch (number) {
	case 1:
		//smooth traveling
		message1 = CCSprite::createWithSpriteFrameName("message3.png");
		message1->setPosition(ccp(winSize.width + 500, winSize.height - 100));
		this->addChild(message1, 1);

		messageMove = CCMoveTo::create(0.5,
				ccp(winSize.width / 2, winSize.height - 100));
		endMoveMessageCallBack = CCCallFuncN::create(this,
				callfuncN_selector(HistoryScr2::endMoveMessage));

		moveMessageSequence = CCSequence::create(messageMove,
				endMoveMessageCallBack, NULL);

		message1->runAction(moveMessageSequence);
		break;
	case 2:
		//meteor shower
		message2 = CCSprite::createWithSpriteFrameName("message6.png");
		message2->setPosition(ccp(winSize.width + 500, winSize.height - 100));
		this->addChild(message2, 1);
		messageMove = CCMoveTo::create(0.5,
				ccp(winSize.width - 2000, winSize.height - 100));

		message2Move = CCMoveTo::create(0.5,
				ccp(winSize.width / 2, winSize.height - 100));
		moveMessageSequence = CCSequence::create(messageMove,
				endMoveMessageCallBack, NULL);
		message1->runAction(moveMessageSequence);
		moveMessageSequence = CCSequence::create(message2Move,
				endMoveMessageCallBack, NULL);
		message2->runAction(moveMessageSequence);

		break;
	default:
		break;

	}

}

void HistoryScr2::endMoveMessage(CCNode* sender) {
	CCLOG("%s \n", "endMessageMove");
}

void HistoryScr2::onEnterTransitionDidFinish() {
	CCLOG("onEnterTransitionDidFinish");
}

void HistoryScr2::update(float dt) {
//CCLOG("%s \n","Update from history screen");
	starsField->update(dt);
}

void HistoryScr2::prepareShip() {
	ship_engine = CCSprite::createWithSpriteFrameName("ship_engine.png");
	ship_engine->setPosition(
			ccp(winSize.width / 10, winSize.height / 2 + winSize.height / 2));

	ship_tail1 = CCSprite::createWithSpriteFrameName("ship_tail1.png");
	ship_tail1->setPosition(
			ccp(winSize.width * 0.35,
					winSize.height * 0.45 + winSize.height / 2));

	ship_tail2 = CCSprite::createWithSpriteFrameName("ship_tail2.png");
	ship_tail2->setPosition(
			ccp(winSize.width / 4, winSize.height * 0.75 + winSize.height / 2));

	ship_base = CCSprite::createWithSpriteFrameName("ship_base.png");
	ship_base->setPosition(
			ccp(winSize.width * 0.60, winSize.height * 0.35 + winSize.height));

	ship_middle = CCSprite::createWithSpriteFrameName("ship_middle.png");
	ship_middle->setPosition(
			ccp(winSize.width * 0.60,
					winSize.height * 0.35 + winSize.height * 0.70
							+ winSize.height / 2));

	ship_control = CCSprite::createWithSpriteFrameName("ship_control.png");

	ship_control->setPosition(
			ccp(winSize.width * 0.80,
					winSize.height * 0.35 + winSize.height * 0.70
							+ winSize.height / 2));

	CCSprite *smoke1 = createSmoke();
	smoke1->setPosition(
			ccp(ship_engine->getPosition().x - 30,
					ship_engine->getPosition().y + 50));

	this->addChild(smoke1);
	this->addChild(ship_tail1);
	this->addChild(ship_tail2);
	this->addChild(ship_engine);

	this->addChild(ship_base);
	this->addChild(ship_middle);
	this->addChild(ship_control);

	applyTranslation(10, ship_tail1);
	applyTranslation(15, ship_tail2);
	applyTranslation(13, ship_engine);

	applyTranslation(12, ship_base);
	applyTranslation(12, ship_middle);
	applyTranslation(10, ship_control);

	applyTranslation(13, smoke1);

	applyRotation(ship_engine);
	applyRotation(ship_control);
	ship_middle->setRotation(90);
}

CCSprite * HistoryScr2::createSmoke() {

//Create Smoke

	CCArray *smokeAnimFrames = CCArray::create();

	for (int i = 1; i <= 6; i++) {
		CCString* framename = CCString::createWithFormat("smoke%d.png", i);

		smokeAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						framename->getCString()));
	}

	CCAnimation *smokeAnim = CCAnimation::createWithSpriteFrames(
			smokeAnimFrames, 0.09f);

	smokeAnim->setRestoreOriginalFrame(true);

	CCAction *smokeActionAnim = CCRepeatForever::create(
			CCAnimate::create(smokeAnim));

	CCSprite *smoke = CCSprite::createWithSpriteFrameName("smoke1.png");

	smoke->runAction(smokeActionAnim);

	return smoke;

}

void HistoryScr2::applyRotation(CCNode* sender) {

	CCFiniteTimeAction *sprtRotAction = CCRotateTo::create(0.5, sprtRotation);
	CCFiniteTimeAction *endSprtRotCallBack = CCCallFuncN::create(this,
			callfuncN_selector(HistoryScr2::endRotateSprt));

	CCSequence *rotateSprtSequence = CCSequence::create(sprtRotAction,
			endSprtRotCallBack, NULL);

	sender->runAction(rotateSprtSequence);
	if (sprtRotation == 360) {
		sprtRotation = 90;
	} else {
		sprtRotation = sprtRotation + 90;
	}

}

void HistoryScr2::endRotateSprt(CCNode* sender) {
	CCLOG("End Engine Rotation");
	applyRotation(sender);
}

void HistoryScr2::applyTranslation(float duration, CCNode *sender) {

	CCFiniteTimeAction *sprtTransAction = CCMoveTo::create(12,
			ccp(sender->getPosition().x, sender->getPosition().y * -1));

	sender->runAction(sprtTransAction);

}
