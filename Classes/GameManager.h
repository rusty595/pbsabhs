#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameManager
{
private:
	GameManager();
	static GameManager* instance;

	bool isGameLive;

	// Methods
	void resetSpeeds();

	// Speed
	float	secondCheck;
	float	playerSpeed;
	float	skyMultiplier;
	float	mountainMultiplier;
	float	treeMultiplier;
public:
	~GameManager();
	static GameManager* sharedGameManager();

	void setIsGameLive(bool);
	bool getIsGameLive();

	void incrementSpeed(float delta);
	void setPlayerRunning(bool running);
	bool getPlayerRunning();
	float getSkySpeed();
	float getMountainSpeed();
	float getTreeSpeed();
	float getIncomingSpeed();
};
