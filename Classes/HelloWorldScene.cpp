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

	// Initialise all images/sprites/buttons/ect...
	Start_Button = static_cast<ui::Button*>(rootNode->getChildByName("Start_Button"));
	Start_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartButtonPressed, this));
	Credits_Button = static_cast<ui::Button*>(rootNode->getChildByName("Credits_Button"));
	Credits_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::CreditsButtonPressed, this));

    return true;
}

void HelloWorld::update(float a)
{
	// Fuck off cocos
}

void HelloWorld::StartButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("In touch! %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->StartGame();
	}
	this->StartGame();
}

void HelloWorld::CreditsButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{

}

void HelloWorld::StartGame()
{
	auto winSize = Director::getInstance()->getVisibleSize();

	auto moveTo = MoveTo::create(0.5, Vec2(-winSize.width*0.5f, winSize.height*0.5f)); // Take half a second to move off screen.
	Start_Button->runAction(moveTo);
}
