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

	// Game data
	bool beheaded = true;
	float x = 1800;
	float headx;

protected:
	// Cocos sprites
	cocos2d::Sprite* body;//= cocos2d::Sprite::create("Dogs\heads\dachs.png");
	cocos2d::Sprite* head;//= cocos2d::Sprite::create("Dogs\bodies\dachs.png");

public:
	cocos2d::Node* layer;
	Dog(int lane, std::string dog, cocos2d::Layer*scene, cocos2d::Vec2 headoffset){
		currentLane = lane;
		layer = cocos2d::CSLoader::createNode("Dog.csb");
		body = (Sprite*)layer->getChildByName("Body");
		scene->addChild(body);
		body->setTexture("Resources/Sprites/Dogs/bodies/" + dog + ".png");
		body->setPosition(1000, GameManager::sharedGameManager()->laneY[currentLane]);
		head = (Sprite*)layer->getChildByName("Head");
		scene->addChild(head);
		head->setTexture("Resources/Sprites/Dogs/heads/" + dog + ".png");
		head->setPosition(body->getPositionX() + headoffset.x, body->getPositionY() + headoffset.y);
		headx = headoffset.x;
	}
	Dog(){}
	~Dog(){}

	bool destroy = false;

	void update(){ x--; if (x < -256) destroy = true; body->setPositionX(x); head->setPositionX(x + headx);
		if (x < Bob && beheaded)
		{
			head->setRotation(head->getRotation() - 1);
		}
	}
	
};

class Dachshund : public Dog
{
public:
	Dachshund(int lane, cocos2d::Layer*scene) :Dog(lane, "dachs", scene, Vec2(-32.0f, 32.0f)){};
	~Dachshund(){};
};

class AbyssinianWireHairedTripeHound : public Dog { public: AbyssinianWireHairedTripeHound(int lane, cocos2d::Layer*scene) :Dog(lane, "abyssinianwirehairedtripe", scene, Vec2(-32.0f, 32.0f)){}; ~AbyssinianWireHairedTripeHound(){} };
class SkyeTerrier : public Dog { public: SkyeTerrier(int lane, cocos2d::Layer*scene) :Dog(lane, "skye", scene, Vec2(-64.0f, 0.0f)){ //head->setAnchorPoint(Vec2(1, 0)); 
}; ~SkyeTerrier(){} };
class Beagle : public Dog { public: Beagle(int lane, cocos2d::Layer*scene) :Dog(lane, "beagle", scene, Vec2(-32.0f, 12.0f)){}; ~Beagle(){} };