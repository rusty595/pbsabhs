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
		NoiseManager::sharedNoiseManager()->PlayBGM((char*)"dogs");
	}
	else
	{
		NoiseManager::sharedNoiseManager()->PlayBGM((char*)"no");
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
	auto creditNode = CSLoader::createNode("CreditScene.csb");
	addChild(creditNode);
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
	auto playerNode = CSLoader::createNode("Player.csb");
	addChild(playerNode);

	// Set up references
	Credit_Text = (ui::Text*)creditNode->getChildByName("Credit_Text");

	sky1 = (Sprite*)parallaxBackground->getChildByName("Sky");
	sky2 = (Sprite*)parallaxBackground->getChildByName("Sky_2");
	mountain1 = (Sprite*)parallaxBackground->getChildByName("Mountain_1");
	mountain2 = (Sprite*)parallaxBackground->getChildByName("Mountain_2");
	mountain3 = (Sprite*)parallaxBackground->getChildByName("Mountain_3");
	tree[0] = (Sprite*)parallaxBackground->getChildByName("Tree_1");
	tree[1] = (Sprite*)parallaxBackground->getChildByName("Tree_2");
	tree[2] = (Sprite*)parallaxBackground->getChildByName("Tree_3");
	tree[3] = (Sprite*)parallaxBackground->getChildByName("Tree_4");
	tree[4] = (Sprite*)parallaxBackground->getChildByName("Tree_5");
	tree[5] = (Sprite*)parallaxBackground->getChildByName("Tree_6");
	tree[6] = (Sprite*)parallaxBackground->getChildByName("Tree_7");
	tree[7] = (Sprite*)parallaxBackground->getChildByName("Tree_8");
	track[0] = (Sprite*)trackNode1->getChildByName("Track");
	track[1] = (Sprite*)trackNode2->getChildByName("Track");
	track[2] = (Sprite*)trackNode3->getChildByName("Track");
	track[3] = (Sprite*)trackNode4->getChildByName("Track");
	track[4] = (Sprite*)trackNode5->getChildByName("Track");
	track[5] = (Sprite*)trackNode6->getChildByName("Track");
	UI_Background = (Sprite*)UINode->getChildByName("UI_Background");

	Start_Button = static_cast<ui::Button*>(rootNode->getChildByName("Start_Button"));
	Credits_Button = static_cast<ui::Button*>(rootNode->getChildByName("Credits_Button"));
	Mute_Button = static_cast<ui::Button*>(rootNode->getChildByName("Mute_Button"));
	Pause_Button = static_cast<ui::Button*>(UINode->getChildByName("Pause_Button"));
	Resume_Button = static_cast<ui::Button*>(rootNode->getChildByName("Resume_Button"));
	Exit_Button = static_cast<ui::Button*>(rootNode->getChildByName("Exit_Button"));

	Logo = (Sprite*)rootNode->getChildByName("Logo");
	Game_Over = (Sprite*)rootNode->getChildByName("Game_Over"); // make a healthmeter ui::Text based on the score indicator

	Pause_Score = (ui::Text*)rootNode->getChildByName("Pause_Score");
	Pause_Highscore = (ui::Text*)rootNode->getChildByName("Pause_Highscore");
	score = (ui::Text*)UINode->getChildByName("Score");
	healthmeter = (ui::Text*)cocos2d::CSLoader::createNode("UI.csb")->getChildByName("Score"); // make a healthmeter ui::Text based on the score indicator
	addChild(healthmeter);

	player_sprite = (Sprite*)playerNode->getChildByName("Player_Skin_1");

	Black_Filter = (Sprite*)rootNode->getChildByName("Black_Filter");
}

