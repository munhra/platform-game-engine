/*
 * HistoryScr.cpp
 *
 *  Created on: 16/12/2013
 *      Author: munhra
 */

#include "HistoryScr.h"
#include "HistoryScr2.h"
#include "scenes/SplScr2Scene.h"

CCScene* HistoryScr::scene() {
	CCScene *scene = CCScene::create();
	HistoryScr *layer = HistoryScr::create();
	scene->addChild(layer);
	return scene;
}

bool HistoryScr::init() {

	if (!CCLayer::init()) {
		return false;
	}

	meteors = CCArray::create();
	meteors->retain();

	CCLayerColor *blueSky = CCLayerColor::create(ccc4(100, 100, 250, 255));
	this->addChild(blueSky, -2);

	winSize = CCDirector::sharedDirector()->getWinSize();
	ship = CCSprite::createWithSpriteFrameName("ship.png");
	ship->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 100));

	this->addChild(ship, 1);

	engine = CCSprite::createWithSpriteFrameName("engine1.png");
	engine->setPosition(ccp(25, 300));
	ship->addChild(engine);
	ship->setScale(0.85);

	defineAnimations();
	generateMessage(1);
	//this->setTouchEnabled(true);
	initParallax();
	shipTranslation();
	this->schedule(schedule_selector(HistoryScr::update));
	this->scheduleOnce(schedule_selector(HistoryScr::meteorShower), 5);
	this->scheduleOnce(schedule_selector(HistoryScr::shipCrash), 10);
	createMenu();

	return true;
}
/*
void HistoryScr::createMenu() {

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *skipMenuItem = CCMenuItemImage::create(
			"backgrounds/skip_up.png", "backgrounds/skip_down.png", this,
			menu_selector(HistoryBasicLayer::menuSkipCallback));

	skipMenu = CCMenu::create(skipMenuItem, NULL);
	skipMenu->setPosition(ccp(size.width * 0.85, size.height * 0.10));
	//this->addChild(skipMenu, 1);
}

void HistoryScr::menuSkipCallback(CCObject* pSender) {
	CCLOG("Skip to main menu");
}*/

void HistoryScr::shipCrash(float dt) {
	CCLOG("%s \n", "Ship Crash !!");

	this->stopAllActions();
	this->unscheduleAllSelectors();
	this->unscheduleUpdate();
	this->removeAllChildren();
	this->removeFromParentAndCleanup(true);
	this->setTouchEnabled(false);

	//CCDirector::sharedDirector()->replaceScene(
	//		CCTransitionFade::create(2, HistoryScr2::scene(),
	//				ccc3(255, 255, 255)));

	CCDirector::sharedDirector()->replaceScene(HistoryScr2::scene());

}

void HistoryScr::meteorShower(float dt) {
	CCLOG("%s \n", "Meteor Shower");
	generateMessage(2);
	generateMeteors();

}

void HistoryScr::generateMeteors() {
	CCLOG("%s \n", "Generate Meteors");
	for (int ii = 1; ii < 3; ii++) {
		//randomize
		this->schedule(schedule_selector(HistoryScr::createMeteor),
				1 + (rand() % 100) / 50);

	}

}

void HistoryScr::createMeteor(float dt) {
	CCLOG("%s \n", "Create and move one meteor");

	CCSprite *meteor = CCSprite::createWithSpriteFrameName("meteor1.png");
	meteor->setPosition(
			ccp(rand() % (int) winSize.width,
					winSize.height + (int) rand % 100));

	this->addChild(meteor, 1);

	CCFiniteTimeAction *meteorMove = CCMoveTo::create(1,
			ccp(rand() % (int) winSize.width, -20 - (int) rand() % 100));
	CCFiniteTimeAction *endMoveMeteorCallBack = CCCallFuncN::create(this,
			callfuncN_selector(HistoryScr::endMoveMeteor));

	CCSequence *moveMeteorSequence = CCSequence::create(meteorMove,
			endMoveMeteorCallBack, NULL);

	meteor->runAction(moveMeteorSequence);

	meteors->addObject(meteor);

}

