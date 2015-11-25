#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ScoreManager
{
private:
	ScoreManager();
	static ScoreManager* instance;

	// score
	int score;
	int highScore;

	// Methods
	void setHighscore(int highScore);
	void storeHighscoreToFile(int highScore);
	int getHighscoreFromFile();
public:
	~ScoreManager();
	static ScoreManager* sharedScoreManager();

	void addToScore(int point);
	void subtractFromScore(int point);
	int getScore();
	void resetScore();

	void compareScoreToHighscore();
	int getHighscore();
};
