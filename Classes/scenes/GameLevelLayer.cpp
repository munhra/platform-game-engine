#include "GameLevelLayer.h"
//#include "SimpleAudioEngine.h"
#include "Player.h"
#include "util/CCXNumericData.h"
#include "util/CollisionEngine.h"
#include "enemies/MeeleEnemy.h"
#include "LevelFailedScene.h"
#include "LevelWonScene.h"
#include "enemies/LoadLevelEnemies.h"
#include "animatedtiles/LoadAnimTiles.h"
#include "Trap.h"

using namespace cocos2d;
//using namespace CocosDenshion;

CCTMXLayer *walls;
CCTMXLayer *hazards;
bool isGameOver;
bool touchMoved;
float beginYTouch;
float deltaYTouch;
float beginXTouch;
float stopPosition;

CCPoint actualPosition;

int GameLevel::levelNumber;

const int DELTA_Y_FOR_JUMP = 50;
const int DELTA_X_FOR_MOVE = 50;
const int DELTA_X_MOVE_LIMIT = 500;

GameLevel::~GameLevel() {
	CCLOG("GameLevel Descontructor");
}

CCScene* GameLevel::scene(int level) {
	CCLOG("Level Number %d", level);
	CCScene *scene = CCScene::create();
	GameLevel *layer = GameLevel::create();
	GameLevel::levelNumber = level;
	scene->addChild(layer);
	return scene;
}

void GameLevel::setViewpointCenter(CCPoint position) {

	// it is very related to the size of the tilemap
	// it is necessary to parametrize this point
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int x = fmax(position.x, winSize.width / 2);
	int y = fmax(position.y, winSize.height / 2);
	x = fmin(x,
			(map->getMapSize().width * map->getTileSize().width)
					- winSize.width / 2);
	y = fmin(y,
			(map->getMapSize().height * map->getTileSize().height)
					- winSize.height / 2);
	//y = fmin(y, (6000) - winSize.height / 2);
	actualPosition = ccp(x, y);
	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	map->setPosition(viewPoint);
}

void GameLevel::updateAllEnemies(float dt) {
	if (levelEnemies->retainCount() > 0) {
		MeeleEnemy* enemy;
		for (int ii = 0; ii < levelEnemies->count(); ii++) {
			enemy = ((MeeleEnemy *) levelEnemies->objectAtIndex(ii));
			enemy->update(dt);
			this->collisionEngine->checkForAndResolveCollisions(enemy);
			// check if the enemy collides with the trap
			if (releasedTraps->retainCount() > 0) {
				Trap* trap;
				for (int ii = 0; ii < releasedTraps->count(); ii++) {
					trap = ((Trap *) releasedTraps->objectAtIndex(ii));

					// check the enemy collision here
					CCRect tileRect = trap->boundingBox();
					CCRect enemyRect = enemy->getTextureRect();
					if (enemy->collisionBoundingBox().intersectsRect(tileRect)
							== true) {
						enemy->doTrapped();
						trap->pickable = false;

					}
				}
			}
			if (enemy->trapped == false) {
				// generate colision only when the enemy is trapped
				CCRect enemyRect = enemy->boundingBox();
				if (this->player->collisionBoundingBox().intersectsRect(
						enemyRect) == true) {
					//check if the enemy is on attack state.
					//if (enemy->attackSeqEnded == false) {
					this->player->receiveAttack(enemy->damage);
					CCString* playerHealth = CCString::createWithFormat("%d",
							this->player->health);
					healthValue->setString(playerHealth->getCString());
					//}

				}
			}
		}
	}
}

void GameLevel::updateAllTraps(float dt) {
	// it is possible to optimize this, checking if the trap is on ground
	// it is not necessary to run the physics if the trap is on the ground
	if (releasedTraps->retainCount() > 0) {
		Trap* trap;
		for (int ii = 0; ii < releasedTraps->count(); ii++) {
			trap = ((Trap *) releasedTraps->objectAtIndex(ii));
			trap->update(dt);
			this->collisionEngine->checkForAndResolveCollisions(trap);
		}
	}
}

