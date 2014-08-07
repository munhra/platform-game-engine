#include "AppDelegate.h"

#include "cocos2d.h"
//#include "HelloWorldScene.h"
#include "scenes/GameLevelLayer.h"
#include "scenes/SplScr1Scene.h"
#include "StoreBridge/cocos2dx_StoreController.h"
#include "StoreBridge/cocos2dx_EventHandlers.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
	handler = new EventHandler();
}

AppDelegate::~AppDelegate()
{
	CCLOG("AppDelegate set handler");
	cocos2dx_EventHandlers::getInstance()->removeHandler(handler);
	delete handler;
}

bool AppDelegate::applicationDidFinishLaunching()
{

	/**
	 * The initialization of StoreController. This is the first and ONLY time it's initialized.
	 **/
	//handler = new EventHandler();
	//CCLOG("applicationDidFinishLaunching");
	//cocos2dx_EventHandlers::getInstance()->removeHandler(handler);

	//cocos2dx_StoreController::initialize("RobotRunnerSecret");
	cocos2dx_EventHandlers::getInstance()->addHandler(handler);

	// initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pEGLView->setDesignResolutionSize(1280,
    		720, kResolutionExactFit);

    //Load all spritesheets
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
			"sprites/animatedTiles.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
			"sprites/enemySheet.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
				"sprites/historySheet.plist");


    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0/60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = GameLevel::scene();
    CCScene *pScene = SplScr1Scene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
    //CCDirector::sharedDirector()->end();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
