#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameManager.h"

class Dog
{
private:
	// Lane data
	int currentLane;
	float Bob = 217.0f;

	// Cocos sprites
	cocos2d::Sprite* body;//= cocos2d::Sprite::create("Dogs\heads\dachs.png");
	cocos2d::Sprite* head;//= cocos2d::Sprite::create("Dogs\bodies\dachs.png");

	// Game data
	bool beheaded = false;
	float x = 1800;
	float headx;
public:
	cocos2d::Node* layer;
	Dog(int lane, std::string dog, cocos2d::Layer*scene, cocos2d::Vec2 headoffset){
		currentLane = lane;
		layer = cocos2d::CSLoader::createNode("Dog.csb");
		body = (Sprite*)layer->getChildByName("Body");
		scene->addChild(body);
		body->setTexture("Resources/Sprites/Dogs/bodies/" + dog + ".png");
		//body->setTextureRect(Rect(0,0,256,96));
		body->setPosition(1000, GameManager::sharedGameManager()->laneY[lane-1]);
		head = (Sprite*)layer->getChildByName("Head");
		scene->addChild(head);
		head->setTexture("Resources/Sprites/Dogs/heads/" + dog + ".png");
		head->setPosition(body->getPositionX() + headoffset.x, body->getPositionY() + headoffset.y);
		headx = headoffset.x;
	}
	Dog(){}
	~Dog(){}

	bool destroy = false;

	void update(){ x--; if (x < -100) destroy = true; body->setPositionX(x); head->setPositionX(x + headx); }
	
};
