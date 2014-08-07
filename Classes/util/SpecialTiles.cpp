/*
 * SpecialTiles.cpp
 *
 *  Created on: 30/08/2013
 *      Author: munhra
 */

#include "SpecialTiles.h"

SpecialTiles* SpecialTiles::create(){
	CCLOG("Create Special Tile");
	SpecialTiles *spectile = new SpecialTiles();
	if (spectile) {
		spectile->autorelease();
		return spectile;
	}
	CC_SAFE_DELETE(spectile);
	return NULL;
}

SpecialTiles::~SpecialTiles() {
	CCLOG("Destruct especial Tile");
}

CCDictionary* SpecialTiles::getTileProperties(){
	return this->tileProperties;
}

void SpecialTiles::setTileProperties(CCDictionary* tileProperties){
	this->tileProperties = tileProperties;
}

CCPoint SpecialTiles::getTilePosition(){
	return this->tilePosition;
}

void SpecialTiles::setTilePosition(CCPoint tilePosition){
	this->tilePosition = tilePosition;
}


