/*
 *
 *  Created on: 25/07/2013
 *      Author: munhra
 */

#ifndef LEVELFAILEDSCENE_H_
#define LEVELFAILEDSCENE_H_

#include "cocos2d.h"

class LevelFailedScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(LevelFailedScene);

    void reloadGamePlayScene(CCObject *sender);
    void gotoMenu(CCObject *sender);
};

#endif /* LEVELFAILEDSCENE_H_ */