void HelloWorld::initCocosElements()
{
	Black_Filter->setGlobalZOrder(200);

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

	limiter = (int)winSize.width + tree[0]->getTextureRect().getMaxX();
	for (int b0 = 0; b0 < 8; b0++) {
		random = cocos2d::RandomHelper::random_int(1, (limiter * 2));
		tree[b0]->setPosition(Vec2(random, 812.0f));
	}

	UI_Background->setPosition(Vec2(951.0f, 1025.5f));

	initTracksPositions();

	Start_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::StartButtonPressed, this));
	Credits_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::CreditsButtonPressed, this));
	Start_Button->setPosition(Vec2(winSize.width + Start_Button->getBoundingBox().getMaxX(), Start_Button->getPositionY()));
	Credits_Button->setPosition(Vec2(winSize.width + Credits_Button->getBoundingBox().getMaxX(), Credits_Button->getPositionY()));
	Logo->setPosition(Vec2(0 - Logo->getBoundingBox().getMaxX(), Logo->getPositionY()));

	auto startMoveTo = MoveTo::create(0.5, Vec2(1431.0f, 471.0f)); // Take half a second to move off screen.
	Start_Button->runAction(startMoveTo);

	auto creditsMoveTo = MoveTo::create(0.5, Vec2(1431.0f, 249.0f)); // Take half a second to move off screen.
	Credits_Button->runAction(creditsMoveTo);

	auto logoMoveTo = MoveTo::create(0.5, Vec2(winSize.width / 2, winSize.height / 2));
	Logo->runAction(logoMoveTo);

	//Game_Over->setVisible(false);
	Game_Over->setPositionX(winSize.width + Game_Over->getBoundingBox().getMaxX());

	Mute_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::MuteButtonPressed, this));
	Pause_Button->setPosition(Vec2(63.0f, 1025.5f));
	Pause_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::PauseButtonPressed, this));
	Resume_Button->setVisible(false);
	Resume_Button->setPositionX(winSize.width + Resume_Button->getContentSize().width);
	Resume_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::ResumeButtonPressed, this));
	Exit_Button->setVisible(false);
	Exit_Button->setPositionX(winSize.width + Exit_Button->getContentSize().width);
	Exit_Button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::ExitButtonPressed, this));

	score->setString(StringUtils::format("%d", 0));
	score->setVisible(false);
	score->setPosition(Vec2(winSize.width - 40.0f, winSize.height - 45.0f));
	healthmeter->setString(StringUtils::format("%d", GameManager::sharedGameManager()->health));
	healthmeter->setVisible(false);
	healthmeter->setPosition(Vec2(winSize.width - 260.0f, winSize.height - 45.0f));
	Credit_Text->setString("Programmers:\n David Smith\n Sam Head\n\nDog Handler:\n Sam Head\n\nDocumentation:\n David Smith\n\n");
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
			player->update(delta, player_sprite);
			if (player->isReady(player_sprite) == true) {
				GameManager::sharedGameManager()->setIsGameLive(true);
				score->setVisible(true);
				healthmeter->setVisible(true);

				auto scoreFadeIn = FadeIn::create(0.5);
				score->runAction(scoreFadeIn);
				healthmeter->runAction(scoreFadeIn);
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
				player->update(delta, player_sprite);
			}
			else {
				GameManager::sharedGameManager()->setPlayerRunning(true);
				player->update(delta, player_sprite);
			}

			// Score
			// Use player speed as a multiplier
			float multiplier = GameManager::sharedGameManager()->getPlayerSpeed() / 1000;
			ScoreManager::sharedScoreManager()->addToScore(multiplier * delta);
			//ScoreManager::sharedScoreManager()->resetScore();
			//ScoreManager::sharedScoreManager()->addToScore(dogs.size());		//debug to check number of dogs in memory
			score->setString(StringUtils::format("%d", ((int)ScoreManager::sharedScoreManager()->getScore())));

			// Dogs
			//make dogs
			updateDogs(delta);
			
			// Health
			healthmeter->setString(StringUtils::format("%d", GameManager::sharedGameManager()->health));

			// Check death
			if (GameManager::sharedGameManager()->getIsPlayerDead()) {
				PauseGame();
			}

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
	int range = (int)(GameManager::sharedGameManager()->getPlayerSpeed() / 150) + 1;
	if (dogs.size() < GameManager::sharedGameManager()->getPlayerSpeed() / 300.0f*2.0f)
	{
		dogs.pushBack(newDog(range));
	}
	for (int i = 0; i < (GameManager::sharedGameManager()->getPlayerSpeed() / 300.0f*2.0f)-1; i++) {
		Dog* d0 = dogs.at(i);
		d0->update(player->currentLane, inTouch, delta);
		// if dog has gone offscreen, renew its existence
		if (d0->destroy) { int b0 = cocos2d::RandomHelper::random_int(0, 65535); if (b0 % range == 0) d0->reset(b0 % 3, "dachs", Vec2(-32.0f, 32.0f), 20); else if (b0 % range == 1) d0->reset(b0 % 3, "abyssinianwirehairedtripe", Vec2(-32.0f, 32.0f), 20); else if (b0 % range == 2) d0->reset(b0 % 3, "skye", Vec2(-64.0f, 0.0f), 20); else if (b0 % range == 3) d0->reset(b0 % 3, "beagle", Vec2(-32.0f, 12.0f), 20); else if (b0 % range == 4) d0->reset(b0 % 3, "scot", Vec2(-64.0f, 8.0f), -10); else if (b0 % range == 5) d0->reset(b0 % 3, "obstacle", Vec2(-32.0f, 32.0f), -5); }
	}
}

