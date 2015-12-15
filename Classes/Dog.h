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
		dead = true;
		if (score > 0)
		{
			beheaded = behead;
			
			if (!beheaded) {
				NoiseManager::sharedNoiseManager()->PlaySFX((char*)"chord");
				ScoreManager::sharedScoreManager()->addToScore(score);
			}
			else if (beheaded) {
				NoiseManager::sharedNoiseManager()->PlaySFX((char*)"sound240");
				ScoreManager::sharedScoreManager()->addToScore(score*1.75);
			}
		}
		else
		{
			if (score>-10) NoiseManager::sharedNoiseManager()->PlaySFX((char*)"sqsh"); else NoiseManager::sharedNoiseManager()->PlaySFX((char*)"criticalstop");
			GameManager::sharedGameManager()->health--;
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
		head->setRotation(0);
		headx = headoffset.x;
		if (dog.compare("abyssinianwirehairedtripe") == 0) { head->setAnchorPoint(Vec2(0, 0)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() - 72); }
		else if (dog.compare("skye") == 0) { head->setAnchorPoint(Vec2(0, 0)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() - body->getTextureRect().size.height); }
		score = Score;
	}
	Dog(){}
	~Dog(){}

	bool destroy = false; // whether to reset the dog or not

	void update(int BobLane, bool behead, float delta){
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
		if (dog.compare("abyssinianwirehairedtripe") == 0) { head->setAnchorPoint(Vec2(0.0f, 0.0f)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() - 72); }
		else if (dog.compare("skye") == 0) { head->setAnchorPoint(Vec2(0.0f, 0.0f)); head->setPositionX(body->getPositionX()); head->setPositionY(body->getPositionY() - body->getTextureRect().size.height); }
		score = Score;
	}

	void reset(){ int b0 = cocos2d::RandomHelper::random_int(0, 65535); if (b0 % 6 == 0) reset(b0 % 3, "dachs", Vec2(-32.0f, 32.0f), 20); else if (b0 % 6 == 1) reset(b0 % 3, "abyssinianwirehairedtripe", Vec2(-32.0f, 32.0f), 20); else if (b0 % 6 == 2) reset(b0 % 3, "skye", Vec2(-64.0f, 0.0f), 20); else if (b0 % 6 == 3) reset(b0 % 3, "beagle", Vec2(-32.0f, 12.0f), 20); else if (b0 % 6 == 4) reset(b0 % 3, "scot", Vec2(-64.0f, 8.0f), -10); else if (b0 % 6 == 5) reset(b0 % 3, "obstacle", Vec2(-32.0f, 32.0f), -5); }

};

class Obstacle : public Dog
{
public:
	Obstacle(int lane, cocos2d::Layer*scene, int scoreoverride = -5) :Dog(lane, "obstacle", scene, Vec2(-32.0f, 32.0f), scoreoverride){};
	Obstacle(int lane, std::string textureoverride, cocos2d::Layer*scene, cocos2d::Vec2 headoffset, int scoreoverride = -5) :Dog(lane, textureoverride, scene, headoffset, scoreoverride){};
	~Obstacle(){};
};

class ScottishTerrier : public Obstacle
{
public:
	ScottishTerrier(int lane, cocos2d::Layer*scene) : Obstacle(lane, "scot", scene, Vec2(-64.0f, 8.0f), -10){};
	~ScottishTerrier(){};
};
