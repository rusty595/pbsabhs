#include "ScoreManager.h"

ScoreManager* ScoreManager::instance = NULL;

ScoreManager::ScoreManager()
{
	setHighscore(getHighscoreFromFile());
	resetScore();
}

ScoreManager* ScoreManager::sharedScoreManager()
{
	if (instance == NULL)
	{
		instance = new ScoreManager();
	}

	return instance;
}

void ScoreManager::addToScore(float point)
{
	score += point;
}

void ScoreManager::subtractFromScore(float point)
{
	score -= point;
}

float ScoreManager::getScore()
{
	return score;
}

void ScoreManager::resetScore()
{
	score = 0;
}

void ScoreManager::compareScoreToHighscore()
{
	if (score > highScore)
	{
		setHighscore(score);
	}
}

void ScoreManager::setHighscore(int newScore)
{
	highScore = newScore;
	storeHighscoreToFile(highScore);
}

int ScoreManager::getHighscore()
{
	return highScore;
}

void ScoreManager::storeHighscoreToFile(int highScore)
{
	// Insert code to save highscore to file
}

int ScoreManager::getHighscoreFromFile()
{
	// Insert code to get highscore from file

	return highScore;
}

ScoreManager::~ScoreManager()
{
}