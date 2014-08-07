/*
 * LoadAnimTiles.cpp
 *
 *  Created on: 04/09/2013
 *      Author: munhra
 */

#include "LoadAnimTiles.h"
#include "AnimatedTile.h"
#include "cocos2d.h"
#include "util/SpecialTiles.h"

LoadAnimTiles::LoadAnimTiles() {
	// TODO Auto-generated constructor stub

}

LoadAnimTiles::~LoadAnimTiles() {
	// TODO Auto-generated destructor stub
}

CCArray* LoadAnimTiles::getAnimTilesFromLayer(CCTMXTiledMap *tilemap) {

	CCTMXLayer* layer = tilemap->layerNamed("animated");

	CCSize layersize = layer->getLayerSize();

	CCLOG("%s \n", "getWallAnimatedTiles");
	CCArray *animTilesArray = CCArray::create();

	for (int x = 0; x < layersize.width; x++) {
		for (int y = 0; y < layersize.height; y++) {
			unsigned int tmpgid = layer->tileGIDAt(ccp(x, y));
			if (tmpgid != 0) {
				CCSprite* tile = layer->tileAt(ccp(x, y));
				CCRect box = tile->boundingBox();
				CCPoint boxsize = ccp(box.size.width, box.size.height);
				CCPoint tilePosition = ccpAdd(tile->getPosition(),
						ccpMult(boxsize, 0.5));
				layer->removeTileAt(ccp(x, y));

				// create the animated tile directly
				CCDictionary* tileProperties = tilemap->propertiesForGID(
						tmpgid);

				CCString* tileFrameName =
						(CCString*) tileProperties->objectForKey("name");

				CCString* tileCollision =
						(CCString*) tileProperties->objectForKey("collision");

				bool collision;
				if (tileCollision->intValue() == 1) {
					collision = true;
				} else {
					collision = false;
				}

				CCLOG("Tile anim frame %s \n", tileFrameName->getCString());
				CCLOG("Tile Anim Position x %f \n", tilePosition.x);

				AnimatedTile* animatedTile = AnimatedTile::create(
						tileFrameName);

				int animtype =
						((CCString*) tileProperties->objectForKey("type"))->intValue();

				CCLOG("Animated Tile Type %d", animtype);

				animatedTile->initAnimatedTile(tilePosition,
						tileFrameName->getCString(), collision , animtype, tilemap);
				CCLOG("%s \n", "Add tiles to tiles array");
				animTilesArray->addObject(animatedTile);

			}
		}
	}

	return animTilesArray;
}

