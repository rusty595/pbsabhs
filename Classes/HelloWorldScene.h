#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "editor-support/cocostudio/cccomaudio.h"
#include "Player.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "Dog.h"

class HelloWorld : public cocos2d::Layer
{
private:
	// Scenes
	int scene;

	// Menu Buttons
	cocos2d::ui::Button*    Start_Button;
	cocos2d::ui::Button*	Credits_Button;

	// Backgrounds
	cocos2d::Sprite*		track1;
	cocos2d::Sprite*		track2;
	cocos2d::Sprite*		track3;
	cocos2d::Sprite*		track4;
	cocos2d::Sprite*		track5;
	cocos2d::Sprite*		track6;
	cocos2d::Sprite*		sky1;
	cocos2d::Sprite*		sky2;
	cocos2d::Sprite*		mountain1;
	cocos2d::Sprite*		mountain2;
	cocos2d::Sprite*		mountain3;
	cocos2d::Sprite*		tree1;
	cocos2d::Sprite*		tree2;
	cocos2d::Sprite*		tree3;
	cocos2d::Sprite*		tree4;
	cocos2d::Sprite*		tree5;
	cocos2d::Sprite*		tree6;
	cocos2d::Sprite*		tree7;
	cocos2d::Sprite*		tree8;

	// Translucent Colour Blocks
	cocos2d::Sprite*		Black_Filter;	// 50% Opacity

	// Text
	cocos2d::ui::Text*		Credit_Text;
	cocos2d::ui::Text*		Pause_Score;
	cocos2d::ui::Text*		Pause_Highscore;

	// Audio
	bool muted;

	// UI
	bool					UIMoving;
	cocos2d::ui::Button*	Pause_Button;
	cocos2d::ui::Button*	Mute_Button;
	cocos2d::Sprite*		UI_Background;
	cocos2d::ui::Text*		score;
	cocos2d::ui::Text*		healthmeter;

	// Pause
	cocos2d::ui::Button*    Resume_Button;
	cocos2d::ui::Button*	Exit_Button;

	// Classes
	Player*					player;
	cocos2d::Sprite*		player_sprite;

	// Touch Events
	bool touchMoved;
	bool inTouch;
	cocos2d::Vec2 initialTouchPos;
	cocos2d::Vec2 finalTouchPos;

public:
	cocos2d::Vector<Dog*> dogs;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void initTouchListeners();
	void initNodes();
	void initCocosElements();
	void initTracksPositions();

    // implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	void update(float);
	void updateMenu(float);
	void updateGame(float);
	void updateCredits(float);
	void updateParallaxBackground(float);
	void updateDogs(float);
	Dog* newDog();

	// Deal with touches.
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	// Button event
	void StartButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void CreditsButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void MuteButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void PauseButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void ResumeButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void ExitButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	// Deal with scene change
	void StartMainMenu();
	void StartGame();
	void PauseGame();
	void ResumeGame();
	void EndGame();
	void StartCredits();
	void EndCredits();
};

#endif // __HELLOWORLD_SCENE_H__