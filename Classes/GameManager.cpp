#include "GameManager.h"

GameManager* GameManager::instance = NULL;

GameManager::GameManager()
{
	isGameLive = false;
	secondCheck = 0.0f;
	playerSpeed = 0.0f;
	skyMultiplier = 2.0f;
	mountainMultiplier = 40.0f;
	treeMultiplier = 400.0f;

	setHighscore(getHighscoreFromFile());
	resetScore();
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

void GameManager::incrementSpeed(float delta)
{
	// Every 5 seconds, increment speed by 0.1
	if (secondCheck + delta > 5.0f) {
		secondCheck = 0;
		playerSpeed += 0.1f;
	}
	else {
		secondCheck += delta;
	}
}

void GameManager::setPlayerRunning(bool running)
{
	if (running == false) {
		resetSpeeds();
	}
	else if (running == true) {
		playerSpeed = 1.0f;
	}
}

bool GameManager::getPlayerRunning()
{
	if (playerSpeed >= 1.0f) {
		return true;
	}
	else {
		return false;
	}
}

float GameManager::getSkySpeed()
{
	// The sky will always be moving in the same direction as bob runs
	// Sky starts moving in the opposite direction when Bob is fast enough
	float speed = 4.0f - (playerSpeed * skyMultiplier);

	return speed;
}

float GameManager::getMountainSpeed()
{
	float speed = -1 * (playerSpeed * mountainMultiplier);

	return speed;
}

float GameManager::getTreeSpeed()
{
	float speed = -1 * (playerSpeed * treeMultiplier);

	return speed;
}

float GameManager::getIncomingSpeed()
{
	float speed = -1 * playerSpeed;

	return speed;
}

void GameManager::resetSpeeds()
{
	secondCheck = 0;
	playerSpeed = 0.0f;
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

	return highScore;
}

GameManager::~GameManager()
{
}