void GameLevel::update(float dt) {
	//CCLOG("update ...");
	if (!isGameOver) {
		if (dt <= 0.03333) {
			//CCLOG("dt value %f",dt);
			this->player->update(dt);
			this->updateAllEnemies(dt);
			this->updateAllTraps(dt);
			this->checkForAndResolveCollisions(this->player);
			this->setViewpointCenter(this->player->getPosition());
			//this->handleHazardCollisions(this->player);
			this->checkToStopPlayer(player);
			this->checkForWin();
			this->updateParallax(dt);
			this->checkItemCollision();
		} else {
			CCLOG("Frame Skiped due to low speed %f", dt);
		}
	}
}

void GameLevel::checkForWin() {
	// create a parameter for each level indicate the end of the level

	if (this->player->getPosition().x
			> (map->getMapSize().width - 5) * map->getTileSize().width) {
		this->gameOver(true);
	}

	/*
	 if (this->player->getPosition().x > 100) {
	 this->gameOver(true);
	 }*/
}

bool GameLevel::init() {
	CCLOG("Init Scene level %d", GameLevel::levelNumber);
	if (!CCLayer::init()) {
		return false;
	}

	winSize = CCDirector::sharedDirector()->getWinSize();

	isGameOver = false;

	if (isGameOver) {
		CCLOG("Game over error");
	} else {
		CCLOG("Game over ok");
	}

	CCString* levelName = CCString::createWithFormat("levels/level%d.tmx",
			GameLevel::levelNumber);

	map = CCTMXTiledMap::create(levelName->getCString());
	this->addChild(map);

	walls = map->layerNamed("walls");

	this->collisionEngine = CollisionEngine::create();

	this->collisionEngine->initCollisionEngine(map);

	this->collisionEngine->retain();

	this->player = Player::create("sprites/walk1.png");

	CCArray* playerInfo = fetchTilesFromLayer(map->layerNamed("player"));

	this->player->initPlayer(
			((SpecialTiles *) playerInfo->objectAtIndex(0))->getTilePosition());

	CCLOG("Collision Engine Created");

	animatedTiles = LoadAnimTiles::getAnimTilesFromLayer(map);
	for (int ii = 0; ii < animatedTiles->count(); ii++) {
		map->addChild((AnimatedTile*) animatedTiles->objectAtIndex(ii));
	}
	animatedTiles->retain();

	levelEnemies = LoadLevelEnemies::getEnemiesListFromLayer(this->map,
			this->player);
	for (int ii = 0; ii < levelEnemies->count(); ii++) {
		map->addChild((MeeleEnemy*) levelEnemies->objectAtIndex(ii));
	}
	levelEnemies->retain();

	map->addChild(this->player, 15);
	stopPosition = this->player->getPosition().x;

	this->initParallax();

	this->schedule(schedule_selector(GameLevel::update));

	this->setTouchEnabled(true);
	CCLOG("End gamelevel layer init process");
	this->vault = PersistenceAux::loadGameData();
	CCLOG("Coins %d", vault->coins);
	this->vault->retain();

	releasedTraps = CCArray::createWithCapacity(3);
	releasedTraps->retain();

	initHud();

	shipPartCollected = false;

	return true;
}

void GameLevel::updateParallax(float dt) {
	CCPoint backgroundScrollVert = ccp(-this->player->velocity.x * -5, 0);

	if (_backgroundNode->retainCount() > 0) {
		_backgroundNode->setPosition(
				ccpAdd(_backgroundNode->getPosition(),
						ccpMult(backgroundScrollVert, dt)));

		CCArray *spaceDusts = CCArray::createWithCapacity(4);
		spaceDusts->addObject(_spacedust1);
		spaceDusts->addObject(_spacedust2);
		//spaceDusts->addObject(_firstlayerbg1);
		//spaceDusts->addObject(_firstlayerbg2);

		for (int ii = 0; ii < spaceDusts->count(); ii++) {
			CCSprite * spaceDust = (CCSprite *) (spaceDusts->objectAtIndex(ii));
			float xPosition = _backgroundNode->convertToWorldSpace(
					spaceDust->getPosition()).x;
			float size = spaceDust->getContentSize().width;
			if (xPosition < -size / 2) {
				_backgroundNode->incrementOffset(
						ccp(spaceDust->getContentSize().width * 2, 0),
						spaceDust);
			}
		}

	}

	/*
	 CCArray *backGrounds = CCArray::createWithCapacity(4);
	 backGrounds->addObject(_galaxy);
	 //backGrounds->addObject(_planetsunrise);
	 backGrounds->addObject(_spacialanomaly);
	 backGrounds->addObject(_spacialanomaly2);
	 for ( int ii = 0; ii <backGrounds->count(); ii++ ) {
	 CCSprite * background = (CCSprite *)(backGrounds->objectAtIndex(ii));
	 float xPosition = _backgroundNode->convertToWorldSpace(background->getPosition()).x;
	 float size = background->getContentSize().width;
	 if ( xPosition < -size ) {
	 _backgroundNode->incrementOffset(ccp(2000,0),background);
	 //_backgroundNode->incrementOffset(ccp(this->player->velocity.x,0),background);
	 }


	 }*/
}

