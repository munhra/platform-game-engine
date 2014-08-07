/*
 * PlayerVault.cpp
 *
 *  Created on: 12/08/2013
 *      Author: munhra
 */

#include "PlayerVault.h"


PlayerVault* PlayerVault::create(){
	CCLOG("Create Vault");
	PlayerVault *vault = new PlayerVault();
	if (vault) {
		vault->autorelease();
		return vault;
	}
	CC_SAFE_DELETE(vault);
	return NULL;
}


PlayerVault::~PlayerVault(){
	CCLOG("Destruct Player Vault");
}
