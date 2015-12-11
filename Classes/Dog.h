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
	int scorePerKill = 20;
	int scorePerBeheading = scorePerKill * 1.75;

	cocos2d::Node* layer;

	void kill(bool behead)
	{
		if (!dead) {
			if (!beheaded) {
				ScoreManager::sharedScoreManager()->addToScore(scorePerKill);
			}
			else if (beheaded) {
				ScoreManager::sharedScoreManager()->addToScore(scorePerBeheading);
			}
		}

		beheaded = behead;
		dead = true;

		if (!NoiseManager::sharedNoiseManager()->isSoundEffectPlaying) {
			NoiseManager::sharedNoiseManager()->Play("chord");
			NoiseManager::sharedNoiseManager()->isSoundEffectPlaying = true;
			NoiseManager::sharedNoiseManager()->currSFlength = 0.25;
		}
	}

	// Cocos sprites
	cocos2d::Sprite* body;
	cocos2d::Sprite* head;

public:
	Dog(int lane, std::string dog, cocos2d::Layer*scene, cocos2d::Vec2 headoffset){
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
	}
	Dog(){}
	~Dog(){}

	bool destroy = false; // whether to reset the dog or not

	void update(int BobLane){ x--; if (x < -256) destroy = true; body->setPositionX(x); head->setPositionX(x + headx);
		if (BobLane == currentLane && x < Bob && !dead) kill(false);
		if (x < Bob && beheaded)
		{
			head->setRotation(head->getRotation() - 1);
		}
		else if (x<Bob && dead){ head->setPositionY(head->getPositionY() - 1); }
	}

	void reset(int lane, std::string dog, cocos2d::Vec2 headoffset)
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
		headx = headoffset.x;
		if (dog.compare("abyssinianwirehairedtripe") == 0) { head->setAnchorPoint(Vec2(0.0f, 1.0f)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() + 32); }
		else if (dog.compare("skye") == 0) { head->setAnchorPoint(Vec2(0.0f, 0.0f)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() - body->getTextureRect().size.height); }
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