void GameLevel::initParallax() {

	//1) Create the CCParallaxNode
	//_backgroundNode = CCParallaxNode::create(); //1
	_backgroundNode = CCParallaxNodeExtras::node();
	this->addChild(_backgroundNode, -1);
	_backgroundNode->retain();

	// 2) Create the sprites will be added to the CCParallaxNode
	_spacedust1 = CCSprite::create("backgrounds/bg1.png"); // first piece of the bg
	_spacedust2 = CCSprite::create("backgrounds/bg1.png"); // second piece of the bg

	//_firstlayerbg1 = CCSprite::create("backgrounds/layer2bg1_test.jpg");
	//_firstlayerbg2 = CCSprite::create("backgrounds/layer2bg1_test.jpg");

	//_planetsunrise = CCSprite::create("backgrounds/bg2.png");
	//_galaxy = CCSprite::create("backgrounds/bg_galaxy.png");
	//_spacialanomaly = CCSprite::create("backgrounds/bg_spacialanomaly.png");
	//_spacialanomaly2 = CCSprite::create("backgrounds/bg_spacialanomaly2.png");

	// 3) Determine relative movement speeds for space dust and background
	//CCPoint dustSpeed = ccp(0.1, 0.1);
	CCPoint dustSpeed = ccp(-0.05, 0);
	CCPoint firstLayerSpeed = ccp(-0.02, 0);
	CCPoint bgSpeed = ccp(0.05, 0.05);

	// 4) Add children to CCParallaxNode
	_backgroundNode->addChild(_spacedust1, 1, dustSpeed,
			ccp(0, winSize.height / 2 - 150)); // 2

	_backgroundNode->addChild(_spacedust2, 1, dustSpeed,
			ccp(_spacedust1->getContentSize().width, winSize.height / 2 - 150));

	/*
	 _backgroundNode->addChild(_firstlayerbg1, 0, firstLayerSpeed,
	 ccp(0, winSize.height / 2)); // 2

	 _backgroundNode->addChild(_firstlayerbg2, 0, firstLayerSpeed,
	 ccp(_spacedust1->getContentSize().width, winSize.height / 2));
	 */

	//_backgroundNode->addChild(_galaxy, -1, bgSpeed,
	//ccp(0, winSize.height * 0.7));
	//_backgroundNode->addChild(_planetsunrise, 1, bgSpeed,
	//		//ccp(600, winSize.height * 0));
	//_backgroundNode->addChild(_spacialanomaly, -1, bgSpeed,
	//ccp(900, winSize.height * 0.3));
	//_backgroundNode->addChild(_spacialanomaly2, -1, bgSpeed,
	//ccp(1500, winSize.height * 0.9));
}

CCPoint GameLevel::tileCoordForPosition(CCPoint position) {

	float x = floor(position.x / map->getTileSize().width);
	float levelHeightInPixels = map->getMapSize().height
			* map->getTileSize().height;
	float y = floor(
			(levelHeightInPixels - position.y) / map->getTileSize().height);
	return ccp(x, y);
}

CCRect GameLevel::tileRectFromTileCoords(CCPoint tileCoords) {
	float levelHeightInPixels = map->getMapSize().height
			* map->getTileSize().height;
	CCPoint origin = ccp(tileCoords.x * map->getTileSize().width,
			levelHeightInPixels
					- ((tileCoords.y + 1) * map->getTileSize().height));
	return CCRectMake(origin.x, origin.y, map->getTileSize().width,
			map->getTileSize().height);
}

