#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "NoiseManager.h"

class Dog : public cocos2d::Sprite
{
private:
	// Lane data
	int currentLane;
	float Bob = 250.0f;

	// Game data
	bool beheaded = false;
	bool dead = false;
	float x = 2000;
	float headx;

	// Score Data
	int score;

	cocos2d::Node* layer;

	void kill(bool behead)
	{
		if (score > 0)
		{
			beheaded = behead;
			dead = true;
			
			if (!beheaded) {
				NoiseManager::NoiseManager().PlaySFX("chord");
				ScoreManager::sharedScoreManager()->addToScore(score);
			}
			else if (beheaded) {
				NoiseManager::NoiseManager().PlaySFX("sound240");
				ScoreManager::sharedScoreManager()->addToScore(score*1.75);
			}
		}
	}

	// Cocos sprites
	cocos2d::Sprite* body;
	cocos2d::Sprite* head;

public:
	Dog(int lane, std::string dog, cocos2d::Layer*scene, cocos2d::Vec2 headoffset, int Score){
		currentLane = lane;
		layer = cocos2d::CSLoader::createNode("Dog.csb");
		body = (Sprite*)layer->getChildByName("Body");
		scene->addChild(body);
		body->setTexture("Resources/Sprites/Dogs/bodies/" + dog + ".png");
		body->setPosition(x, GameManager::sharedGameManager()->laneY[currentLane] + (body->getTextureRect().size.height / 2));
		head = (Sprite*)layer->getChildByName("Head");
		scene->addChild(head);
		head->setTexture("Resources/Sprites/Dogs/heads/" + dog + ".png");
		head->setPosition(body->getPositionX() + headoffset.x, body->getPositionY() + headoffset.y);
		headx = headoffset.x;
		if (dog.compare("abyssinianwirehairedtripe") == 0) { head->setAnchorPoint(Vec2(0, 1)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() + 32); }
		else if (dog.compare("skye") == 0) { head->setAnchorPoint(Vec2(0, 0)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() - body->getTextureRect().size.height); }
		score = Score;
	}
	Dog(){}
	~Dog(){}

	bool destroy = false; // whether to reset the dog or not

	void update(int BobLane, bool behead){ x--; if (x < -256) destroy = true; body->setPositionX(x); head->setPositionX(x + headx);
		if (BobLane == currentLane && x < Bob + 100 && !dead && x > Bob && behead) kill(behead);
		else if (BobLane == currentLane && x <= Bob && !dead && x > 150.0f) kill(behead);
		if (beheaded)
		{
			head->setRotation(head->getRotation() - 1);
		}
		else if (dead){ head->setPositionY(head->getPositionY() - 1); }
	}

	void reset(int lane, std::string dog, cocos2d::Vec2 headoffset, int Score)
	{
		destroy = false;
		beheaded = false;
		dead = false;
		x = 2000;
		currentLane = lane;
		body->setTexture("Resources/Sprites/Dogs/bodies/" + dog + ".png");
		body->setPosition(x, GameManager::sharedGameManager()->laneY[currentLane] + (body->getTextureRect().size.height / 2));
		head->setAnchorPoint(Vec2(0.0f, 1.0f));
		head->setTexture("Resources/Sprites/Dogs/heads/" + dog + ".png");
		head->setPosition(body->getPositionX() + headoffset.x, body->getPositionY() + headoffset.y);
		head->setRotation(0);
		headx = headoffset.x;
		if (dog.compare("abyssinianwirehairedtripe") == 0) { head->setAnchorPoint(Vec2(0.0f, 1.0f)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() + 32); }
		else if (dog.compare("skye") == 0) { head->setAnchorPoint(Vec2(0.0f, 0.0f)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() - body->getTextureRect().size.height); }
		score = Score;
	}

};
/*
class Dachshund : public Dog
{
public:
	Dachshund(int lane, cocos2d::Layer*scene) :Dog(lane, "dachs", scene, Vec2(-32.0f, 32.0f)){};
	~Dachshund(){};
};

class AbyssinianWireHairedTripeHound : public Dog { public: AbyssinianWireHairedTripeHound(int lane, cocos2d::Layer*scene) :Dog(lane, "abyssinianwirehairedtripe", scene, Vec2(-32.0f, 32.0f)){  }; ~AbyssinianWireHairedTripeHound(){} };
class SkyeTerrier : public Dog { public: SkyeTerrier(int lane, cocos2d::Layer*scene) :Dog(lane, "skye", scene, Vec2(-64.0f, 0.0f)){}; ~SkyeTerrier(){};};
class Beagle : public Dog { public: Beagle(int lane, cocos2d::Layer*scene) :Dog(lane, "beagle", scene, Vec2(-32.0f, 12.0f)){}; ~Beagle(){} };*/