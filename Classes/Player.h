#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Player : public cocos2d::Node
{
private:
	// Lane data
	int currentLane;
	float fixedX;

	// Player Data
	cocos2d::Vec2		pos;

	// Game data
	bool gameStarting;
public:
	Player();
	~Player();

	virtual bool init() override;
	static Player* create();

	void update(float);

	void setOffscreenPos(cocos2d::Sprite* player);
	void moveIntoStartPos(cocos2d::Sprite* player);
	bool isReady(cocos2d::Sprite* player);

	void moveUpLane(cocos2d::Sprite* player);
	void moveDownLane(cocos2d::Sprite* player);
};
