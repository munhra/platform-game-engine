/*
 * LoadAnimTiles.h
 *
 *  Created on: 04/09/2013
 *      Author: munhra
 */

#ifndef LOADANIMTILES_H_
#define LOADANIMTILES_H_

#include "cocos2d.h"

using namespace cocos2d;

class LoadAnimTiles {
public:
	LoadAnimTiles();
	virtual ~LoadAnimTiles();
	static CCArray* getAnimTilesFromLayer(CCTMXTiledMap *tilemap);

};

#endif /* LOADANIMTILES_H_ */
