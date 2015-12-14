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

void NoiseManager::PlaySFX(char * noise)
{
	
	//if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((cocos2d::StringUtils::format("Resources/Audio/%s.wav", noise)).c_str());
	//else if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((cocos2d::StringUtils::format("Resources/Audio/%s.wav", noise)).c_str());
	//else if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((cocos2d::StringUtils::format("Resources/Audio/%s.wav", noise)).c_str());
	//else 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((cocos2d::StringUtils::format("Resources/Audio/%s.wav", noise)).c_str()); //allegedly wav works everywhere (except Windows 10)
}

void NoiseManager::PlayBGM(char * noise)
{
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		if (FILE *file = fopen((cocos2d::StringUtils::format("%s.mid", noise)).c_str(), "rb"))
		{
			fclose(file);
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic((cocos2d::StringUtils::format("%s.mid", noise)).c_str());
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic((cocos2d::StringUtils::format("%s.mid", noise)).c_str(), true);
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic((cocos2d::StringUtils::format("%s.mp3", noise)).c_str());
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic((cocos2d::StringUtils::format("%s.mp3", noise)).c_str(), true);
		}
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic((cocos2d::StringUtils::format("%s.mp3", noise)).c_str());
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic((cocos2d::StringUtils::format("%s.mp3", noise)).c_str(), true);
	}
}

void NoiseManager::PauseBGM()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void NoiseManager::PauseSFX()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void NoiseManager::ResumeBGM()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}