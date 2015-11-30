#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ScoreManager
{
private:
	ScoreManager();
	static ScoreManager* instance;

	// score
	float score;
	int highScore;

	// Methods
	void setHighscore(int highScore);
	void storeHighscoreToFile(int highScore);
	int getHighscoreFromFile();
public:
	~ScoreManager();
	static ScoreManager* sharedScoreManager();

	void addToScore(float point);
	void subtractFromScore(float point);
	float getScore();
	void resetScore();

	void compareScoreToHighscore();
	int getHighscore();
};
