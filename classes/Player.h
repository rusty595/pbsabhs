#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Player : public cocos2d::Node
{
private:
	// Lane data
	int currentLane;
	float laneOneY;
	float laneTwoY;
	float laneThreeY;

	// Player Data
	cocos2d::Vec2		pos;
	cocos2d::Sprite*	player_skin;
public:
	Player();
	~Player();

	virtual bool init() override;
	static Player* create();

	void update(float);

	void moveUpLane();
	void moveDownLane();
};

