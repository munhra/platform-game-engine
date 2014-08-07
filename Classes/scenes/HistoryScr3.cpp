/*
 * HistoryScr3.cpp
 *
 *  Created on: 23/12/2013
 *      Author: munhra
 */

#include "HistoryScr3.h"
#include "SplScr2Scene.h"
#include "MenuScene.h"

CCScene* HistoryScr3::scene() {
	CCScene *scene = CCScene::create();
	HistoryScr3 *layer = HistoryScr3::create();
	scene->addChild(layer);
	return scene;
}

bool HistoryScr3::init() {

	if (!CCLayer::init()) {
		return false;
	}
	winSize = CCDirector::sharedDirector()->getWinSize();
	createMenu();
	return true;
}

void HistoryScr3::onEnterTransitionDidFinish() {
	generatePlanetBG();
	this->scheduleOnce(schedule_selector(HistoryScr3::showMessage), 4);

}

void HistoryScr3::showMessage(CCNode *sender) {
	CCLOG("Showmessage");
	generateMessage(1);
}

void HistoryScr3::generatePlanetBG() {

	CCLayerColor *blueSky = CCLayerColor::create(ccc4(67, 195, 239, 255));
	this->addChild(blueSky);

	planetGround = CCSprite::createWithSpriteFrameName("planetbase.png");
	planetGround->setPosition(
			ccp(winSize.width / 2, planetGround->getContentSize().height / 2));
	this->addChild(planetGround);

	stone = CCSprite::createWithSpriteFrameName("stone.png");
	stone->setPosition(
			ccp(winSize.width * 0.3,
					planetGround->getContentSize().height + 50));
	this->addChild(stone);

	generateClouds();
	generateTree();
	prepareShip();

}

void HistoryScr3::generateClouds() {

	cloud1 = CCSprite::createWithSpriteFrameName("cloud.png");
	cloud1->setPosition(ccp(winSize.width / 2, winSize.height * 0.85));

	cloud2 = CCSprite::createWithSpriteFrameName("cloud.png");
	cloud2->setPosition(ccp(winSize.width * 0.85, winSize.height * 0.75));

	cloud3 = CCSprite::createWithSpriteFrameName("cloud.png");
	cloud3->setPosition(ccp(winSize.width / 10, winSize.height * 0.55));

	this->addChild(cloud1);
	this->addChild(cloud2);
	this->addChild(cloud3);

	applyTransition(cloud1);
	applyTransition(cloud2);
	applyTransition(cloud3);

}

void HistoryScr3::applyTransition(CCNode *node) {

	CCPoint deltaX1 = ccp(5, 0);
	CCPoint deltaX2 = ccp(4, 0);
	CCPoint deltaY1 = ccp(0, 5);
	CCPoint deltaY2 = ccp(0, 4);

	CCFiniteTimeAction *moveForward = CCMoveTo::create(1,
			ccpAdd(node->getPosition(), deltaX1));

	CCFiniteTimeAction *moveBackward = CCMoveTo::create(1,
			ccpSub(node->getPosition(), deltaX2));

	CCFiniteTimeAction *moveUp = CCMoveTo::create(1,
			ccpAdd(node->getPosition(), deltaY1));

	CCFiniteTimeAction *moveDown = CCMoveTo::create(1,
			ccpSub(node->getPosition(), deltaY2));

	CCFiniteTimeAction *endMoveCallBack = CCCallFuncN::create(this,
			callfuncN_selector(HistoryScr3::endMoveTranslation));

	CCSequence *moveSequence = CCSequence::create(moveForward, moveBackward,
			moveUp, moveDown, endMoveCallBack, NULL);

	node->runAction(moveSequence);

}

void HistoryScr3::endMoveTranslation(CCNode* sender) {
	CCLOG("%s \n", "endMoveTranslation");
	applyTransition(sender);

}

void HistoryScr3::generateTree() {

	CCArray *treeAnimFrames = CCArray::create();

	tree = CCSprite::createWithSpriteFrameName("tree1.png");

	for (int i = 1; i <= 4; i++) {
		CCString* framename = CCString::createWithFormat("tree%d.png", i);

		treeAnimFrames->addObject(
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						framename->getCString()));
	}

	CCAnimation *treeAnim = CCAnimation::createWithSpriteFrames(treeAnimFrames,
			2);

	treeAnim->setRestoreOriginalFrame(true);

	CCAction *treeActionAnim = CCRepeatForever::create(
			CCAnimate::create(treeAnim));

	tree->runAction(treeActionAnim);
	this->addChild(tree, 10);
	tree->setPosition(
			ccp(winSize.width * 0.85,
					planetGround->getContentSize().height + 150));

}

void HistoryScr3::prepareShip() {
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
			ccp(winSize.width * 0.45,
					winSize.height * 0.35 + winSize.height * 0.70
							+ winSize.height / 2));

	ship_control = CCSprite::createWithSpriteFrameName("ship_control.png");

	ship_control->setPosition(
			ccp(winSize.width * 0.80,
					winSize.height * 0.35 + winSize.height * 0.70
							+ winSize.height / 2));

	this->addChild(ship_tail1);
	this->addChild(ship_tail2);
	this->addChild(ship_engine);

	this->addChild(ship_base);
	this->addChild(ship_middle);
	this->addChild(ship_control);

	applyTranslation(1, ship_tail1, 0);
	applyTranslation(0.5, ship_tail2, 0);
	applyTranslation(2, ship_engine, 0);

	applyTranslation(3, ship_base, 0);
	applyTranslation(2, ship_middle, 150);
	applyTranslation(1, ship_control, tree->getPosition().y);

	ship_middle->setRotation(15);
}

void HistoryScr3::applyTranslation(float duration, CCNode *sender,
		float yEndPosition) {

	CCFiniteTimeAction *sprtTransAction = CCMoveTo::create(1,
			ccp(sender->getPosition().x,
					planetGround->getPosition().y
							+ planetGround->getContentSize().height / 2
							+ yEndPosition));
	sender->runAction(sprtTransAction);

}

void HistoryScr3::generateMessage(int number) {

	CCFiniteTimeAction *messageMove;
	CCFiniteTimeAction *message2Move;
	CCFiniteTimeAction *endMoveMessageCallBack;
	CCSequence *moveMessageSequence;

	message1 = CCSprite::createWithSpriteFrameName("message4.png");
	message1->setPosition(ccp(winSize.width + 500, winSize.height - 100));
	this->addChild(message1, 1);

	messageMove = CCMoveTo::create(0.5,
			ccp(winSize.width / 2, winSize.height - 100));
	endMoveMessageCallBack = CCCallFuncN::create(this,
			callfuncN_selector(HistoryScr3::endMoveMessage));

	moveMessageSequence = CCSequence::create(messageMove,
			endMoveMessageCallBack, NULL);

	message1->runAction(moveMessageSequence);

}

void HistoryScr3::endMoveMessage(CCNode* sender) {
	CCLOG("%s \n", "endMessageMove");
	this->scheduleOnce(schedule_selector(HistoryScr3::gotoMenu), 3.5);
}

void HistoryScr3::gotoMenu(CCNode* sender) {
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}
