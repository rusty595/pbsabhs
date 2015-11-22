#include "GameManager.h"

GameManager* GameManager::instance = NULL;

GameManager::GameManager()
{
	isGameLive = false;
}

GameManager* GameManager::sharedGameManager()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}

	return instance;
}

void GameManager::setIsGameLive(bool live) 
{
	isGameLive = live;
}

bool GameManager::getIsGameLive()
{
	return isGameLive;
}

void GameManager::addToScore(int point)
{
	score += point;
}

void GameManager::subtractFromScore(int point)
{
	score -= point;
}

int GameManager::getScore()
{
	return score;
}

void GameManager::resetScore()
{
	score = 0;
}

void GameManager::compareScoreToHighscore()
{
	if (score > highScore)
	{
		setHighscore(score);
	}
}

void GameManager::setHighscore(int newScore)
{
	highScore = newScore;
	storeHighscoreToFile(highScore);
}

int GameManager::getHighscore()
{
	return highScore;
}

void GameManager::storeHighscoreToFile(int highScore)
{
	// Insert code to save highscore to file
}

int GameManager::getHighscoreFromFile()
{
	// Insert code to get highscore from file
}

GameManager::~GameManager()
{
}
