#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

Player::Player()
{
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
	//player_skin->setPosition(Vec2(0.0f - (0.5 * player_skin->_contentSize.width)))
}

Player::~Player()
{
}