void GameLevel::reloadGamePlayScene(CCObject *sender) {
	this->removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->replaceScene(
			GameLevel::scene(GameLevel::levelNumber));
}

void GameLevel::gameOver(bool won) {
	CCLOG("Game Over");
	isGameOver = true;
	const char *gameText;

	this->stopAllActions();
	this->unscheduleAllSelectors();
	this->unscheduleUpdate();
	this->removeAllChildren();
	this->removeFromParentAndCleanup(true);
	this->setTouchEnabled(false);

	CCLOG("Reference counter player walking animation %d",
			player->walkAnimation->retainCount());

	if (won == true) {
		gameText = "You Won!";
		CCLOG("Game over you won ");
		//save the game
		PersistenceAux::saveGameData(this->vault, this->shipPartCollected);
		CCDirector::sharedDirector()->replaceScene(LevelWonScene::scene());

		//CCDirector::sharedDirector()->replaceScene(
		//CCTransitionFadeBL::create(2, LevelWonScene::scene()));


	} else {
		gameText = "You have Died!";
		CCLOG("Game over you died ");
		CCDirector::sharedDirector()->replaceScene(LevelFailedScene::scene());
	}

	levelEnemies->removeAllObjects();
	animatedTiles->removeAllObjects();
	_backgroundNode->removeAllChildren();

	levelEnemies->release();
	animatedTiles->release();
	releasedTraps->release();
	collisionEngine->release();
	_backgroundNode->release();
	vault->release();

	CCLOG("player retain count %d", player->retainCount());
}

CCRect CCRectIntersection(CCRect r1, CCRect r2) {

	CCRect intersection;
	intersection = CCRectMake(std::max(r1.getMinX(), r2.getMinX()),
			std::max(r1.getMinY(), r2.getMinY()), 0, 0);
	intersection.size.width = std::min(r1.getMaxX(), r2.getMaxX())
			- intersection.getMinX();
	intersection.size.height = std::min(r1.getMaxY(), r2.getMaxY())
			- intersection.getMinY();

	return intersection;
}

CCArray* GameLevel::getSurroundingTilesAtPosition(CCPoint position,
		CCTMXLayer *layer) {

	CCPoint plPos = tileCoordForPosition(position);
	CCArray *gids = CCArray::create();

	for (int i = 0; i < 9; i++) {
		int c = i % 3;
		int r = (int) (i / 3);
		CCPoint tilePos = ccp(plPos.x + (c - 1), plPos.y + (r - 1));
		// fall into a hole
		if (tilePos.y > (map->getMapSize().height - 1)) {
			this->gameOver(false);
			return NULL;
		}

		int tgid = layer->tileGIDAt(tilePos);

		CCRect tileRect = tileRectFromTileCoords(tilePos);

		CCDictionary *tileDict = CCDictionary::create();

		CCXNumericData *tilePosData = CCXNumericData::create();
		CCXNumericData *tgidData = CCXNumericData::create();
		CCXNumericData *rectOrgXData = CCXNumericData::create();
		CCXNumericData *rectOrgYData = CCXNumericData::create();

		tilePosData->setPoint(tilePos);
		tgidData->setIntValue(tgid);
		rectOrgXData->setFloatValue(tileRect.origin.x);
		rectOrgYData->setFloatValue(tileRect.origin.y);
		tileDict->setObject(tgidData, "gid");
		tileDict->setObject(rectOrgXData, "x");
		tileDict->setObject(rectOrgYData, "y");
		tileDict->setObject(tilePosData, "tilePos");

		gids->addObject(tileDict);
	}

	gids->removeObjectAtIndex(4);
	gids->insertObject(gids->objectAtIndex(2), 6);
	gids->removeObjectAtIndex(2);
	gids->exchangeObjectAtIndex(4, 6);
	gids->exchangeObjectAtIndex(0, 4);

	return gids;
}

