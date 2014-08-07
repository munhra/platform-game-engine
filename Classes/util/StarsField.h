/*
 * StarsField.h
 *
 *  Created on: 19/12/2013
 *      Author: munhra
 */

#ifndef STARSFIELD_H_
#define STARSFIELD_H_

#include "cocos2d.h"

using namespace cocos2d;

class StarsField: public CCSprite {
public:
	virtual ~StarsField();

	static StarsField* create();
	void initStarsField();
	void update(float dt);

private:

	CCSize winSize;

	CCArray *starsArray;

	void generateStars();

};

#endif /* STARSFIELD_H_ */
