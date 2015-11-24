#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/cccomaudio.h"
#include "Player.h"
#include "GameManager.h"

class HelloWorld : public cocos2d::Layer
{
private:
	// Scenes
	int scene;

	// Menu Buttons
	cocos2d::ui::Button*    Start_Button;
	cocos2d::ui::Button*	Credits_Button;

	// Backgrounds
	cocos2d::Image*			Track_Background;	// TEMPLATE BACKGROUND - NEEDS REMOVING	
	cocos2d::Sprite*		track1;
	cocos2d::Sprite*		track2;
	cocos2d::Sprite*		track3;
	cocos2d::Sprite*		sky;
	cocos2d::Sprite*		mountain1;
	cocos2d::Sprite*		mountain2;
	cocos2d::Sprite*		mountain3;
	cocos2d::Sprite*		tree1;
	cocos2d::Sprite*		tree2;
	cocos2d::Sprite*		tree3;
	cocos2d::Sprite*		tree4;

	// Translucent Colour Blocks
	cocos2d::Sprite*		Black_Filter;	// 50% Opacity

	// Text
	cocos2d::ui::Text*		Credit_Text;

	// Audio
	cocostudio::ComAudio*	audio;

	// Classes
	Player*					player;
	cocos2d::Sprite*		player_sprite;

	// Touch Events
	bool touchMoved;
	cocos2d::Vec2 initialTouchPos;
	cocos2d::Vec2 finalTouchPos;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	void update(float);

	// Deal with touches.
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	// Button event
	void StartButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void CreditsButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	// Deal with scene change
	void StartMainMenu();
	void StartGame();
	void PauseGame();
	void EndGame();
	void StartCredits();
	void EndCredits();
};

#endif // __HELLOWORLD_SCENE_H__