void GameLevel::checkForAndResolveCollisions(Player *p) {

	CCArray *tiles = getSurroundingTilesAtPosition(p->getPosition(), walls);

	if (isGameOver) {
		return;
	}

	p->onGround = false;

	for (int tileIndx = 0; tileIndx < tiles->count(); tileIndx++) {

		CCRect pRect = p->collisionBoundingBox();
		CCDictionary *dic = (CCDictionary *) tiles->objectAtIndex(tileIndx);
		CCXNumericData *tgidData = (CCXNumericData *) dic->objectForKey("gid");
		if (tgidData->getIntValue() > 0) {

			CCXNumericData *rectOrgXData = (CCXNumericData *) dic->objectForKey(
					"x");
			CCXNumericData *rectOrgYData = (CCXNumericData *) dic->objectForKey(
					"y");

			CCRect tileRect = CCRectMake(rectOrgXData->getFloatValue(),
					rectOrgYData->getFloatValue(), map->getTileSize().width,
					map->getTileSize().height);

			// the colision is not detected.
			if (p->collisionBoundingBox().intersectsRect(tileRect)) {
				CCRect intersection = CCRectIntersection(pRect, tileRect);
				if (tileIndx == 0) {
					//tile is directly below player

					p->desiredPosition = ccp(p->desiredPosition.x,
							p->desiredPosition.y + intersection.size.height);
					p->velocity = ccp(p->velocity.x, 0.0);

					if (p->mightAsWellJump == true && p->onGround == false) {
						p->backwardMarch = false;
						p->forwardMarch = false;
						p->velocity.x = 0;
						p->stopAllActions();
						p->runAction(p->stopAnimation);
					}

					p->onGround = true;

				} else if (tileIndx == 1) {
					//tile is directly above player
					p->desiredPosition = ccp(p->desiredPosition.x,
							p->desiredPosition.y - intersection.size.height);
					p->velocity = ccp(p->velocity.x, 0.0);
				} else if (tileIndx == 2) {
					//tile is left of player
					p->desiredPosition = ccp(
							p->desiredPosition.x + intersection.size.width,
							p->desiredPosition.y);
					if (p->mightAsWellJump == true) {
					} else {
						p->backwardMarch = false;
						p->velocity.x = 0;
					}
				} else if (tileIndx == 3) {
					//tile is right of player
					p->desiredPosition = ccp(
							p->desiredPosition.x - intersection.size.width,
							p->desiredPosition.y);
					if (p->mightAsWellJump == true) {
					} else {
						p->forwardMarch = false;
						p->velocity.x = 0;
					}
				} else {
					if (intersection.size.width > intersection.size.height) {
						//tile is diagonal, but resolving collision vertially
						if (p->mightAsWellJump == true) {
							p->mightAsWellJump = false;
						} else {
							p->velocity = ccp(p->velocity.x, 0.0); //////Here
						}
						float resolutionHeight;
						if (tileIndx > 5) {
							resolutionHeight = intersection.size.height;

							if (p->mightAsWellJump == true
									&& p->onGround == false) {
								p->backwardMarch = false;
								p->forwardMarch = false;
								p->velocity.x = 0;
								p->stopAllActions();
								p->runAction(p->stopAnimation);
							}
							p->onGround = true;
						} else {
							resolutionHeight = -intersection.size.height;
						}
						p->desiredPosition = ccp(p->desiredPosition.x,
								p->desiredPosition.y + resolutionHeight);

					} else {
						float resolutionWidth;
						if (tileIndx == 6 || tileIndx == 4) {
							resolutionWidth = intersection.size.width;
						} else {
							resolutionWidth = -intersection.size.width;
						}
						p->desiredPosition = ccp(
								p->desiredPosition.x + resolutionWidth,
								p->desiredPosition.y);
					}
				}
			}
		}
	}
	p->setPosition(p->desiredPosition);
}

void GameLevel::checkToStopPlayer(Player *p) {
	if (!this->player->mightAsWellJump) {
		if (p->forwardMarch) {
			if (p->getPosition().x >= stopPosition) {
				p->forwardMarch = false;
				p->backwardMarch = false;
				p->velocity = ccp(0, 0);
				p->stopAllActions();
				p->runAction(p->stopAnimation);
			}
		}
		if (p->backwardMarch) {
			if (p->getPosition().x <= stopPosition) {
				p->forwardMarch = false;
				p->backwardMarch = false;
				p->velocity = ccp(0, 0);
				p->stopAllActions();
				p->runAction(p->stopAnimation);
			}
		}
		if (p->velocity.x == 0) {
			p->stopAllActions();
			p->runAction(p->stopAnimation);
		}
	}

}

