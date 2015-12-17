#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "NoiseManager.h"

enum DOG{ DACHSUND, ABYSSINIANWIREHAIREDTRIPEHOUND, DALMATIAN, BEAGLE, DROPEAREDSKYETERRIER, SCOTTISHTERRIER, RETRIEVER, SUSPICIOUSOBSTACLE };

class Dog : public cocos2d::Sprite
{
private:
	// Dog data
	static const int dogcount = 8;
	std::string dog[dogcount];
	cocos2d::Vec2 headoffset[dogcount];
	int Score[dogcount];

	// Lane data
	int currentLane;
	float Bob = 265.0f;

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
		dead = true;
		if (score > 0)
		{
			beheaded = behead;
			
			if (!beheaded) {
				NoiseManager::sharedNoiseManager()->PlaySFX((char*)"ding");
				ScoreManager::sharedScoreManager()->addToScore(score);
			}
			else if (beheaded) {
				NoiseManager::sharedNoiseManager()->PlaySFX((char*)"wilhelm");
				ScoreManager::sharedScoreManager()->addToScore(score*1.75);
			}
		}
		else
		{
			if (score>-10) NoiseManager::sharedNoiseManager()->PlaySFX((char*)"sqsh"); else NoiseManager::sharedNoiseManager()->PlaySFX((char*)"scot");
			GameManager::sharedGameManager()->health--;
		}
	}

	// Cocos sprites
	cocos2d::Sprite* body;
	cocos2d::Sprite* head;

public:
	Dog(int lane, int d, cocos2d::Layer*scene) // make dog in this lane, with this type given by enum DOG, in this scene
	{
		std::string tmpdog[dogcount] = { "dachs", "abyssinianwirehairedtripe", "dalmatia", "beagle", "skye", "scot", "retriever" "obstacle" };
		std::copy(tmpdog, tmpdog + dogcount, dog);
		Vec2 tmpoffset[dogcount] = { Vec2(-32.0f, 32.0f), Vec2(-32.0f, -72.0f), Vec2(-64.0f, 32.0f), Vec2(-32.0f, 12.0f), Vec2(-64.0f, -160.0f), Vec2(-64.0f, 8.0f), Vec2(-64.0f, 32.0f), Vec2() };
		std::copy(tmpoffset, tmpoffset + dogcount, headoffset);
		int tmpscore[dogcount] = { 20, 20, 40, 20, 20, -10, 20, -5 };
		std::copy(tmpscore, tmpscore + dogcount, Score);
		
		currentLane = lane;
		layer = cocos2d::CSLoader::createNode("Dog.csb");
		body = (Sprite*)layer->getChildByName("Body");
		scene->addChild(body);
		body->setTexture("Resources/Sprites/Dogs/bodies/" + dog[d] + ".png");
		body->setPosition(x, GameManager::sharedGameManager()->laneY[currentLane] + (body->getTextureRect().size.height / 2));
		head = (Sprite*)layer->getChildByName("Head");
		scene->addChild(head);
		head->setTexture("Resources/Sprites/Dogs/heads/" + dog[d] + ".png");
		head->setPosition(body->getPositionX() + headoffset[d].x, body->getPositionY() + headoffset[d].y);
		head->setRotation(0);
		headx = headoffset[d].x;
		if (dog[d].compare("abyssinianwirehairedtripe") == 0 || dog[d].compare("skye") == 0) { head->setAnchorPoint(Vec2(0, 0)); }
		score = Score[d];
	}
	Dog(){}
	~Dog(){}

	bool destroy = false; // whether to reset the dog or not

	void update(int BobLane, bool behead, float delta)
	{
		float s = 0.5 * GameManager::sharedGameManager()->getIncomingSpeed();
		if (delta < 1) s = GameManager::sharedGameManager()->getIncomingSpeed() * delta;
		x+=s; 
		//x--;
		if (x < -256) destroy = true; body->setPositionX(x); head->setPositionX(x + headx);
		if (BobLane == currentLane && x < Bob + 100 && !dead && x > Bob && behead) kill(behead);
		else if (BobLane == currentLane && x <= Bob && !dead && x > 150.0f) kill(behead);
		if (beheaded)
		{
			if (head->getRotation()<-180.0f) head->setPositionY(head->getPositionY() - 1); 
			if (head->getRotation()>-270.0f) head->setRotation(head->getRotation() - 1);
		}
		else if (dead){ head->setPositionY(head->getPositionY() - 1); }
	}

	void reset(int lane, int d) // reset dog to be in this lane with this type (types from enum DOG)
	{
		destroy = false;
		beheaded = false;
		dead = false;
		x = 2000;
		currentLane = lane;
		body->setTexture("Resources/Sprites/Dogs/bodies/" + dog[d] + ".png");
		body->setPosition(x, GameManager::sharedGameManager()->laneY[currentLane] + (body->getTextureRect().size.height / 2));
		head->setAnchorPoint(Vec2(0.0f, 1.0f));
		head->setTexture("Resources/Sprites/Dogs/heads/" + dog[d] + ".png");
		head->setPosition(body->getPositionX() + headoffset[d].x, body->getPositionY() + headoffset[d].y);
		head->setRotation(0);
		headx = headoffset[d].x;
		if (dog[d].compare("abyssinianwirehairedtripe") == 0 || dog[d].compare("skye") == 0) { head->setAnchorPoint(Vec2(0, 0)); }
		score = Score[d];
	}

	void reset(int range){ int b0 = cocos2d::RandomHelper::random_int(0, 65535); reset(b0 % 3, b0 % range); } // reset dog within given range
	void reset(){ reset(2); } // reset dog using initial range

};



// DO NOT USE THESE CLASSES, PASS THE DESIRED ENUM DOG TO Dog()
class Obstacle : public Dog { public: Obstacle(int lane, cocos2d::Layer*scene) :Dog(lane, SUSPICIOUSOBSTACLE, scene){}; Obstacle(int lane, int override, cocos2d::Layer*scene) :Dog(lane, override, scene){}; ~Obstacle(){}; };
class ScottishTerrier : public Obstacle { public: ScottishTerrier(int lane, cocos2d::Layer*scene) : Obstacle(lane, SCOTTISHTERRIER, scene){}; ~ScottishTerrier(){}; };
class Dachshund : public Dog { public: Dachshund(int lane, cocos2d::Layer*scene) :Dog(lane, DACHSUND, scene){}; ~Dachshund(){}; };
class AbyssinianWireHairedTripeHound : public Dog { public: AbyssinianWireHairedTripeHound(int lane, cocos2d::Layer*scene) :Dog(lane, ABYSSINIANWIREHAIREDTRIPEHOUND, scene){  }; ~AbyssinianWireHairedTripeHound(){} };
class SkyeTerrier : public Dog { public: SkyeTerrier(int lane, cocos2d::Layer*scene) :Dog(lane, DROPEAREDSKYETERRIER, scene){}; ~SkyeTerrier(){}; };
class Beagle : public Dog { public: Beagle(int lane, cocos2d::Layer*scene) :Dog(lane, BEAGLE, scene){}; ~Beagle(){} };
class Dalmatian : public Dog { public: Dalmatian(int lane, cocos2d::Layer*scene) :Dog(lane, DALMATIAN, scene){}; ~Dalmatian(){} };