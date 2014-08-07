/*
 * CCXNumericData.cpp
 *
 *  Created on: May 3, 2013
 *      Author: vntraal
 */

#include "CCXNumericData.h"

CCXNumericData::~CCXNumericData() {
	//CCLOG("CCXNumericData Desconstructor");
}

CCXNumericData* CCXNumericData::create() {
	//CCLOG("Create CCXNumericData");
	CCXNumericData *ndata = new CCXNumericData();
	if (ndata) {
		ndata->autorelease();
		return ndata;
	}
	CC_SAFE_DELETE(ndata);
	return NULL;
}

void CCXNumericData::setPoint(CCPoint pnt) {
	point = pnt;
}

CCPoint CCXNumericData::getPoint() {
	return point;
}

void CCXNumericData::setFloatValue(float value) {
	floatValue = value;
}

float CCXNumericData::getFloatValue() {
	return floatValue;
}

void CCXNumericData::setIntValue(int value) {

	intValue = value;
}

int CCXNumericData::getIntValue() {
	return intValue;
}

