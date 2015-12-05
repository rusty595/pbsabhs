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

	// Initialise Scene
	scene = 1;
	UIMoving = false;

	//TOUCHES
	initTouchListeners();

	//NODES
	initNodes();

	//COCOS ELEMENTS
	initCocosElements();

	// Initialise player class
	player->create();
	player = Player::create();
	this->addChild(player);
	player->setOffscreenPos(player_sprite);
	player_sprite->setVisible(true);

	// Audio
	muted = false;
	auto b0 = cocos2d::RandomHelper::random_int(0, 65535);
	if (b0 != 0){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("dogs.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("dogs.mp3", true);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("no.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("no.mp3", true);
	}

	this->scheduleUpdate();

	// Game is not live until the start button is pressed.
	GameManager::sharedGameManager()->setIsGameLive(false);

    return true;
}

void HelloWorld::initTouchListeners()
{
	//Set up a touch listener.
	auto touchListener = EventListenerTouchOneByOne::create();

	//Set callbacks for our touch functions.
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	//Add our touch listener to event listener list.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void HelloWorld::initNodes()
{
	// Create nodes
	auto parallaxBackground = CSLoader::createNode("ParallaxBackground.csb");
	addChild(parallaxBackground);
	auto trackNode1 = CSLoader::createNode("Track.csb");
	addChild(trackNode1);
	auto trackNode2 = CSLoader::createNode("Track.csb");
	addChild(trackNode2);
	auto trackNode3 = CSLoader::createNode("Track.csb");
	addChild(trackNode3);
	auto trackNode4 = CSLoader::createNode("Track.csb");
	addChild(trackNode4);
	auto trackNode5 = CSLoader::createNode("Track.csb");
	addChild(trackNode5);
	auto trackNode6 = CSLoader::createNode("Track.csb");
	addChild(trackNode6);
	auto UINode = CSLoader::createNode("UI.csb");
	addChild(UINode);
	auto rootNode = CSLoader::createNode("MainMenu.csb");
	addChild(rootNode);
	auto creditNode = CSLoader::createNode("CreditScene.csb");
	addChild(creditNode);
	auto playerNode = CSLoader::createNode("Player.csb");
	addChild(playerNode);

	// Set up references
	sky1 = (Sprite*)parallaxBackground->getChildByName("Sky");
	sky2 = (Sprite*)parallaxBackground->getChildByName("Sky_2");
	mountain1 = (Sprite*)parallaxBackground->getChildByName("Mountain_1");
	mountain2 = (Sprite*)parallaxBackground->getChildByName("Mountain_2");
	mountain3 = (Sprite*)parallaxBackground->getChildByName("Mountain_3");
	tree1 = (Sprite*)parallaxBackground->getChildByName("Tree_1");
	tree2 = (Sprite*)parallaxBackground->getChildByName("Tree_2");
	tree3 = (Sprite*)parallaxBackground->getChildByName("Tree_3");
	tree4 = (Sprite*)parallaxBackground->getChildByName("Tree_4");
	tree5 = (Sprite*)parallaxBackground->getChildByName("Tree_5");
	tree6 = (Sprite*)parallaxBackground->getChildByName("Tree_6");
	tree7 = (Sprite*)parallaxBackground->getChildByName("Tree_7");
	tree8 = (Sprite*)parallaxBackground->getChildByName("Tree_8");
	track1 = (Sprite*)trackNode1->getChildByName("Track");
	track2 = (Sprite*)trackNode2->getChildByName("Track");
	track3 = (Sprite*)trackNode3->getChildByName("Track");
	track4 = (Sprite*)trackNode4->getChildByName("Track");
	track5 = (Sprite*)trackNode5->getChildByName("Track");
	track6 = (Sprite*)trackNode6->getChildByName("Track");
	UI_Background = (Sprite*)UINode->getChildByName("UI_Background");

	Black_Filter = (Sprite*)rootNode->getChildByName("Black_Filter");

	Start_Button = static_cast<ui::Button*>(rootNode->getChildByName("Start_Button"));
	Credits_Button = static_cast<ui::Button*>(rootNode->getChildByName("Credits_Button"));
	Mute_Button = static_cast<ui::Button*>(rootNode->getChildByName("Mute_Button"));
	Pause_Button = static_cast<ui::Button*>(UINode->getChildByName("Pause_Button"));
	Resume_Button = static_cast<ui::Button*>(rootNode->getChildByName("Resume_Button"));
	Exit_Button = static_cast<ui::Button*>(rootNode->getChildByName("Exit_Button"));

	Credit_Text = (ui::Text*)creditNode->getChildByName("Credit_Text");
	Pause_Score = (ui::Text*)rootNode->getChildByName("Pause_Score");
	Pause_Highscore = (ui::Text*)rootNode->getChildByName("Pause_Highscore");
	score = (ui::Text*)UINode->getChildByName("Score");

	player_sprite = (Sprite*)playerNode->getChildByName("Player_Skin_1");
}

void HelloWorld::initCocosElements()
{
	auto winSize = Director::getInstance()->getVisibleSize();

	sky1->setPosition(Vec2(888.0f, 864.0f));
	sky2->setPosition(Vec2(sky1->getTextureRect().getMaxX() + (sky1->getPosition().x), 864.0f));

	int limiter = (int)winSize.width + mountain1->getBoundingBox().getMaxX();
	int random = cocos2d::RandomHelper::random_int(1, limiter);
	mountain1->setPosition(Vec2(random, 864.0f));
	random = cocos2d::RandomHelper::random_int(1, (int)winSize.width);
	mountain2->setPosition(Vec2(random, 864.0f));
	random = cocos2d::RandomHelper::random_int(1, (int)winSize.width);
	mountain3->setPosition(Vec2(random, 864.0f));

	limiter = (int)winSize.width + tree1->getTextureRect().getMaxX();
	random = cocos2d::RandomHelper::random_int(1, (limiter * 2));
	tree1->setPosition(Vec2(random, 812.0f));
	random = cocos2d::RandomHelper::random_int(1, (limiter * 2));
	tree2->setPosition(Vec2(random, 812.0f));
	random = cocos2d::RandomHelper::random_int(1, (limiter * 2));
	tree3->setPosition(Vec2(random, 812.0f));
	random = cocos2d::RandomHelper::random_int(1, (limiter * 2));
	tree4->setPosition(Vec2(random, 812.0f));
	random = cocos2d::RandomHelper::random_int(1, (limiter * 2));
	tree5->setPosition(Vec2(random, 812.0f));
	random = cocos2d::RandomHelper::random_int(1, (limiter * 2));
	tree6->setPosition(Vec2(random, 812.0f));
	random = cocos2d::RandomHelper::random_int(1, (limiter * 2));
	tree7->setPosition(Vec2(random, 812.0f));
	random = cocos2d::RandomHelper::random_int(1, (limiter * 2));
	tree8->setPosition(Vec2(random, 812.0f));

	UI_Background->setPosition(Vec2(951.0f, 1025.5f));

	initTracksPositions();

	Start_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartButtonPressed, this));
	Credits_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::CreditsButtonPressed, this));
	Start_Button->setPosition(Vec2(winSize.width + Start_Button->getBoundingBox().getMaxX(), Start_Button->getPositionY()));
	Credits_Button->setPosition(Vec2(winSize.width + Credits_Button->getBoundingBox().getMaxX(), Credits_Button->getPositionY()));

	auto startMoveTo = MoveTo::create(0.5, Vec2(1280.0f, 471.0f)); // Take half a second to move off screen.
	Start_Button->runAction(startMoveTo);

	auto creditsMoveTo = MoveTo::create(0.5, Vec2(1280.0f, 249.0f)); // Take half a second to move off screen.
	Credits_Button->runAction(creditsMoveTo);

	Mute_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::MuteButtonPressed, this));
	Pause_Button->setPosition(Vec2(63.0f, 1025.5f));
	Pause_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::PauseButtonPressed, this));
	Resume_Button->setVisible(false);
	Resume_Button->setPositionX(winSize.width + Resume_Button->getContentSize().width);
	Resume_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::ResumeButtonPressed, this));
	Exit_Button->setVisible(false);
	Exit_Button->setPositionX(winSize.width + Exit_Button->getContentSize().width);
	Exit_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::ExitButtonPressed, this));

	score->setFontSize(30);
	score->setString(StringUtils::format("%d", 0));
	score->setVisible(false);
	score->setPosition(Vec2(winSize.width - 40.0f, winSize.height - 45.0f));
	Credit_Text->setFontSize(30);
	Credit_Text->setString("Programmers:\n David Smith\n Sam Head\n\nDog Handler:\n Sam Head\n\nDocumentation:\n David Smith\n");
	Credit_Text->setAnchorPoint(Vec2(0.5f, 1.0f));
	Credit_Text->setVisible(false);
	Pause_Score->setString(StringUtils::format("%d", 0));
	Pause_Score->setVisible(false);
	Pause_Highscore->setString(StringUtils::format("%d", 0));
	Pause_Highscore->setVisible(false);
}

