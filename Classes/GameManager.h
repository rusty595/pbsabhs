#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameManager
{
private:
	GameManager();
	static GameManager* instance;

	bool isGameLive;

	// score
	int score;
	int highScore;

	// Methods
	void setHighscore(int highScore);
	void storeHighscoreToFile(int highScore);
	int getHighscoreFromFile();
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

	void addToScore(int point);
	void subtractFromScore(int point);
	int getScore();
	void resetScore();

	void compareScoreToHighscore();
	int getHighscore();
};