void HistoryScr::checkMeteorCollision() {

	CCArray *meteorsToRemove = CCArray::create();

	for (int ii = 0; ii < meteors->count(); ii++) {
		CCRect meteorRect =
				((CCSprite*) meteors->objectAtIndex(ii))->boundingBox();
		CCRect shipRect = shipBoundingBox();

		if (meteorRect.intersectsRect(shipRect) == true) {
			meteorsToRemove->addObject(meteors->objectAtIndex(ii));
			generateFire(
					((CCSprite *) meteors->objectAtIndex(ii))->getPosition());
			this->removeChild((CCSprite *) meteors->objectAtIndex(ii), true);
		}
	}

	for (int j = 0; j < meteorsToRemove->count(); j++) {
		meteors->removeObject(meteorsToRemove->objectAtIndex(j), true);
	}
}

void *HistoryScr::generateFire(CCPoint position) {
	//generate sprite
	CCSprite *meteorFire = CCSprite::createWithSpriteFrameName("fire1.png");

	//generate fire

	CCArray *fireAnimFrames = CCArray::create();

	for (int i = 1; i <= 3; i++) {
		CCString* framename = CCString::createWithFormat("fire%d.png", i);

		fireAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						framename->getCString()));
	}

	CCAnimation *fireAnim = CCAnimation::createWithSpriteFrames(fireAnimFrames,
			0.09f);

	fireAnim->setRestoreOriginalFrame(true);

	CCAction *fireActionAnim = CCRepeatForever::create(
			CCAnimate::create(fireAnim));

	meteorFire->setScale(0.85);
	meteorFire->setPosition(position);

	ship->addChild(meteorFire);
	meteorFire->runAction(fireActionAnim);

}

void HistoryScr::endMoveMeteor(CCNode* sender) {
	CCLOG("%s \n", "End move meteor");
}

void HistoryScr::update(float dt) {
	//CCLOG("%s \n","Update from history screen");
	updateParallax(dt);
	checkMeteorCollision();
}

void HistoryScr::initParallax() {

	CCLOG("%s \n", "Init paralax from history screen");

	_backgroundNode = CCParallaxNodeExtras::node();
	this->addChild(_backgroundNode, -1);
	_backgroundNode->retain();

	generateStars();

}

void HistoryScr::updateParallax(float dt) {

	CCPoint backgroundScrollVert = ccp(-5000, 0);

	_backgroundNode->setPosition(
			ccpAdd(_backgroundNode->getPosition(),
					ccpMult(backgroundScrollVert, dt)));

	CCArray *starsArray = CCArray::createWithCapacity(10);

	starsArray->addObject(star1);
	starsArray->addObject(star2);
	starsArray->addObject(star3);
	starsArray->addObject(star4);
	starsArray->addObject(star5);
	starsArray->addObject(star6);
	starsArray->addObject(star7);
	starsArray->addObject(star8);
	starsArray->addObject(star9);
	starsArray->addObject(star10);

	for (int ii = 0; ii < starsArray->count(); ii++) {
		CCSprite * star = (CCSprite *) (starsArray->objectAtIndex(ii));
		float xPosition = _backgroundNode->convertToWorldSpace(
				star->getPosition()).x;
		float size = star->getContentSize().width;
		if (xPosition < -size) {
			_backgroundNode->incrementOffset(ccp(1200, 0), star);
		}
	}

}

void HistoryScr::defineAnimations() {

	//Engine animation
	CCArray *engineAnimFrames = CCArray::create();

	for (int i = 1; i <= 3; i++) {
		CCString* framename = CCString::createWithFormat("engine%d.png", i);

		engineAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						framename->getCString()));
	}

	CCAnimation *engineAnim = CCAnimation::createWithSpriteFrames(
			engineAnimFrames, 0.09f);

	engineAnim->setRestoreOriginalFrame(true);

	CCAction *engineActionAnim = CCRepeatForever::create(
			CCAnimate::create(engineAnim));

	engine->runAction(engineActionAnim);

	//Window Warning Animation

}