void HelloWorld::update(float delta)
{
	// Check what scene player is on
	if (scene == 1) {		// scene 1 == menu
		updateMenu(delta);
	}
	else if (scene == 2) {	// scene 2 == game
		updateGame(delta);
	}
	else if (scene == 3) {	// scene 3 == credits
		updateCredits(delta);
	}

	// Parallax Background
	updateParallaxBackground(delta);
}

void HelloWorld::updateMenu(float delta)
{
	if (Black_Filter->getOpacity() != 127) {
		// Start smoothly fading the filter to 127 opacity
		int currOpac = Black_Filter->getOpacity();

		if (currOpac <= 127) {
			int nextOpac = currOpac + 5;

			// Check that currOpac will not fall below 0 next update
			if (nextOpac < 127) {
				Black_Filter->setOpacity(nextOpac);
			}
			else {
				Black_Filter->setOpacity(127);
			}
		}
	}
}

void HelloWorld::updateGame(float delta)
{
	if (GameManager::sharedGameManager()->getIsGameLive() == false) {

		if (Black_Filter->getOpacity() != 0) {
			// Start smoothly fading the filter to 0 opacity
			int currOpac = Black_Filter->getOpacity();

			if (currOpac >= 0) {
				int nextOpac = currOpac - 5;

				// Check that currOpac will not fall below 0 next update
				if (nextOpac > 0) {
					Black_Filter->setOpacity(nextOpac);
				}
				else {
					Black_Filter->setOpacity(0);
				}
			}
		}
		else {
			if (player->isReady(player_sprite) == true) {
				GameManager::sharedGameManager()->setIsGameLive(true);
				score->setVisible(true);

				auto scoreFadeIn = FadeIn::create(0.5);
				score->runAction(scoreFadeIn);
			}
			else {
				player->setVisible(true);
				player->moveIntoStartPos(player_sprite);
			}
		}
	}
	else {
		// Updates for when game is live
		if (GameManager::sharedGameManager()->getIsGamePaused() == false) {
			if (GameManager::sharedGameManager()->getPlayerRunning() == true) {
				GameManager::sharedGameManager()->incrementSpeed(delta);
			}
			else {
				GameManager::sharedGameManager()->setPlayerRunning(true);
			}

			// Score
			// Use player speed as a multiplier
			float multiplier = GameManager::sharedGameManager()->getPlayerSpeed() / 1000;
			ScoreManager::sharedScoreManager()->addToScore(multiplier * delta);
			//ScoreManager::sharedScoreManager()->resetScore();
			//ScoreManager::sharedScoreManager()->addToScore(dogs.size());		//debug to check number of dogs in memory
			score->setString(StringUtils::format("%d", ((int)ScoreManager::sharedScoreManager()->getScore())));
			////make dogs
			//updateDogs(delta); // DO NOT MAKE DOGS
			// Filter
			if (Black_Filter->getOpacity() != 0) {
				// Start smoothly fading the filter to 0 opacity
				int currOpac = Black_Filter->getOpacity();

				if (currOpac >= 0) {
					int nextOpac = currOpac - 5;

					// Check that currOpac will not fall below 0 next update
					if (nextOpac > 0) {
						Black_Filter->setOpacity(nextOpac);
					}
					else {
						Black_Filter->setOpacity(0);
					}
				}
			}
		}
		else if (GameManager::sharedGameManager()->getIsGamePaused() == true) {

			if (Black_Filter->getOpacity() != 127) {
				// Start smoothly fading the filter to 127 opacity
				int currOpac = Black_Filter->getOpacity();

				if (currOpac <= 127) {
					int nextOpac = currOpac + 5;

					// Check that currOpac will not fall below 0 next update
					if (nextOpac < 127) {
						Black_Filter->setOpacity(nextOpac);
					}
					else {
						Black_Filter->setOpacity(127);
					}
				}
			}
		}
	}
}

