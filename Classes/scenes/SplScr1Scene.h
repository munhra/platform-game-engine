/*
 * SplScr1Scene.h
 *
 *  Created on: 25/07/2013
 *      Author: munhra
 */

#ifndef SPLSCR1SCENE_H_
#define SPLSCR1SCENE_H_

#include "cocos2d.h"

using namespace cocos2d;

class SplScr1Scene : public cocos2d::CCLayer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(SplScr1Scene);

private:
    CCSprite *computer;
    CCSprite *company;
    CCSprite *slogan;
    CCSprite *cursor;

    CCSize winSize;


    void changeScene(float dt);
    void prepareLogo();
    void defineComputerAnim();


};

#endif /* SPLSCR1SCENE_H_ */
