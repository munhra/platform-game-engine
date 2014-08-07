/*
 * MenuScene.h
 *
 *  Created on: 25/07/2013
 *      Author: munhra
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H_

#include "cocos2d.h"

using namespace cocos2d;

class MenuScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(MenuScene);

    void menuCloseCallback(CCObject* pSender);

    void newGameButtonCBK(CCObject *pSender);

    void continueButtonCBK(CCObject *pSender);

    void nextScreenButtonCBK(CCObject *pSender);

    void storeButtonCBK(CCObject *pSender);

    void tutorialButtonCBK(CCObject *pSender);

    void storeTestCallBack(CCObject* pSender);

    static void setCurrencyBalanceLabel();

private:

    CCSprite *bgGround;
    CCSprite *spaceGuy;
    CCSprite *gameLogo;

    CCSize winSize;

    void prepareBG();
    void prepareButtons();
};

#endif /* MENUSCENE_H_ */
