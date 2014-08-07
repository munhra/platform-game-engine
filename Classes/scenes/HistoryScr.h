/*
 * HistoryScr.h
 *
 *  Created on: 16/12/2013
 *      Author: munhra
 */

#ifndef HISTORYSCR_H_
#define HISTORYSCR_H_

#include "cocos2d.h"
#include "util/CCParallaxNodeExtras.h"
#include "HistoryBasicLayer.h"

using namespace cocos2d;

class HistoryScr : public HistoryBasicLayer{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(HistoryScr);

private:

    CCParallaxNodeExtras *_backgroundNode;

    CCSprite *star1,*star2,*star3,*star4,*star5,*star6,*star7,*star8,*star9,*star10;
   	CCSize winSize;

   	CCSprite *ship;
   	CCSprite *engine;
   	CCSprite *shipWindow;
   	CCSprite *message1;
   	CCSprite *message2;
   	CCArray *meteors;

   	void update(float dt);
   	void initParallax();
    void updateParallax(float dt);
    void generateStars();
    void shipTranslation();
    void generateMessage(int number);
    void endMoveMessage(CCNode* sender);
    void endMoveMeteor(CCNode* sender);
    void endMoveShip(CCNode* sender);
    void defineAnimations();
    void meteorShower(float dt);
    void createMeteor(float dt);
    void generateMeteors();
    void checkMeteorCollision();
    CCRect shipBoundingBox();
    void *generateFire(CCPoint position);
    void shipCrash(float dt);
    //void createMenu();
    //void menuSkipCallback(CCObject* pSender);



};

#endif /* HISTORYSCR_H_ */
