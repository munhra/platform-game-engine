/*
 * StarsField.cpp
 *
 *  Created on: 19/12/2013
 *      Author: munhra
 */

#include "StarsField.h"

StarsField::~StarsField() {

}

StarsField* StarsField::create() {
	StarsField *s = new StarsField();
	if (s && s->init()) {
		s->autorelease();
		return s;
	}
	CC_SAFE_DELETE(s);
	return NULL;
}

void StarsField::initStarsField() {
	winSize = CCDirector::sharedDirector()->getWinSize();
	generateStars();
}

void StarsField::update(float dt) {

	for (int ii = 0; ii < 25; ii++) {

		float xPosition =
				((CCSprite *) starsArray->objectAtIndex(ii))->getPosition().x;
		float yPosition =
				((CCSprite *) starsArray->objectAtIndex(ii))->getPosition().y;
		float yIncPosition = yPosition + 20;

		float starHeight =
				((CCSprite *) starsArray->objectAtIndex(ii))->getContentSize().height;

		((CCSprite *) starsArray->objectAtIndex(ii))->setPosition(
				ccp(xPosition, yIncPosition));

		if (yIncPosition > winSize.height + starHeight) {

			((CCSprite *) starsArray->objectAtIndex(ii))->setPosition(
					ccp(xPosition, -starHeight));
		}
	}
}

void StarsField::generateStars() {

	CCLOG("%s \n", "Generate stars ...");
	starsArray = CCArray::create();
	for (int ii = 0; ii < 25; ii++) {
		CCSprite *star = CCSprite::createWithSpriteFrameName("stars1.png");
		star->setPosition(
				ccp(rand() % (int) winSize.width,
						rand() % (int) winSize.height));
		this->addChild(star);
		starsArray->addObject(star);
	}
	starsArray->retain();
}