void GameLevel::handleHazardCollisions(Player *p) {

	// every position in tiles is a dictionary
	CCArray *tiles = getSurroundingTilesAtPosition(p->getPosition(), hazards);
	CCDictionary *dic = CCDictionary::create();

	CCXNumericData *tgidData = CCXNumericData::create();
	CCXNumericData *rectOrgXData = CCXNumericData::create();
	CCXNumericData *rectOrgYData = CCXNumericData::create();

	for (int i = 0; i < tiles->count(); i++) {
		dic = (CCDictionary *) tiles->objectAtIndex(i);
		rectOrgXData = (CCXNumericData *) dic->objectForKey("x");
		rectOrgYData = (CCXNumericData *) dic->objectForKey("y");
		tgidData = (CCXNumericData *) dic->objectForKey("gid");

		CCRect tileRect = CCRectMake(rectOrgXData->getFloatValue(),
				rectOrgYData->getFloatValue(), map->getTileSize().width,
				map->getTileSize().height);

		CCRect pRect = p->collisionBoundingBox();

		// check if it is realy getIntValue() or why this value is checked.

		if (tgidData->getIntValue() && pRect.intersectsRect(tileRect)) {
			gameOver(false);
		}
	}
}

void GameLevel::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	CCSetIterator it;
	CCTouch* touch;

	for (it = pTouches->begin(); it != pTouches->end(); it++) {
		touch = (CCTouch*) (*it);

		if (touchMoved && this->player->onGround) {
			float deltaXView = actualPosition.x - (winSize.width / 2);
			CCPoint touchLocation = this->convertTouchToNodeSpace(touch);

			CCLog("Player (x) Position %f",this->player->getPosition().x);

			if (touchLocation.x + deltaXView > this->player->getPosition().x + DELTA_X_FOR_MOVE) {
				CCLog("Move Forward %f",touchLocation.x + deltaXView);
				this->player->forwardMarch = true;
				this->player->backwardMarch = false;
				this->player->setFlipX(false);
			} else if (touchLocation.x + deltaXView
					< this->player->getPosition().x) {
				CCLog("Move Backward %f",touchLocation.x + deltaXView - DELTA_X_FOR_MOVE);
				this->player->backwardMarch = true;
				this->player->forwardMarch = false;
				this->player->setFlipX(true);
			}

			this->player->stopAllActions();
			if (deltaYTouch > DELTA_Y_FOR_JUMP) {
				this->player->mightAsWellJump = true;
				this->player->onJump = false;
				this->player->runAction(this->player->jumpAnimation);
			} else {
				this->player->mightAsWellJump = false;
				if (player->walkAnimation->retainCount() > 0) {
					this->player->runAction(this->player->walkAnimation);
				}

			}

			if (deltaYTouch <= DELTA_Y_FOR_JUMP) {

				float deltaXTouch = fabs(beginXTouch - touchLocation.x);

				if (deltaXTouch <= DELTA_X_MOVE_LIMIT) {
					//walk near the end of the touch
					stopPosition = touchLocation.x + deltaXView;
				} else {
					CCLog("Touch limit exceed delta x");
					//stopPosition = touchLocation.x;
					//stopPosition = this->player->getPosition().x + 100;
				}

			}

			deltaYTouch = 0;

			//CCLOG("deltaXTouch %f \n", deltaXTouch);

		}
	}
	touchMoved = false;

}

void GameLevel::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {

	CCSetIterator it;
	CCTouch* touch;

	for (it = pTouches->begin(); it != pTouches->end(); it++) {
		touch = (CCTouch*) (*it);
		CCPoint touchLocation = this->convertTouchToNodeSpace(touch);
		deltaYTouch = touchLocation.y - beginYTouch;
		touchMoved = true;
	}
}

void GameLevel::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {

}

