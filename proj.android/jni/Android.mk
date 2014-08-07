LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/util/CCXNumericData.cpp \
                   ../../Classes/scenes/GameLevelLayer.cpp \
                   ../../Classes/scenes/SplScr1Scene.cpp \
                   ../../Classes/scenes/SplScr2Scene.cpp \
                   ../../Classes/scenes/MenuScene.cpp \
                   ../../Classes/scenes/LevelFailedScene.cpp \
                   ../../Classes/scenes/LevelWonScene.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/util/CollisionEngine.cpp \
                   ../../Classes/util/PersistenceAux.cpp \
                   ../../Classes/enemies/MeeleEnemy.cpp \
                   ../../Classes/util/CCParallaxNodeExtras.cpp \
                   ../../Classes/StoreBridge/JniHelpers.cpp \
                   ../../Classes/StoreBridge/cocos2dx_StoreController.cpp \
                   ../../Classes/StoreBridge/cocos2dx_StoreInventory.cpp \
				   ../../Classes/StoreBridge/cocos2dx_EventHandlers.cpp \
                   ../../Classes/StoreBridge/cocos2dx_StoreInfo.cpp \
                   ../../Classes/StoreBridge/com_soomla_cocos2dx_store_EventHandlerBridge.cpp \
                   ../../Classes/util/SpecialTiles.cpp \
                   ../../Classes/util/StarsField.cpp \
                   ../../Classes/enemies/LoadLevelEnemies.cpp \
                   ../../Classes/animatedtiles/LoadAnimTiles.cpp \
                   ../../Classes/animatedtiles/AnimatedTile.cpp \
                   ../../Classes/EventHandler.cpp \
                   ../../Classes/util/HudDataSource.cpp \
                   ../../Classes/scenes/LevelSelectionScene.cpp \
                   ../../Classes/scenes/HistoryScr.cpp \
                   ../../Classes/scenes/HistoryScr2.cpp \
                   ../../Classes/scenes/HistoryScr3.cpp \
                   ../../Classes/scenes/HistoryBasicLayer.cpp \
                   ../../Classes/util/PlayerVault.cpp \
                   ../../Classes/Trap.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
