#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Player* Player::create()
{
	Player* myNode = new Player();
	if (myNode->init())
	{
		myNode->autorelease();
		return myNode;
	}
	else
	{
		CC_SAFE_DELETE(myNode);
		return nullptr;
	}
	return myNode;
}

bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}

	// Start in center lane (lanes now numbered from zero because we're programmers)
	currentLane = 1;

	gameStarting = false;
	this->scheduleUpdate();

	return true;
}

void Player::update(float deltaTime)
{
}

void Player::setOffscreenPos(Sprite* player)
{
	//laneTwoY = laneTwoY;
	int boundingBoxWidth = player->boundingBox().size.width;
	float x = 0.0f - (0.5f * boundingBoxWidth);
	//float x = 200.0f;
	float y = GameManager::sharedGameManager()->laneY[1];
	player->setPosition(Vec2(x, y));
}

void Player::moveIntoStartPos(Sprite* player)
{
	int currX = player->getPositionX();
	if (gameStarting == false) {
		if (currX < fixedX) {
			//player->setPositionX(currX + 0.5f);
			auto moveTo = MoveTo::create(1.0f, Vec2(fixedX, GameManager::sharedGameManager()->laneY[1])); // Take a second to move into position.
			player->runAction(moveTo);

			gameStarting = true;
		}
	}
}

bool Player::isReady(Sprite* player)
{
	int currX = player->getPositionX();
	if (currX == fixedX) {
		gameStarting = false;

		return true;
	}
	else {
		return false;
	}
}

void Player::moveUpLane(Sprite* player) 
{
	if (currentLane == 0) {
		// Bottom Lane
		currentLane = 1;
	}
	else if (currentLane == 1) {
		// Middle lane
		currentLane = 2;
	}
	auto moveTo = MoveTo::create(0.25f, Vec2(fixedX, GameManager::sharedGameManager()->laneY[currentLane])); // Take half a second to move into position.
	player->runAction(moveTo);
	if (!GameManager::sharedGameManager()->isSoundEffectPlaying){ CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Resources/Audio/logon.wav"); GameManager::sharedGameManager()->isSoundEffectPlaying = true; GameManager::sharedGameManager()->currSFlength = 0.45; }
}

void Player::moveDownLane(Sprite* player)
{
	if (currentLane == 1) {
		// Middle Lane
		currentLane = 0;
	}
	else if (currentLane == 2) {
		// Top Lane
		currentLane = 1;
	}
	auto moveTo = MoveTo::create(0.25f, Vec2(fixedX, GameManager::sharedGameManager()->laneY[currentLane])); // Take half a second to move into position.
	player->runAction(moveTo);
	if (!GameManager::sharedGameManager()->isSoundEffectPlaying){ CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Resources/Audio/logoff.wav"); GameManager::sharedGameManager()->isSoundEffectPlaying = true; GameManager::sharedGameManager()->currSFlength = 0.6; }
}

Player::Player()
{
}
Player::~Player()
{
}