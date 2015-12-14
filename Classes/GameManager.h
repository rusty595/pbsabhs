#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameManager
{
private:
	GameManager();
	static GameManager* instance;

	bool isGameLive;
	bool isGamePaused;

	// Speed
	float	secondCheck;
	float	playerSpeed;
	float	storedPlayerSpeed;
	float	skyMultiplier;
	float	mountainMultiplier;
	float	treeMultiplier;

public:
	float laneY[3];
	int health = 3;

	~GameManager();
	static GameManager* sharedGameManager();

	void setIsGameLive(bool);
	bool getIsGameLive();
	void setIsGamePaused(bool);
	bool getIsGamePaused();

	void incrementSpeed(float delta);
	void setPlayerRunning(bool running);
	bool getPlayerRunning();
	float getPlayerSpeed();
	float getSkySpeed();
	float getMountainSpeed();
	float getTreeSpeed();
	float getIncomingSpeed();

	void resetSpeeds();
	void resetHealth(){ health = 3; }
};
