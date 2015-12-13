#include "GameManager.h"

GameManager* GameManager::instance = NULL;

GameManager::GameManager()
{
	isGameLive = false;
	isGamePaused = false;
	secondCheck = 0.0f;
	playerSpeed = 0.0f;
	skyMultiplier = 0.002f;
	mountainMultiplier = 0.04f;
	treeMultiplier = 0.4f;
	laneY[0] = 108.0f;
	laneY[1] = laneY[0] + (laneY[0] * 2);
	laneY[2] = laneY[0] + (laneY[0] * 4);
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

void GameManager::setIsGamePaused(bool paused)
{
	isGamePaused = paused;
}

bool GameManager::getIsGamePaused()
{
	return isGamePaused;
}

void GameManager::incrementSpeed(float delta)
{
	// Every 5 seconds, increment speed by 0.1
	if (secondCheck + delta > 5.0f) {
		secondCheck = 0;
		playerSpeed += 100.0f;
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
		playerSpeed = 1000.0f;
	}
}

bool GameManager::getPlayerRunning()
{
	if (playerSpeed >= 1000.0f) {
		return true;
	}
	else {
		return false;
	}
}

float GameManager::getPlayerSpeed()
{
	return playerSpeed;
}

float GameManager::getSkySpeed()
{
	// The sky will always be moving in the same direction as bob runs
	// Sky starts moving in the opposite direction when Bob is fast enough
	float speed;
	
	if (isGamePaused == false) {
		speed = 4.0f - (playerSpeed * skyMultiplier);
	}
	else if (isGamePaused == true) {
		speed = 0.0f;
	}
	return speed;
}

float GameManager::getMountainSpeed()
{
	float speed;

	if (isGamePaused == false) {
		speed = -1 * (playerSpeed * mountainMultiplier);
	}
	else if (isGamePaused == true) {
		speed = 0.0f;
	}

	return speed;
}

float GameManager::getTreeSpeed()
{
	float speed;

	if (isGamePaused == false) {
		speed = -1 * (playerSpeed * treeMultiplier);
	}
	else if (isGamePaused == true) {
		speed = 0.0f;
	}

	return speed;
}

float GameManager::getIncomingSpeed()
{
	float speed;

	if (isGamePaused == false) {
		speed = -1 * playerSpeed;
	}
	else if (isGamePaused == true) {
		speed = 0.0f;
	}

	return speed;
}

void addToHealth(int health)
{
	//TODO
}

void subtractFromHealth(int health)
{
	//TODO
}

void GameManager::resetSpeeds()
{
	secondCheck = 0;
	playerSpeed = 0.0f;
}

GameManager::~GameManager()
{
}