void GameLevel::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	CCSetIterator it;
	CCTouch* touch;
	for (it = pTouches->begin(); it != pTouches->end(); it++) {
		touch = (CCTouch*) (*it);
		CCPoint touchLocation = this->convertTouchToNodeSpace(touch);
		beginYTouch = touchLocation.y;
		beginXTouch = touchLocation.x;
		touchMoved = false;
	}
}

CCArray* GameLevel::fetchTilesFromLayer(CCTMXLayer* layer) {
	CCArray *controlTiles = CCArray::create();
	CCSize layersize = layer->getLayerSize();
	for (int x = 0; x < layersize.width; x++) {
		for (int y = 0; y < layersize.height; y++) {
			unsigned int tmpgid = layer->tileGIDAt(ccp(x, y));
			if (tmpgid != 0) {
				SpecialTiles *specialTile = SpecialTiles::create();
				CCSprite* tile = layer->tileAt(ccp(x, y));
				CCRect box = tile->boundingBox();
				CCPoint boxsize = ccp(box.size.width, box.size.height);
				CCPoint tilePosition = ccpAdd(tile->getPosition(),
						ccpMult(boxsize, 0.5));
				specialTile->setTilePosition(tilePosition);
				specialTile->setTilePosition(tilePosition);
				specialTile->setTileProperties(map->propertiesForGID(tmpgid));
				controlTiles->addObject(specialTile);
				CCLOG("Special Tile Retain counter %d",
						specialTile->retainCount());
				layer->removeTileAt(ccp(x, y));
			}
		}
	}
	return controlTiles;
}

void GameLevel::checkEnemyCollision() {

}

void GameLevel::checkItemCollision() {
	//check collision with coins
	if (animatedTiles->retainCount() > 0) {
		for (int ii = 0; ii < animatedTiles->count(); ii++) {
			if (((AnimatedTile*) animatedTiles->objectAtIndex(ii))->hasCollision
					== true) {
				CCRect tileRect = ((AnimatedTile*) animatedTiles->objectAtIndex(
						ii))->boundingBox();
				CCRect playerRect = this->player->getTextureRect();
				if (this->player->collisionBoundingBox().intersectsRect(
						tileRect) == true) {
					CCLOG("Animated Tile Type %d",
							((AnimatedTile *) animatedTiles->objectAtIndex(ii))->animtype);
					if (((AnimatedTile *) animatedTiles->objectAtIndex(ii))->animtype
							== 4) {
						CCLog("coin collected");
						this->vault->coins = this->vault->coins + 1;
						CCString* coins = CCString::createWithFormat("%d",
								vault->coins);
						coinsValue->setString(coins->getCString());
					}
					if (((AnimatedTile *) animatedTiles->objectAtIndex(ii))->animtype
							== 3) {
						CCLog("ship part collected");
						this->shipPartCollected = true;
						partsValue->setString("Part Collected");
					}

					((AnimatedTile*) animatedTiles->objectAtIndex(ii))->doCollisionWithPlayer();
					animatedTiles->removeObjectAtIndex(ii, true);

				}
			}
		}
	}
	// check colision with traps
	if (releasedTraps->retainCount() > 0) {
		for (int ii = 0; ii < releasedTraps->count(); ii++) {

			CCRect tileRect =
					((Trap*) releasedTraps->objectAtIndex(ii))->boundingBox();
			CCRect playerRect = this->player->getTextureRect();
			if (this->player->collisionBoundingBox().intersectsRect(tileRect)
					== true) {

				Trap *releasedtrap = ((Trap*) releasedTraps->objectAtIndex(ii));
				if (releasedtrap->pickable == true) {
					//((AnimatedTile*) animatedTiles->objectAtIndex(ii))->doCollisionWithPlayer();
					releasedTraps->removeObjectAtIndex(ii, true);
					map->removeChild(releasedtrap, true);
				}
			}
		}
	}

}

