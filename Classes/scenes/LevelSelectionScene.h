/*
 * LevelSelectionScene.h
 *
 *  Created on: 17/09/2013
 *      Author: munhra
 */

#ifndef LEVELSELECTIONSCENE_H_
#define LEVELSELECTIONSCENE_H_

#include "cocos2d.h"

class LevelSelectionScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(LevelSelectionScene);

    void selectLevel(CCObject *sender);

private:
    void createMenu();

};

#endif /* LEVELSELECTIONSCENE_H_ */
