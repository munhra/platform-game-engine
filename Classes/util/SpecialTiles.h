/*
 * SpecialTiles.h
 *
 *  Created on: 30/08/2013
 *      Author: munhra
 */

#ifndef SPECIALTILES_H_
#define SPECIALTILES_H_

#include "cocos2d.h"

using namespace cocos2d;

class SpecialTiles: public CCObject {
public:
	virtual ~SpecialTiles();

	static SpecialTiles* create();

	CCDictionary* getTileProperties();
	void setTileProperties(CCDictionary* tileProperties);

	CCPoint getTilePosition();
	void setTilePosition(CCPoint tileSprite);

private:
	CCPoint tilePosition;
	CCDictionary* tileProperties;

};

#endif /* SPECIALTILES_H_ */