Dog* HelloWorld::newDog(int range)
{
	int b0 = cocos2d::RandomHelper::random_int(0, 65535);
	if (b0 % range == 0) { Dog* sausage = new Dog(b0 % 3, "dachs", this, Vec2(-32.0f, 32.0f), 20); return sausage; }
	else if (b0 % range == 1) { Dog* gnob = new Dog(b0 % 3, "abyssinianwirehairedtripe", this, Vec2(-32.0f, 32.0f), 20); return gnob; }
	else if (b0 % range == 2) { Dog* pollux = new Dog(b0 % 3, "skye", this, Vec2(-64.0f, 0.0f), 20); return pollux; }
	else if (b0 % range == 3) { Dog* peanus = new Dog(b0 % 3, "beagle", this, Vec2(-32.0f, 12.0f), 20); return peanus; }
	else if (b0 % range == 4) { ScottishTerrier* ofthejedi = new ScottishTerrier(b0 % 3, this); return ofthejedi; }
	else if (b0 % range == 5) { Obstacle* tooz = new Obstacle(b0 % 3, this); return tooz; }
	else return newDog(range); // keep trying until a dog is made successfully. prevents range-based dog generation bias.
}

void HelloWorld::updateCredits(float delta)
{
	auto winSize = Director::getInstance()->getVisibleSize();

	// Check if credits have exited the screen
	// REMEMBER - Anchor point is taken at (0, 1) [Normalized coords]
	if ((Credit_Text->getPositionY() - Credit_Text->getContentSize().height) > tree[0]->getPositionY()-(tree[0]->getBoundingBox().size.height/2)) {
		EndCredits();
	}
	Credit_Text->setPosition(Vec2(Credit_Text->getPositionX() + (delta * 0.0f),
	Credit_Text->getPositionY() + (delta * 150.0f)));

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
	for (int b0=0;b0<8;b0++)
		if (tree[b0]->getPositionX() + tree[b0]->getTextureRect().getMaxX() < 0) {
			int limiter = (int)winSize.width + tree[b0]->getTextureRect().getMaxX();
			int randomTree = cocos2d::RandomHelper::random_int(limiter, (limiter * 2));
			tree[b0]->setPositionX(randomTree);
		}
		else {
			tree[b0]->setPositionX(tree[b0]->getPositionX() + treeSpeed);
		}

	// Tracks
	float trackSpeed = 0.5 * GameManager::sharedGameManager()->getIncomingSpeed();
	if (delta > 1) initTracksPositions();
	else trackSpeed = GameManager::sharedGameManager()->getIncomingSpeed() * delta;
	for (int b0 = 0; b0 < 6; b0++)
	{
		track[b0]->setPositionX(track[b0]->getPositionX() + trackSpeed);
		/*
		// Check if track is offscreen, if so, move track to the end of second track
		if (track[b0]->getPositionX() + track[b0]->getTextureRect().getMaxX() < 0) {
			if (b0 < 3){
				track[b0]->setPositionX(track[b0+3]->getTextureRect().getMaxX() + (track[b0+3]->getPosition().x));
			}
			else
			{
				track[b0]->setPositionX(track[b0-3]->getTextureRect().getMaxX() + (track[b0-3]->getPosition().x));
			}
		}
		*/
	}
	// Check if track is offscreen, if so, move track to the end of second track
	if (track[0]->getPositionX() + track[0]->getTextureRect().getMaxX() < 0) {
		track[0]->setPositionX(track[3]->getTextureRect().getMaxX() + (track[3]->getPosition().x));
		track[1]->setPositionX(track[4]->getTextureRect().getMaxX() + (track[4]->getPosition().x));
		track[2]->setPositionX(track[5]->getTextureRect().getMaxX() + (track[5]->getPosition().x));
	}
	else if (track[3]->getPositionX() + track[3]->getTextureRect().getMaxX() < 0) {
		track[3]->setPositionX(track[0]->getTextureRect().getMaxX() + (track[0]->getPosition().x));
		track[4]->setPositionX(track[1]->getTextureRect().getMaxX() + (track[1]->getPosition().x));
		track[5]->setPositionX(track[2]->getTextureRect().getMaxX() + (track[2]->getPosition().x));
	}
}

