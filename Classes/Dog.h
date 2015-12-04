#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Dog
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
	bool beheaded = false;
	float x = 1800;
public:
	Dog(int lane, std::string dog, cocos2d::Layer*scene){
		currentLane = lane;
		body = cocos2d::Sprite::create("/Sprites/Dogs/heads/" + dog + ".png");
		body->setPosition(10, 10);
		head = cocos2d::Sprite::create("/Sprites/Dogs/heads/" + dog + ".png");
		head->setPosition(20, 20);
		scene->addChild(body);
		scene->addChild(head);
	}
	Dog(){}
	~Dog(){ body->cleanup(); body->release(); head->cleanup(); head->release(); }

	bool destroy = false;

	void update(){ x--; if (x < -100) destroy = true; }
	
};
