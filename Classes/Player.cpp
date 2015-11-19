#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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

	// Set lane Y values
	laneOneY = 10.8f;
	laneTwoY = laneOneY + (laneOneY * 2);
	laneThreeY = laneOneY + (laneOneY * 4);

	// Start in center lane
	currentLane = 2;

	auto rootNode = CSLoader::createNode("Player.csb");
	addChild(rootNode);

	// Initialise sprite
	player_skin = (Sprite*)rootNode->getChildByName("Player_Skin_1");

	// Start position is off screen
	player_skin->setPosition(Vec2(0.0f - (0.5 * player_skin->boundingBox().size.width), laneTwoY));

	return true;
}

void Player::update(float)
{

}

void Player::moveUpLane() 
{

}

void Player::moveDownLane()
{

}

Player::Player()
{
}
Player::~Player()
{
}
