/*
 * HudDataSource.h
 *
 *  Created on: 13/09/2013
 *      Author: munhra
 */

#ifndef HUDDATASOURCE_H_
#define HUDDATASOURCE_H_

#include "cocos2d.h"

using namespace cocos2d;

class HudDataSource {
public:
	HudDataSource();
	virtual ~HudDataSource();

	CCString *level;
	CCString *coins;
	CCString *health;
	CCString *traps;
	CCString *shipParts;


};

#endif /* HUDDATASOURCE_H_ */
