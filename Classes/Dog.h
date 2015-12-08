#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

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
	cocos2d::Node* layer;
	Dog(int lane, std::string dog, cocos2d::Layer*scene){//, cocos2d::Vec2 headoffset){
		currentLane = lane;
		layer = cocos2d::CSLoader::createNode("Dog.csb");
		//scene->addChild(layer);
		//layer->
		body = (Sprite*)layer->getChildByName("Body");
		scene->addChild(body);
		//body->setPosition(10, 10);
		head = (Sprite*)layer->getChildByName("Head");
		scene->addChild(head);
		//head = cocos2d::Sprite::create("Resources/Sprites/Dogs/heads/" + dog + ".png");
		//head->setPosition(20, 20);
	}
	Dog(){}
	~Dog(){}

	bool destroy = false;

	void update(){ x--; if (x < -100) destroy = true; }
	
};
