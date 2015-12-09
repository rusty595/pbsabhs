#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "editor-support/cocostudio/cccomaudio.h"

class NoiseManager
{
	NoiseManager(){};
	static NoiseManager* instance;

	// SFX
	float timeSinceEffectStart = 0.0f;

public:
	bool isSoundEffectPlaying = false;
	float currSFlength;

	void updateSFXState(float delta);
	void Play(char*);

	~NoiseManager();
	static NoiseManager* sharedNoiseManager();
};