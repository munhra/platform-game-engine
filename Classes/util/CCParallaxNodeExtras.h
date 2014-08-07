/*
 * CCParallaxNodeExtras.h
 *
 *  Created on: 19/08/2013
 *      Author: munhra
 */

#ifndef CCPARALLAXNODEEXTRAS_H_
#define CCPARALLAXNODEEXTRAS_H_

#include "cocos2d.h"
#include "CCParallaxNodeExtras.h"

USING_NS_CC;

class CCParallaxNodeExtras : public CCParallaxNode {

    public :

    CCParallaxNodeExtras();
    virtual ~CCParallaxNodeExtras();

    static CCParallaxNodeExtras * node();

    void incrementOffset(CCPoint offset, CCNode* node);
} ;

#endif /* CCPARALLAXNODEEXTRAS_H_ */
