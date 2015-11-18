#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto rootNode = CSLoader::createNode("MainMenu.csb");
	addChild(rootNode);
	auto creditNode = CSLoader::createNode("CreditScene.csb");
	addChild(creditNode);

	this->scheduleUpdate();

	// Initialise Scene
	scene = 1;

	// Initialise all images/sprites/buttons/ect...
	Black_Filter = (Sprite*)rootNode->getChildByName("Black_Filter");

	Start_Button = static_cast<ui::Button*>(rootNode->getChildByName("Start_Button"));
	Start_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartButtonPressed, this));

	Credits_Button = static_cast<ui::Button*>(rootNode->getChildByName("Credits_Button"));
	Credits_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::CreditsButtonPressed, this));

	Credit_Text = (ui::Text*)creditNode->getChildByName("Credit_Text");
	Credit_Text->setFontSize(30);
	Credit_Text->setString("Programmers:\n David Smith\n Sam Head\n\nArtwork:\n Sam Head\n\nDocumentation:\n David Smith\n");
	Credit_Text->setAnchorPoint(Vec2(0.0f, 1.0f));
	Credit_Text->setVisible(false);

	// Initialise Audio
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Steve_Combs_-_05_-_Dog.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Steve_Combs_-_05_-_Dog.mp3", true);
	//audio->preloadBackgroundMusic("Resources/Audio/Steve_Combs_-_05_-_Dog.mp3");
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("res/Resources/Audio/Steve_Combs_-_05_-_Dog.mp3", true);
	//audio->playBackgroundMusic("Resources/Audio/Steve_Combs_-_05_-_Dog.mp3", true);
    return true;
}

void HelloWorld::update(float delta)
{
	auto winSize = Director::getInstance()->getVisibleSize();

	// Check what scene player is on
	if (scene == 1) {		// scene 1 == menu

	}
	else if (scene == 2) {	// scene 2 == game

	}
	else if (scene == 3) {	// scene 3 == credits
		// Check if credits have exited the screen
		// REMEMBER - Anchor point is taken at (0, 1) [Normalized coords]
		if ((Credit_Text->getPositionY() - Credit_Text->getSize().height) > winSize.height) {
			EndCredits();
		}
		else {
			int currOpac = Black_Filter->getOpacity();

			// If scenes have just switched, the black filter's opacity needs to slowly increase for a smooth fade transition
			if (currOpac <= 255) {	// 255 because opacity is stored as an unsigned char
				int nextOpac = currOpac + 5;

				// Check that currOpac will not exeed 255 next update
				if (nextOpac <= 255) {
					Black_Filter->setOpacity(nextOpac);
				}
				else {
					Black_Filter->setOpacity(255);
				}
			}

			Credit_Text->setPosition(Vec2(Credit_Text->getPositionX() + (delta * 0.0f),
				Credit_Text->getPositionY() + (delta * 150.0f)));
		}
	}
}

void HelloWorld::StartButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("I touched the start, and I liked it! %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->StartGame();
	}
	this->StartGame();
}

void HelloWorld::CreditsButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("I touched the credits, and I liked it! %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->StartCredits();
	}
	this->StartCredits();
}

void HelloWorld::StartMainMenu()
{
	scene = 1;

	auto startMoveTo = MoveTo::create(0.5, Vec2(1280.0f, 471.0f)); // Take half a second to move off screen.
	Start_Button->runAction(startMoveTo);

	auto creditsMoveTo = MoveTo::create(0.5, Vec2(1280.0f, 249.0f)); // Take half a second to move off screen.
	Credits_Button->runAction(creditsMoveTo);
}

void HelloWorld::StartGame()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	scene = 2;

	auto startMoveTo = MoveTo::create(0.5, Vec2(winSize.width, Start_Button->getPositionY())); // Take half a second to move off screen.
	Start_Button->runAction(startMoveTo);

	auto creditsMoveTo = MoveTo::create(0.5, Vec2(winSize.width, Credits_Button->getPositionY())); // Take half a second to move off screen.
	Credits_Button->runAction(creditsMoveTo);
}

void HelloWorld::PauseGame()
{

}

void HelloWorld::EndGame()
{

}

void HelloWorld::StartCredits()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	scene = 3;

	//Set up credit text
	Credit_Text->setPosition(Vec2(888.0f, 0.0f));
	Credit_Text->setVisible(true);

	// Move buttons
	auto startMoveTo = MoveTo::create(0.5, Vec2(winSize.width, Start_Button->getPositionY())); // Take half a second to move off screen.
	Start_Button->runAction(startMoveTo);

	auto creditsMoveTo = MoveTo::create(0.5, Vec2(winSize.width, Credits_Button->getPositionY())); // Take half a second to move off screen.
	Credits_Button->runAction(creditsMoveTo);
}

void HelloWorld::EndCredits()
{
	// Start smoothly fading the filter back to menu opacity (50% - 127 unsigned char)
	int currOpac = Black_Filter->getOpacity();

	if (currOpac >= 127) {	// 255 because opacity is stored as an unsigned char
		int nextOpac = currOpac - 5;

		// Check that currOpac will not fall below 127 next update
		if (nextOpac > 127) {
			Black_Filter->setOpacity(nextOpac);
		}
		else {
			Black_Filter->setOpacity(127);

			// Transition complete, remove stray elements and start menu scene
			Credit_Text->setVisible(false);
			StartMainMenu();
		}
	}
}
