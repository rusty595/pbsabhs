#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "editor-support/cocostudio/cccomaudio.h"
#include <stdio.h>
#include <iostream>

class NoiseManager
{
	static NoiseManager* instance;

	// SFX
	float timeSinceEffectStart = 0.0f;
	bool isSoundEffectPlaying = false;
	float currSFlength;

public:
	void updateSFXState(float delta);
	void PlaySFX(char*);
	void PlayBGM(char*);
	void PauseBGM();
	void PauseSFX();
	void ResumeBGM();

	NoiseManager(){};
	~NoiseManager(){};
	static NoiseManager* sharedNoiseManager();
};