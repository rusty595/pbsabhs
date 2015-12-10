#include "NoiseManager.h"

NoiseManager* NoiseManager::instance = NULL;

NoiseManager* NoiseManager::sharedNoiseManager()
{
	if (instance == NULL)
	{
		instance = new NoiseManager();
	}

	return instance;
}

void NoiseManager::updateSFXState(float delta)
{
	if (isSoundEffectPlaying) timeSinceEffectStart += delta;
	if (timeSinceEffectStart > currSFlength) { isSoundEffectPlaying = false; timeSinceEffectStart = 0.0f; }
}

void NoiseManager::Play(char * noise)
{
	/*
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((cocos2d::StringUtils::format("Resources/Audio/%s.wav", noise)).c_str());
	else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((cocos2d::StringUtils::format("Resources/Audio/%s.wav", noise)).c_str());
	else if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((cocos2d::StringUtils::format("Resources/Audio/%s.wav", noise)).c_str());
	else */
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((cocos2d::StringUtils::format("Resources/Audio/%s.wav", noise)).c_str()); //allegedly wav works everywhere (except near David)
}
