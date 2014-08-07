/*
 * CCParallaxNodeExtras.cpp
 *
 *  Created on: 19/08/2013
 *      Author: munhra
 */

#include "CCParallaxNodeExtras.h"

// Hack to access CCPointObject (which is not a public class)
class CCPointObject: CCObject {
	CC_SYNTHESIZE(CCPoint, m_tRatio, Ratio)
	CC_SYNTHESIZE(CCPoint, m_tOffset, Offset)
	CC_SYNTHESIZE(CCNode *, m_pChild, Child)
};

CCParallaxNodeExtras::~CCParallaxNodeExtras(){
	CCLOG("Destruct paralax node ");
}


// Need to provide a constructor
CCParallaxNodeExtras::CCParallaxNodeExtras() {
	//CCParallaxNode(); // call parent constructor
}

CCParallaxNodeExtras * CCParallaxNodeExtras::node() {
	CCLOG("Create parallax node");
	CCParallaxNodeExtras *pnode = new CCParallaxNodeExtras();
	if (pnode) {
		pnode->autorelease();
		return pnode;
	}
	CC_SAFE_DELETE(pnode);
	return NULL;
}

void CCParallaxNodeExtras::incrementOffset(CCPoint offset, CCNode* node) {
	for (unsigned int i = 0; i < m_pParallaxArray->num; i++) {
		CCPointObject *point = (CCPointObject *) m_pParallaxArray->arr[i];
		CCNode * curNode = point->getChild();
		if (curNode->isEqual(node)) {
			point->setOffset(ccpAdd(point->getOffset(), offset));
			break;
		}
	}
}
