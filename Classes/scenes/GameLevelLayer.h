/*
 * GameLevelLayer.h
 *
 *  Created on: Apr 29, 2013
 *      Author: vntraal
 */

#ifndef GAMELEVELLAYER_H_
#define GAMELEVELLAYER_H_

#include "cocos2d.h"
#include "Player.h"
#include "enemies/MeeleEnemy.h"
#include "animatedtiles/AnimatedTile.h"
#include "util/CollisionEngine.h"
#include "util/CCParallaxNodeExtras.h"
#include "util/SpecialTiles.h"
#include "util/PlayerVault.h"

using namespace cocos2d;

class GameLevel : public cocos2d::CCLayer
{

public:

	virtual ~GameLevel();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene(int level);

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameLevel);

    virtual void ccTouchesMoved (CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded (CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled (CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesBegan (CCSet *pTouches, CCEvent *pEvent);

    void endCollisionAnimationCallBack(CCNode *sender);

    void releaseTrapCallBack(CCObject* pSender);

    virtual void onExit();

    static int levelNumber;

private:

    CCTMXTiledMap *map;
    Player *player;
    MeeleEnemy *enemy1;
    CCArray* levelEnemies;
    CCArray* animatedTiles;
    CCArray* releasedTraps;
    bool shipPartCollected;

    CollisionEngine *collisionEngine;
    CCParallaxNodeExtras *_backgroundNode;

    CCSprite *_firstlayerbg1;
    CCSprite *_firstlayerbg2;

    CCSprite *_spacedust1;
    CCSprite *_spacedust2;
    CCSprite *_planetsunrise;
    CCSprite *_galaxy;
    CCSprite *_spacialanomaly;
   	CCSprite *_spacialanomaly2;

   	CCLabelBMFont* levelValue;
	CCLabelBMFont* coinsValue ;
	CCLabelBMFont* healthValue;
	CCLabelBMFont* trapsValue;
	CCLabelBMFont* partsValue;

	PlayerVault* vault;

   	CCSize winSize;

	void gameOver(bool won);
	void handleHazardCollisions(Player *p);
	void checkForAndResolveCollisions(Player *p);
	CCArray* getSurroundingTilesAtPosition(CCPoint position, CCTMXLayer *layer);
	void reloadGamePlayScene(CCObject *sender);
	void update(float dt);
	void setViewpointCenter(CCPoint position);
	void checkToStopPlayer(Player *p);
	void checkForWin();
	void initParallax();
	void updateParallax(float dt);
	CCArray* fetchTilesFromLayer(CCTMXLayer* layer);
	void updateAllEnemies(float dt);
	void updateAllTraps(float dt);
	void checkItemCollision();
	void checkEnemyCollision();
	void initHud();
	void updateHud();
	CCPoint tileCoordForPosition(CCPoint position);
	CCRect tileRectFromTileCoords(CCPoint tileCoords);

};

#endif // GAMELEVELLAYER_H_