void HelloWorld::initTracksPositions()
{
	track[0]->setPosition(Vec2(888.0f, 108.0f));
	track[1]->setPosition(Vec2(888.0f, track[0]->getPositionY() + (track[0]->getPositionY() * 2)));
	track[2]->setPosition(Vec2(888.0f, track[0]->getPositionY() + (track[0]->getPositionY() * 4)));
	track[3]->setPosition(Vec2((track[0]->getPosition().x + track[0]->getTextureRect().getMaxX()), track[0]->getPositionY()));
	track[4]->setPosition(Vec2((track[1]->getPosition().x + track[1]->getTextureRect().getMaxX()), (track[0]->getPositionY() * 3)));
	track[5]->setPosition(Vec2((track[2]->getPosition().x + track[2]->getTextureRect().getMaxX()), (track[0]->getPositionY() * 5)));
}

void HelloWorld::StartButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
		CCLOG("bloodbath started %d", type);

		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			this->StartGame();
		}
}

void HelloWorld::CreditsButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("crediting started %d", type);

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
			NoiseManager::sharedNoiseManager()->PauseBGM();
			NoiseManager::sharedNoiseManager()->PauseSFX();
		}
		else if (muted == true) {
			muted = false;
			Mute_Button->setBright(true);
			NoiseManager::sharedNoiseManager()->ResumeBGM();
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

	auto startMoveTo = MoveTo::create(0.5, Vec2(1431.0f, 471.0f)); // Take half a second to move on screen.
	Start_Button->runAction(startMoveTo);

	auto creditsMoveTo = MoveTo::create(0.5, Vec2(1431.0f, 249.0f)); // Take half a second to move on screen.
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

	auto logoMoveTo = MoveTo::create(0.5, Vec2(0 - Logo->getBoundingBox().getMaxX(), Logo->getPositionY()));
	Logo->runAction(logoMoveTo);

	Mute_Button->setVisible(false);
	inTouch = false;
}

void HelloWorld::PauseGame()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	GameManager::sharedGameManager()->setIsGamePaused(true);

	if (!GameManager::sharedGameManager()->getIsPlayerDead()) {
		auto resumeMoveTo = MoveTo::create(0.5, Vec2(winSize.width / 2, Resume_Button->getPositionY())); // Take half a second to move on screen.
		Resume_Button->setVisible(true);
		Resume_Button->runAction(resumeMoveTo);
	}
	else {
		auto gameOverMoveTo = MoveTo::create(0.5, Vec2(winSize.width / 2, Game_Over->getPositionY())); // Take half a second to move on screen.
		Game_Over->setVisible(true);
		Game_Over->runAction(gameOverMoveTo);

		// Submit Highscore
		ScoreManager::sharedScoreManager()->compareScoreToHighscore();
	}

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

	// Reset Health
	GameManager::sharedGameManager()->resetHealth();

	// Reset all objects to the default position
	initCocosElements();

	for (int b0 = 0; b0 < dogs.size() - 1; b0++) dogs.at(b0)->reset();

	scene = 1;
}

void HelloWorld::StartCredits()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	scene = 3;
	for (int b0 = 0; b0 < 6; b0++) track[b0]->runAction(FadeOut::create(0.5f));
	for (int b0 = 0; b0 < 8; b0++) tree[b0]->runAction(FadeOut::create(0.25f));
	Logo->runAction(FadeOut::create(0.5f));
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
	for (int b0 = 0; b0 < 6; b0++) track[b0]->runAction(FadeIn::create(0.5f));
	for (int b0 = 0; b0 < 8; b0++) tree[b0]->runAction(FadeIn::create(0.75f));
	Logo->runAction(FadeIn::create(0.5f));
	Credit_Text->setVisible(false);
	StartMainMenu();
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (GameManager::sharedGameManager()->getIsGameLive() == true) {
		//Store the coordinates of where this touch began.
		Point touchPos = touch->getLocationInView();
		touchPos = Director::getInstance()->convertToGL(touchPos);
		touchPos = convertToNodeSpace(touchPos);

		initialTouchPos = touchPos;
		inTouch = true;
		return true;
	}
	else {
		return false;
	}
}

void HelloWorld::onTouchEnded(cocos2d::Touch*, cocos2d::Event*)
{
	if (GameManager::sharedGameManager()->getIsGameLive() == true) {
		inTouch = false;
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
		inTouch = false; // can't behead from a slide

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
