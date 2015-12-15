#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Player : public cocos2d::Node
{
private:
	// Set the x coord that Bob can never run past
	const float fixedX = 217.0f;
	// Player Data
	cocos2d::Vec2		pos;
	// Animation data
	float timeSinceLastFrame;
	int currFrame=0;
	//Arm data
	float armtimeSinceLastFrame;
	int armcurrFrame = 0;
	cocos2d::Sprite* arm;
	// Game data
	bool gameStarting;
public:
	// Lane data
	int currentLane;

	Player(cocos2d::Layer*scene);
	~Player();

	virtual bool init() override;
	static Player* create(cocos2d::Layer*scene);

	void update(float,cocos2d::Sprite* player);

	void setGameStarting(bool b);
	void setOffscreenPos(cocos2d::Sprite* player);
	void moveIntoStartPos(cocos2d::Sprite* player);
	bool isReady(cocos2d::Sprite* player);

	void moveUpLane(cocos2d::Sprite* player);
	void moveDownLane(cocos2d::Sprite* player);

	void startArm();
};
