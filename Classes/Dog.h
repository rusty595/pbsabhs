#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Dog : public cocos2d::Node
{
private:
	// Lane data
	int currentLane;
	float laneOneY;
	float laneTwoY;
	float laneThreeY;
	float fixedX;

	// Cocos sprites
	cocos2d::Sprite* body;//= cocos2d::Sprite::create("Dogs\heads\dachs.png");
	cocos2d::Sprite* head;//= cocos2d::Sprite::create("Dogs\bodies\dachs.png");

	// Game data
	bool beheaded;
public:
	Dog();
	~Dog();

	virtual bool init() override;
	static Dog* create();

	void update(float);
};