void HelloWorld::updateDogs(float delta)
{
	int b0;
	if (dogs.size() < GameManager::sharedGameManager()->getPlayerSpeed() / 1000.0f*2.0f)
	{
		b0 = cocos2d::RandomHelper::random_int(0, 65535);
		if (b0 % 1==0)
		{
			Dachshund not_bob = Dachshund(2, this);
			dogs.push_back(not_bob);
		}
	}
	std::list<Dog> dogsRemaining;
	for each (Dog d0 in dogs)
	{
		d0.update();
		if (!d0.destroy) dogsRemaining.push_back(d0);
	}
	dogs.clear();
	dogs = dogsRemaining;
}

void HelloWorld::updateCredits(float delta)
{
	auto winSize = Director::getInstance()->getVisibleSize();

	// Check if credits have exited the screen
	// REMEMBER - Anchor point is taken at (0, 1) [Normalized coords]
	if ((Credit_Text->getPositionY() - Credit_Text->getContentSize().height) > winSize.height) {
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

void HelloWorld::updateParallaxBackground(float delta)
{
	auto winSize = Director::getInstance()->getVisibleSize();

	// Sky
	float skySpeed = GameManager::sharedGameManager()->getSkySpeed() * delta;
	sky1->setPositionX(sky1->getPositionX() + skySpeed);
	sky2->setPositionX(sky2->getPositionX() + skySpeed);
	// Check if sky is offscreen, if so, move sky image to the end of second sky image
	if (sky1->getPositionX() + sky1->getTextureRect().getMaxX() < 0) {
		sky1->setPositionX(sky2->getTextureRect().getMaxX() + (sky2->getPosition().x));
	}
	else if (sky2->getPositionX() + sky2->getTextureRect().getMaxX() < 0) {
		sky2->setPositionX(sky1->getTextureRect().getMaxX() + (sky1->getPosition().x));
	}
	else if (sky1->getBoundingBox().getMinX() > 0) {
		// Sky has floated too far to the right
		sky2->setPositionX(sky1->getPositionX() - sky1->getTextureRect().getMaxX());
	}

	// Mountain
	int randomMountain = cocos2d::RandomHelper::random_int(1, 300);
	float mountainSpeed = GameManager::sharedGameManager()->getMountainSpeed() * delta;
	mountain1->setPositionX(mountain1->getPositionX() + mountainSpeed);
	mountain2->setPositionX(mountain2->getPositionX() + mountainSpeed);
	mountain3->setPositionX(mountain3->getPositionX() + mountainSpeed);
	// If mountain is offscreen, give it a CHANCE to come back onscreen to stop same Mountain pattern emerging
	if (mountain1->getPositionX() + mountain1->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + mountain1->getTextureRect().getMaxX();
		int randomMountain = cocos2d::RandomHelper::random_int(limiter, (int)(limiter * 1.5));
		mountain1->setPositionX(randomMountain);
	}
	else {
		mountain1->setPositionX(mountain1->getPositionX() + mountainSpeed);
	}
	if (mountain2->getPositionX() + mountain2->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + mountain2->getTextureRect().getMaxX();
		int randomMountain = cocos2d::RandomHelper::random_int(limiter, (int)(limiter * 1.5));
		mountain2->setPositionX(randomMountain);
	}
	else {
		mountain2->setPositionX(mountain2->getPositionX() + mountainSpeed);
	}
	if (mountain3->getPositionX() + mountain3->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + mountain3->getTextureRect().getMaxX();
		int randomMountain = cocos2d::RandomHelper::random_int(limiter, (int)(limiter * 1.5));
		mountain3->setPositionX(randomMountain);
	}
	else {
		mountain3->setPositionX(mountain3->getPositionX() + mountainSpeed);
	}

	// Tree
	float treeSpeed = GameManager::sharedGameManager()->getTreeSpeed() * delta;
	// If tree is offscreen, give it a CHANCE to come back onscreen to stop same tree pattern emerging
	if (tree1->getPositionX() + tree1->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + tree1->getTextureRect().getMaxX();
		int randomTree = cocos2d::RandomHelper::random_int(limiter, (limiter * 2));
		tree1->setPositionX(randomTree);
	}
	else {
		tree1->setPositionX(tree1->getPositionX() + treeSpeed);
	}
	if (tree2->getPositionX() + tree2->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + tree2->getTextureRect().getMaxX();
		int randomTree = cocos2d::RandomHelper::random_int(limiter, (limiter * 2));
		tree2->setPositionX(randomTree);
	}
	else {
		tree2->setPositionX(tree2->getPositionX() + treeSpeed);
	}
	if (tree3->getPositionX() + tree3->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + tree3->getTextureRect().getMaxX();
		int randomTree = cocos2d::RandomHelper::random_int(limiter, (limiter * 2));
		tree3->setPositionX(randomTree);
	}
	else {
		tree3->setPositionX(tree3->getPositionX() + treeSpeed);
	}
	if (tree4->getPositionX() + tree4->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + tree4->getTextureRect().getMaxX();
		int randomTree = cocos2d::RandomHelper::random_int(limiter, (limiter * 2));
		tree4->setPositionX(randomTree);
	}
	else {
		tree4->setPositionX(tree4->getPositionX() + treeSpeed);
	}
	if (tree5->getPositionX() + tree5->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + tree5->getTextureRect().getMaxX();
		int randomTree = cocos2d::RandomHelper::random_int(limiter, (limiter * 2));
		tree5->setPositionX(randomTree);
	}
	else {
		tree5->setPositionX(tree5->getPositionX() + treeSpeed);
	}
	if (tree6->getPositionX() + tree6->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + tree6->getTextureRect().getMaxX();
		int randomTree = cocos2d::RandomHelper::random_int(limiter, (limiter * 2));
		tree6->setPositionX(randomTree);
	}
	else {
		tree6->setPositionX(tree6->getPositionX() + treeSpeed);
	}
	if (tree7->getPositionX() + tree7->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + tree7->getTextureRect().getMaxX();
		int randomTree = cocos2d::RandomHelper::random_int(limiter, (limiter * 2));
		tree7->setPositionX(randomTree);
	}
	else {
		tree7->setPositionX(tree7->getPositionX() + treeSpeed);
	}
	if (tree8->getPositionX() + tree8->getTextureRect().getMaxX() < 0) {
		int limiter = (int)winSize.width + tree8->getTextureRect().getMaxX();
		int randomTree = cocos2d::RandomHelper::random_int(limiter, (limiter * 2));
		tree8->setPositionX(randomTree);
	}
	else {
		tree8->setPositionX(tree8->getPositionX() + treeSpeed);
	}

	// Tracks
	float trackSpeed = 0.5 * GameManager::sharedGameManager()->getIncomingSpeed();
	if (delta > 1) initTracksPositions();
	else trackSpeed = GameManager::sharedGameManager()->getIncomingSpeed() * delta;
	track1->setPositionX(track1->getPositionX() + trackSpeed);
	track2->setPositionX(track2->getPositionX() + trackSpeed);
	track3->setPositionX(track3->getPositionX() + trackSpeed);
	track4->setPositionX(track4->getPositionX() + trackSpeed);
	track5->setPositionX(track5->getPositionX() + trackSpeed);
	track6->setPositionX(track6->getPositionX() + trackSpeed);
	// Check if track is offscreen, if so, move sky image to the end of second sky image
	if (track1->getPositionX() + track1->getTextureRect().getMaxX() < 0) {
		track1->setPositionX(track4->getTextureRect().getMaxX() + (track4->getPosition().x));
		track2->setPositionX(track5->getTextureRect().getMaxX() + (track5->getPosition().x));
		track3->setPositionX(track6->getTextureRect().getMaxX() + (track6->getPosition().x));
	}
	else if (track4->getPositionX() + track4->getTextureRect().getMaxX() < 0) {
		track4->setPositionX(track1->getTextureRect().getMaxX() + (track1->getPosition().x));
		track5->setPositionX(track2->getTextureRect().getMaxX() + (track2->getPosition().x));
		track6->setPositionX(track3->getTextureRect().getMaxX() + (track3->getPosition().x));
	}
}

void HelloWorld::initTracksPositions()
{
	track1->setPosition(Vec2(888.0f, 108.0f));
	track2->setPosition(Vec2(888.0f, track1->getPositionY() + (track1->getPositionY() * 2)));
	track3->setPosition(Vec2(888.0f, track1->getPositionY() + (track1->getPositionY() * 4)));
	track4->setPosition(Vec2((track1->getPosition().x + track1->getTextureRect().getMaxX()), track1->getPositionY()));
	track5->setPosition(Vec2((track2->getPosition().x + track2->getTextureRect().getMaxX()), (track1->getPositionY() * 3)));
	track6->setPosition(Vec2((track3->getPosition().x + track3->getTextureRect().getMaxX()), (track1->getPositionY() * 5)));
}

void HelloWorld::StartButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
		CCLOG("I touched the start, and I liked it! %d", type);

		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			this->StartGame();
		}
}

