/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "EventHandler.h"
#include "scenes/MenuScene.h"
#include "StoreBridge/Includes.h"

void EventHandler::billingSupported() {
	
}
void EventHandler::billingNotSupported() {
	
}
void EventHandler::closingStore() {
	
}
void EventHandler::currencyBalanceChanged(string &itemId, int balance, int amountAdded) {
	 __android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "currencyBalanceChanged");
	MenuScene::setCurrencyBalanceLabel();
}
void EventHandler::goodBalanceChanged(string &itemId, int balance, int amountAdded) {

}
void EventHandler::goodEquipped(string& itemId) {
	
}
void EventHandler::goodUnequipped(string& itemId) {
	
}
void EventHandler::goodUpgrade(string& itemId, string& upgradeItemId) {
	
}
void EventHandler::itemPurchased(string& itemId) {
	
}
void EventHandler::itemPurchaseStarted() {
	
}
void EventHandler::openingStore() {
	__android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "openingStore");
}
void EventHandler::marketPurchaseCancelled(string& itemId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    __android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "Market purchase cancelled by user!");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    iOSHelper::LogMessage("Market purchase cancelled by user!");
#endif
}
void EventHandler::marketPurchase(string& itemId) {
	__android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "marketPurchase");
}
void EventHandler::marketPurchaseStarted(string& itemId) {
	__android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "marketPurchaseStarted");
}
void EventHandler::marketRefund(string& itemId) {
	__android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "marketRefund");
}
void EventHandler::restoreTransactions(bool success) {
	__android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "restoreTransactions");
}
void EventHandler::restoreTransactionsStarted() {
	__android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "restoreTransactionsStarted");
}
void EventHandler::unexpectedErrorInStore() {
	__android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "unexpectedErrorInStore");
}