void GameLevel::initHud() {

	CCLOG("Init hud");
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *releaseTrap = CCMenuItemImage::create("releaseBnt.png",
			"releaseBnt.png", this,
			menu_selector(GameLevel::releaseTrapCallBack));
	releaseTrap->setPosition(ccp(size.width / 2 - 200, size.height / 2 - 80));

	CCMenu* pMenu = CCMenu::create(releaseTrap, NULL);

	this->addChild(pMenu, 1);

	CCLOG("Hud level");

	/* Level info */
	CCLabelBMFont* levelLabel = CCLabelBMFont::create("0", "fonts/gamefont.fnt",
			size.width * 0.3f);
	levelLabel->setString("Level");
	levelLabel->setPosition(ccp(size.width * 0.08, size.height * 0.95));
	CCLOG("Level number hud %d", GameLevel::levelNumber);
	CCString* level = CCString::createWithFormat("%d", GameLevel::levelNumber);
	levelValue = CCLabelBMFont::create("0", "fonts/gamefont.fnt",
			size.width * 0.3f);
	levelValue->setString(level->getCString());
	levelValue->setPosition(ccp(size.width * 0.12, size.height * 0.915));
	/* Level info */

	/* Coins info */
	CCString* coins = CCString::createWithFormat("%d", vault->coins);
	CCLabelBMFont* coinsLabel = CCLabelBMFont::create("0", "fonts/gamefont.fnt",
			size.width * 0.3f);
	coinsLabel->setString("Coins");
	coinsLabel->setPosition(ccp(size.width * 0.20, size.height * 0.95));
	coinsValue = CCLabelBMFont::create("0", "fonts/gamefont.fnt",
			size.width * 0.3f);
	coinsValue->setString(coins->getCString());
	coinsValue->setPosition(ccp(size.width * 0.24, size.height * 0.915));
	/* Coins info */

	/* Health info */
	CCLabelBMFont* healthLabel = CCLabelBMFont::create("0",
			"fonts/gamefont.fnt", size.width * 0.3f);
	healthLabel->setString("Health");
	healthLabel->setPosition(ccp(size.width * 0.37, size.height * 0.95));
	healthValue = CCLabelBMFont::create("0", "fonts/gamefont.fnt",
			size.width * 0.3f);
	healthValue->setString("100");
	healthValue->setPosition(ccp(size.width * 0.37, size.height * 0.915));
	/* Health info */

	/* Trap info */
	CCLabelBMFont* trapsLabel = CCLabelBMFont::create("0", "fonts/gamefont.fnt",
			size.width * 0.3f);
	trapsLabel->setString("Traps");
	trapsLabel->setPosition(ccp(size.width * 0.52, size.height * 0.95));
	trapsValue = CCLabelBMFont::create("0", "fonts/gamefont.fnt",
			size.width * 0.3f);
	trapsValue->setString("3");
	trapsValue->setPosition(ccp(size.width * 0.52, size.height * 0.915));
	/* Trap info */

	/* Ship part */
	CCLabelBMFont* partsLabel = CCLabelBMFont::create("0", "fonts/gamefont.fnt",
			size.width * 0.3f);
	partsLabel->setString("Ship Parts");
	partsLabel->setPosition(ccp(size.width * 0.65, size.height * 0.95));
	partsValue = CCLabelBMFont::create("0", "fonts/gamefont.fnt",
			size.width * 0.3f);
	partsValue->setString("Not Collected");
	partsValue->setPosition(ccp(size.width * 0.65, size.height * 0.915));
	/*Ship part */

	this->addChild(levelLabel);
	this->addChild(levelValue);
	this->addChild(coinsLabel);
	this->addChild(coinsValue);
	this->addChild(healthLabel);
	this->addChild(healthValue);
	this->addChild(trapsLabel);
	this->addChild(trapsValue);
	this->addChild(partsLabel);
	this->addChild(partsValue);

}

void GameLevel::releaseTrapCallBack(CCObject* pSender) {
	CCLOG("Release Trap");
	if (releasedTraps->count() < vault->traps) {
		Trap *trap = Trap::create();
		trap->initTrap(this->player->getPosition());
		releasedTraps->addObject(trap);
		map->addChild(trap);
		//int avaliableTraps = vault->traps - releasedTraps->count();
		CCString* avaliableTraps = CCString::createWithFormat("%d",
				vault->traps - releasedTraps->count());
		trapsValue->setString(avaliableTraps->getCString());
	}
}

void GameLevel::updateHud() {
	//CCLOG("update hud");
}

void GameLevel::onExit() {
	CCLOG("GameLevel onExit called!!! game level retaincount %d",
			this->retainCount());
}

void GameLevel::menuCloseCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
