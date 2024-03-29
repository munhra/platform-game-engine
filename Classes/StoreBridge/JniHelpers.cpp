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

#include "JniHelpers.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath)
					throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&){
    cocos2d::JniMethodInfo minfo;
    __android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "try open");
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "()V"); 
    
    if (!isHave) {
        //do nothing
    } else {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, bool arg0) 
					throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&){
    cocos2d::JniMethodInfo minfo;
    
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Z)V"); 
    
    if (!isHave) {
        //do nothing
    } else {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, arg0);
    }
}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, const char* arg0) 
					throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&) {
    cocos2d::JniMethodInfo minfo;
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo, classPath, methodName, "(Ljava/lang/String;)V"); 
    
    if (!isHave) {
        //do nothing
    	__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "do not!");
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
		
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);		
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION 1");
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
			
			vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/NotEnoughGoodsException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought NotEnoughGoodsException!"); 

				throw cocos2dx_NotEnoughGoodsException();
			}
			
			vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/InsufficientFundsException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought InsufficientFundsException!"); 

				throw cocos2dx_InsufficientFundsException();
			}
		}
    }
}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, const char* arg0, int arg1)
					throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&){
	cocos2d::JniMethodInfo minfo;
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo, classPath, methodName, "(Ljava/lang/String;I)V"); 

    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0, arg1);

		minfo.env->DeleteLocalRef(stringArg0);		

		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION 2");
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();

			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}

			vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/NotEnoughGoodsException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought NotEnoughGoodsException!"); 

				throw cocos2dx_NotEnoughGoodsException();
			}

			vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/InsufficientFundsException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought InsufficientFundsException!"); 

				throw cocos2dx_InsufficientFundsException();
			}
		}
    }
}

int JniHelpers::jniCommonIntCall(const char* methodName, const char* classPath, const char* arg0) 
					throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&){
    cocos2d::JniMethodInfo minfo;
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;)I"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
		
        jint ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION 3");
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
		}
		
		return (int)ret;
    }
	
	return 0;
}

int JniHelpers::jniCommonIntCall(const char* methodName, const char* classPath, const char* arg0, int arg1) 
					throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&){
    cocos2d::JniMethodInfo minfo;
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;I)I"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
		
        jint ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, arg1);
		
		minfo.env->DeleteLocalRef(stringArg0);
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION 4");
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
		}
		
		return (int)ret;
    }
	
	return 0;
}

int JniHelpers::jniCommonIntCall(const char* methodName, const char* classPath, const char* arg0, const char* arg1) 
					throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&){
    cocos2d::JniMethodInfo minfo;
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;Ljava/lang/String;)I"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
		jstring stringArg1 = minfo.env->NewStringUTF(arg1);
		
        jint ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, stringArg1);
		
		minfo.env->DeleteLocalRef(stringArg0);
		minfo.env->DeleteLocalRef(stringArg1);
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION 5");
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
		}
		
		return (int)ret;
    }
	
	return 0;
}

string JniHelpers::jniCommonStringCall(const char* methodName, const char* classPath, const char* arg0) 
					throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&){
    cocos2d::JniMethodInfo minfo;
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;)Ljava/lang/String;"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
		
        jstring retString = (jstring) minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);
		
		const char *nativeString = minfo.env->GetStringUTFChars(retString, 0);
		string ret(nativeString);
		minfo.env->ReleaseStringUTFChars(retString, nativeString);
		   
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION 6");
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
		}
		
		return ret;
    }
	
	return NULL;
}

double JniHelpers::jniCommonDoubleCall(const char* methodName, const char* classPath, const char* arg0) 
					throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&){
    cocos2d::JniMethodInfo minfo;
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;)D"); 
    
    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
		
        jdouble ret = minfo.env->CallStaticDoubleMethod(minfo.classID, minfo.methodID, stringArg0);
		
		minfo.env->DeleteLocalRef(stringArg0);
		
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION 7");
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
			
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
		}
		
		return (double)ret;
    }
	
	return 0;	
}

bool JniHelpers::jniCommonBoolCall(const char* methodName, const char* classPath, const char* arg0) 
	throw(cocos2dx_VirtualItemNotFoundException&, cocos2dx_NotEnoughGoodsException&, cocos2dx_InsufficientFundsException&) {
	
    cocos2d::JniMethodInfo minfo;

    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;)Z"); 

    if (!isHave) {
        //do nothing
    } else {
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
	
        jdouble ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID, stringArg0);
	
		minfo.env->DeleteLocalRef(stringArg0);
	
		if(minfo.env->ExceptionCheck() == JNI_TRUE ) {
			__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "HAS EXCEPTION 8");
			jthrowable exceptionObj = minfo.env->ExceptionOccurred();
			minfo.env->ExceptionClear();
		
			jclass vinfEx = cocos2d::JniHelper::getClassID("com/soomla/store/exceptions/VirtualItemNotFoundException", minfo.env);
			if (minfo.env->IsInstanceOf(exceptionObj, vinfEx)) {
				__android_log_write(ANDROID_LOG_DEBUG, "SOOMLA JNI", "Cought VirtualItemNotFoundException!"); 

				throw cocos2dx_VirtualItemNotFoundException();
			}
		}
	
		return (double)ret;
    }

	return 0;
		
}

