#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Dog : public cocos2d::Node
{
private:
	// Lane data
	int currentLane;
	float laneOneY = 108.0f;
	float laneTwoY = laneOneY + (laneOneY * 2);
	float laneThreeY = laneOneY + (laneOneY * 4);
	float Bob = 217.0f;

	// Cocos sprites
	cocos2d::Sprite* body;//= cocos2d::Sprite::create("Dogs\heads\dachs.png");
	cocos2d::Sprite* head;//= cocos2d::Sprite::create("Dogs\bodies\dachs.png");

	// Game data
	bool beheaded;
	float x = 1800;
public:
	Dog(int lane, std::string dog){
		currentLane = lane;
		body = cocos2d::Sprite::create("Dogs/heads/" + dog + ".png");
		head = cocos2d::Sprite::create("Dogs/heads/" + dog + ".png");
	}
	~Dog(){}

	void update(float){ x--; if (x < -100){ body->cleanup(); body->release(); head->cleanup(); head->release(); } }
};