void HelloWorld::CreditsButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("But what if there's an after-credits sequence? %d", type);

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->StartCredits();
	}
}

void HelloWorld::MuteButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		if (muted == false) {
			muted = true;
			Mute_Button->setBright(false);

			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		}
		else if (muted == true) {
			muted = false;
			Mute_Button->setBright(true);

			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	}
}

void HelloWorld::PauseButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (GameManager::sharedGameManager()->getIsGameLive() == true) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			this->PauseGame();
		}
	}
}

void HelloWorld::ResumeButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->ResumeGame();
	}
}

void HelloWorld::ExitButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		this->EndGame();
	}
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

	auto startMoveTo = MoveTo::create(0.5, Vec2(winSize.width + Start_Button->getBoundingBox().getMaxX(), Start_Button->getPositionY())); // Take half a second to move off screen.
	Start_Button->runAction(startMoveTo);

	auto creditsMoveTo = MoveTo::create(0.5, Vec2(winSize.width + Credits_Button->getBoundingBox().getMaxX(), Credits_Button->getPositionY())); // Take half a second to move off screen.
	Credits_Button->runAction(creditsMoveTo);

	Mute_Button->setVisible(false);
}

void HelloWorld::PauseGame()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	GameManager::sharedGameManager()->setIsGamePaused(true);

	auto resumeMoveTo = MoveTo::create(0.5, Vec2(winSize.width / 2, Resume_Button->getPositionY())); // Take half a second to move on screen.
	Resume_Button->setVisible(true);
	Resume_Button->runAction(resumeMoveTo);

	auto exitMoveTo = MoveTo::create(0.5, Vec2(winSize.width / 2, Exit_Button->getPositionY())); // Take half a second to move on screen.
	Exit_Button->setVisible(true);
	Exit_Button->runAction(exitMoveTo);

	Pause_Score->setString("Score: " + StringUtils::format("%d", ((int)ScoreManager::sharedScoreManager()->getScore())));
	Pause_Score->setVisible(true);

	Pause_Highscore->setString("Highscore: " + StringUtils::format("%d", ((int)ScoreManager::sharedScoreManager()->getHighscore())));
	Pause_Highscore->setVisible(true);

	Mute_Button->setVisible(true);
}

