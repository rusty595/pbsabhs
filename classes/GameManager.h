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

	//Methods
	void setHighscore(int highScore);
	void storeHighscoreToFile(int highScore);
	int getHighscoreFromFile();
public:
	~GameManager();
	static GameManager* sharedGameManager();

	void setIsGameLive(bool);
	bool getIsGameLive();

	void addToScore(int point);
	void subtractFromScore(int point);
	int getScore();
	void resetScore();

	void compareScoreToHighscore();
	int getHighscore();
};