void HistoryScr::shipTranslation() {

	CCFiniteTimeAction *shipMoveForward = CCMoveTo::create(1,
			ccp(winSize.width / 2 + 40, winSize.height / 2 - 100));

	CCFiniteTimeAction *shipMoveBackward = CCMoveTo::create(1,
			ccp(winSize.width / 2 - 40, winSize.height / 2 - 100));

	CCFiniteTimeAction *shipMoveUp = CCMoveTo::create(1,
			ccp(winSize.width / 2 - 40, winSize.height / 2));

	CCFiniteTimeAction *shipMoveDown = CCMoveTo::create(1,
			ccp(winSize.width / 2 - 40, winSize.height / 2 - 100));

	CCFiniteTimeAction *endMoveShipCallBack = CCCallFuncN::create(this,
			callfuncN_selector(HistoryScr::endMoveShip));

	CCSequence *moveShipSequence = CCSequence::create(shipMoveForward,
			shipMoveBackward, shipMoveUp, shipMoveDown, endMoveShipCallBack,
			NULL);

	ship->runAction(moveShipSequence);
}

void HistoryScr::endMoveShip(CCNode* sender) {
	CCLOG("%s \n", "endMoveShipCallBack");
	shipTranslation();

}

void HistoryScr::generateMessage(int number) {

	CCFiniteTimeAction *messageMove;
	CCFiniteTimeAction *message2Move;
	CCFiniteTimeAction *endMoveMessageCallBack;
	CCSequence *moveMessageSequence;

	switch (number) {
	case 1:
		//smooth traveling
		message1 = CCSprite::createWithSpriteFrameName("message1.png");
		message1->setPosition(ccp(winSize.width + 500, winSize.height - 100));
		this->addChild(message1, 1);

		messageMove = CCMoveTo::create(0.5,
				ccp(winSize.width / 2, winSize.height - 100));
		endMoveMessageCallBack = CCCallFuncN::create(this,
				callfuncN_selector(HistoryScr::endMoveMessage));

		moveMessageSequence = CCSequence::create(messageMove,
				endMoveMessageCallBack, NULL);

		message1->runAction(moveMessageSequence);
		break;
	case 2:
		//meteor shower
		message2 = CCSprite::createWithSpriteFrameName("message2.png");
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

CCRect HistoryScr::shipBoundingBox() {

	CCRect adjustedRect;
	CCRect shipRect = ship->boundingBox();

	adjustedRect = CCRect(shipRect.origin.x + 40, shipRect.origin.y - 140,
			shipRect.size.width - 40, shipRect.size.height - 40);

	return adjustedRect;

}

void HistoryScr::endMoveMessage(CCNode* sender) {
	CCLOG("%s \n", "endMessageMove");
}

void HistoryScr::generateStars() {

	CCLOG("%s \n", "Generate stars ...");

	CCPoint dustSpeed = ccp(0.1, 0.1);

	star1 = CCSprite::createWithSpriteFrameName("stars1.png");
	star1->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	star2 = CCSprite::createWithSpriteFrameName("stars1.png");
	star2->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	star3 = CCSprite::createWithSpriteFrameName("stars1.png");
	star3->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	star4 = CCSprite::createWithSpriteFrameName("stars1.png");
	star4->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	star5 = CCSprite::createWithSpriteFrameName("stars1.png");
	star5->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	star6 = CCSprite::createWithSpriteFrameName("stars1.png");
	star6->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	star7 = CCSprite::createWithSpriteFrameName("stars1.png");
	star7->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	star8 = CCSprite::createWithSpriteFrameName("stars1.png");
	star8->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	star9 = CCSprite::createWithSpriteFrameName("stars1.png");
	star9->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	star10 = CCSprite::createWithSpriteFrameName("stars1.png");
	star10->setPosition(
			ccp(rand() % (int) winSize.width, rand() % (int) winSize.height));

	_backgroundNode->addChild(star1, 0, dustSpeed, star1->getPosition());

	_backgroundNode->addChild(star2, 0, dustSpeed, star2->getPosition());

	_backgroundNode->addChild(star3, 0, dustSpeed, star3->getPosition());

	_backgroundNode->addChild(star4, 0, dustSpeed, star4->getPosition());

	_backgroundNode->addChild(star5, 0, dustSpeed, star5->getPosition());

	_backgroundNode->addChild(star6, 0, dustSpeed, star6->getPosition());

	_backgroundNode->addChild(star7, 0, dustSpeed, star7->getPosition());

	_backgroundNode->addChild(star8, 0, dustSpeed, star8->getPosition());

	_backgroundNode->addChild(star9, 0, dustSpeed, star9->getPosition());

	_backgroundNode->addChild(star10, 0, dustSpeed, star10->getPosition());

	CCLOG("%s \n", "End generate stars");

}