void HelloWorld::ResumeGame()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	GameManager::sharedGameManager()->setIsGamePaused(false);

	auto resumeMoveTo = MoveTo::create(0.5, Vec2(winSize.width + Resume_Button->getContentSize().width, Resume_Button->getPositionY())); // Take half a second to move on screen.
	Resume_Button->setVisible(true);
	Resume_Button->runAction(resumeMoveTo);

	auto exitMoveTo = MoveTo::create(0.5, Vec2(winSize.width + Exit_Button->getContentSize().width, Exit_Button->getPositionY())); // Take half a second to move on screen.
	Exit_Button->setVisible(true);
	Exit_Button->runAction(exitMoveTo);

	Pause_Score->setVisible(false);
	Pause_Highscore->setVisible(false);

	Mute_Button->setVisible(false);
}

void HelloWorld::EndGame()
{
	GameManager::sharedGameManager()->setIsGamePaused(false);
	GameManager::sharedGameManager()->setIsGameLive(false);

	// Abandon high score. Players are not rewarded for quitting
	ScoreManager::sharedScoreManager()->resetScore();

	// Reset Speeds
	GameManager::sharedGameManager()->resetSpeeds();

	// Reset all objects to the default position
	initCocosElements();

	scene = 1;
}

void HelloWorld::StartCredits()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	scene = 3;

	//Set up credit text
	Credit_Text->setPosition(Vec2(840.0f, 0.0f));
	Credit_Text->setVisible(true);

	// Move buttons
	auto startMoveTo = MoveTo::create(0.5, Vec2(winSize.width + Start_Button->getBoundingBox().getMaxX(), Start_Button->getPositionY())); // Take half a second to move off screen.
	Start_Button->runAction(startMoveTo);

	auto creditsMoveTo = MoveTo::create(0.5, Vec2(winSize.width + Credits_Button->getBoundingBox().getMaxX(), Credits_Button->getPositionY())); // Take half a second to move off screen.
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

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (GameManager::sharedGameManager()->getIsGameLive() == true) {
		//Store the coordinates of where this touch began.
		Point touchPos = touch->getLocationInView();
		touchPos = Director::getInstance()->convertToGL(touchPos);
		touchPos = convertToNodeSpace(touchPos);

		initialTouchPos = touchPos;
		return true;
	}
	else {
		return false;
	}
}

void HelloWorld::onTouchEnded(cocos2d::Touch*, cocos2d::Event*)
{
	if (GameManager::sharedGameManager()->getIsGameLive() == true) {
		if (touchMoved == true)	// Deal with a touch-slide
		{
			int minimumMoved = 200;	// 200px must have been moved across to make Bob change lanes
			float diffX = finalTouchPos.x - initialTouchPos.x;
			float diffY = finalTouchPos.y - initialTouchPos.y;

			if (diffY > minimumMoved) {
				player->moveUpLane(player_sprite);
			}
			else if (diffY < (-1 * minimumMoved)) {
				player->moveDownLane(player_sprite);
			}
			else {
				// Nothing happens, player did not slide enough
			}

			// Reset touch
			touchMoved = false;
		}
	}
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (GameManager::sharedGameManager()->getIsGameLive() == true) {
		touchMoved = true;

		// Keep updating the final coords until this method is no longer called
		Point touchPos = touch->getLocationInView();
		touchPos = Director::getInstance()->convertToGL(touchPos);
		touchPos = convertToNodeSpace(touchPos);

		finalTouchPos = touchPos;
	}
}

void HelloWorld::onTouchCancelled(cocos2d::Touch*, cocos2d::Event*)
{

}