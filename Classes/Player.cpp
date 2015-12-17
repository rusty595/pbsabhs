#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "NoiseManager.h"

using namespace cocos2d;

Player* Player::create(cocos2d::Layer*scene)
{
	Player* myNode = new Player(scene);
	
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

void Player::update(float deltaTime, Sprite* player)
{
	timeSinceLastFrame += deltaTime;
	if (timeSinceLastFrame > 30.0f / GameManager::sharedGameManager()->getPlayerSpeed())
	{
		timeSinceLastFrame = 0;
		currFrame++;
		if (currFrame > 7) currFrame = 0;
		player->setTexture(StringUtils::format("Resources/Sprites/Bob/bodies/bob%d.png", currFrame).c_str());
	}
	arm->setPosition(player->getPositionX()-(28*4), player->getPositionY()+(27*4));
	if (armcurrFrame > 0)
	{
		armtimeSinceLastFrame += deltaTime;
		if (armtimeSinceLastFrame > 30.0f / GameManager::sharedGameManager()->getPlayerSpeed())
		{
			armtimeSinceLastFrame = 0;
			arm->setTexture(StringUtils::format("Resources/Sprites/Bob/heads/sword%d.png", armcurrFrame).c_str());
			armcurrFrame++;
			if (armcurrFrame > 4) armcurrFrame = 0;
		}
	}
}

void Player::startArm() { if (armcurrFrame==0) armcurrFrame++; }

void Player::setArmVisible(bool v) { arm->setVisible(v); }

void Player::setGameStarting(bool b)
{
	gameStarting = b;
}

void Player::setOffscreenPos(Sprite* player)
{
	int boundingBoxWidth = player->getBoundingBox().size.width;
	float x = 0.0f - (0.5f * boundingBoxWidth);
	float y = GameManager::sharedGameManager()->laneY[1];
	player->setPosition(Vec2(x, y));
}

void Player::moveIntoStartPos(Sprite* player)
{
	int currX = player->getPositionX();
	if (gameStarting == false) {
		if (currX < fixedX) {
			//player->setPositionX(currX + 0.5f);
			auto moveTo = MoveTo::create(1.0f, Vec2(fixedX, GameManager::sharedGameManager()->laneY[1]+32)); // Take a second to move into position.
			player->runAction(moveTo);

			setGameStarting(true);
		}
	}
}

bool Player::isReady(Sprite* player)
{
	int currX = player->getPositionX();
	if (currX == fixedX) {
		setGameStarting(false);

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
	auto moveTo = MoveTo::create(0.25f, Vec2(fixedX, GameManager::sharedGameManager()->laneY[currentLane]+32)); // Take half a second to move into position.
	player->runAction(moveTo);
	NoiseManager::sharedNoiseManager()->PlaySFX((char*)"up");
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
	auto moveTo = MoveTo::create(0.25f, Vec2(fixedX, GameManager::sharedGameManager()->laneY[currentLane]+32)); // Take half a second to move into position.
	player->runAction(moveTo);
	NoiseManager::sharedNoiseManager()->PlaySFX((char*)"dn");
}

Player::Player(cocos2d::Layer*scene)
{
	arm = (Sprite*)cocos2d::CSLoader::createNode("Dog.csb")->getChildByName("Head");
	addChild(arm);
	arm->setPosition(2000, 0);
	arm->setTexture(StringUtils::format("Resources/Sprites/Bob/heads/sword%d.png", armcurrFrame).c_str());
}
Player::~Player()
{
}
