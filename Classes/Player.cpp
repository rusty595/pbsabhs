#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"

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

	// Set the x coords that Bob can never run past
	fixedX = 217.0f;

	// Start in center lane
	currentLane = 2;

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
	if (currentLane == 1) {
		// Bottom Lane
		currentLane = 2;
	}
	else if (currentLane == 2) {
		// Middle lane
		currentLane = 3;
	}
	auto moveTo = MoveTo::create(0.25f, Vec2(fixedX, GameManager::sharedGameManager()->laneY[currentLane - 1])); // Take half a second to move into position.
	player->runAction(moveTo);

}

void Player::moveDownLane(Sprite* player)
{
	if (currentLane == 2) {
		// Middle Lane
		currentLane = 1;
	}
	else if (currentLane == 3) {
		// Top Lane
		currentLane = 2;
	}
	auto moveTo = MoveTo::create(0.25f, Vec2(fixedX, GameManager::sharedGameManager()->laneY[currentLane - 1])); // Take half a second to move into position.
	player->runAction(moveTo);
}

Player::Player()
{
}
Player::~Player()
{
}