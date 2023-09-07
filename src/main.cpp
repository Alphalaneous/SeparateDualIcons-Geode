
#include <Geode/Geode.hpp>
#include <Geode/modify/GaragePage.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJRobotSprite.hpp>
#include <Geode/modify/ListButtonBar.hpp>

using namespace geode::prelude;

bool is2ndPlayer = true;
int icon = 1;
int ship = 1;
int ball = 1;
int UFO = 1;
int wave = 1;
int robot = 1;
int spider = 1;
int trail = 1;
int deathEffect = 1;
int primaryColor = 0;
int secondaryColor = 3;
bool hasGlow = false;
bool usesDefault = false;

IconType lastPlayer = IconType::Cube;

int callPosStreak = 0;

void setSelectorPosIcons(GaragePage* page, bool isP2);
CCSprite* getOriginalSelector(CCLayer* obj);
template<typename Base, typename T>
bool instanceof(const T ptr);
void setGlow(GJGarageLayer* garage);
void saveIcons();
void setGlowToggler(bool enabled, GJGarageLayer* garage);
template<typename O, typename T>
T getFromObjectContentSizeWidth(CCObject* obj, float width, int index);
void setSelectorPosColors(GJGarageLayer* page, bool isP2);
template<typename O, typename T>
T getFromObjectIndex(CCObject* obj, int index);
void setIconColor(GJGarageLayer* self, int ID, bool primary, bool isP2);
void setIcon(GJGarageLayer* self, IconType type, int ID, bool changeIcon, bool isP2);
bool isSecondPlayerInPlay(PlayerObject* playerObject);
void setPlayerColor(PlayerObject* playerObject);

class ButtonStuff {
public:
    void setGlowA(CCObject* target) {
        
        CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
        
        GJGarageLayer* garage = reinterpret_cast<GJGarageLayer*>(scene->getChildren()->objectAtIndex(0));

        CCMenu* menu = reinterpret_cast<CCMenu*>(garage->getChildByTag(23423));

        CCMenuItemToggler* toggler = reinterpret_cast<CCMenuItemToggler*>(menu->getChildByTag(67532));

        hasGlow = !toggler->isOn();

        setGlow(garage);
    }

    void setP2(CCObject* target) {

        CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

        GJGarageLayer* garage = reinterpret_cast<GJGarageLayer*>(scene->getChildren()->objectAtIndex(0));

        CCMenu* playerMenu = reinterpret_cast<CCMenu*>(garage->getChildByTag(74356));
        CCSprite* rightArrow = reinterpret_cast<CCSprite*>(playerMenu->getChildByTag(34730));
        CCSprite* leftArrow = reinterpret_cast<CCSprite*>(playerMenu->getChildByTag(34729));
        rightArrow->setVisible(true);
        leftArrow->setVisible(false);

        is2ndPlayer = true;
    }
    void setP1(CCObject* target) {

        CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

        GJGarageLayer* garage = reinterpret_cast<GJGarageLayer*>(scene->getChildren()->objectAtIndex(0));

        CCMenu* playerMenu = reinterpret_cast<CCMenu*>(garage->getChildByTag(74356));
        CCSprite* rightArrow = reinterpret_cast<CCSprite*>(playerMenu->getChildByTag(34730));
        CCSprite* leftArrow = reinterpret_cast<CCSprite*>(playerMenu->getChildByTag(34729));
        rightArrow->setVisible(false);
        leftArrow->setVisible(true);

        is2ndPlayer = false;
    }
    void setDefaultP2(CCObject* target) {
        CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

        GJGarageLayer* garage = reinterpret_cast<GJGarageLayer*>(scene->getChildren()->objectAtIndex(0));

        CCMenu* menu = reinterpret_cast<CCMenu*>(garage->getChildByTag(74356));

        CCMenuItemToggler* toggler = reinterpret_cast<CCMenuItemToggler*>(menu->getChildByTag(14736));

        usesDefault = !toggler->isOn();
    }

};

class $modify(GaragePage){

	bool init(IconType type, GJGarageLayer* pGarage, cocos2d::SEL_MenuHandler pSelectCallback){

		if (!GaragePage::init(type, pGarage, pSelectCallback)) return false;

		CCSprite* playerTwoSelect = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
		playerTwoSelect->setTag(69543);
		playerTwoSelect->setColor({ 0, 255, 255 });
		playerTwoSelect->setScale(0.85f);
		playerTwoSelect->setZOrder(101);

		CCLabelBMFont* p1Label = CCLabelBMFont::create("P1", "bigFont.fnt");
		CCLabelBMFont* p2Label = CCLabelBMFont::create("P2", "bigFont.fnt");

		p1Label->setScale(0.25);
		p1Label->setPosition({ 10, 31 });
		p1Label->setColor({ 255, 175, 0 });
		p2Label->setScale(0.25);
		p2Label->setPosition({ 28, 8 });
		p2Label->setColor({ 0, 255, 255 });

		CCSprite* playerOneSelect = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
		playerOneSelect->setTag(69542);
		playerOneSelect->setColor({ 255, 175, 0 });
		playerOneSelect->setScale(0.85f);
		playerOneSelect->setZOrder(101);

		playerOneSelect->addChild(p1Label);
		playerTwoSelect->addChild(p2Label);


		this->addChild(playerTwoSelect);
		this->addChild(playerOneSelect);
		


		setSelectorPosIcons(this, true);
		setSelectorPosIcons(this, false);


		return true;
	}
};

class $modify(ListButtonBar){


	void switchedPage(int param_1){
		CCLayer* parent = reinterpret_cast<CCLayer*>(this->getParent());

		ListButtonBar::switchedPage(param_1);

		if (parent->getChildByTag(69543)) {

			GaragePage* garagePage = reinterpret_cast<GaragePage*>(parent);

			setSelectorPosIcons(garagePage, true);
			setSelectorPosIcons(garagePage, false);
		}
		else if(this->getID() == "color-selection-menu") {


			GJGarageLayer* garageLayer = reinterpret_cast<GJGarageLayer*>(parent);

			setSelectorPosColors(garageLayer, true);
			setSelectorPosColors(garageLayer, false);
		}
	}
};


class $modify(GJGarageLayer){

	bool init(){
		if (!GJGarageLayer::init()) return false;

		is2ndPlayer = false;

		CCSprite* unlockTxt = getFromObjectContentSizeWidth<CCLayer*, CCSprite*>(this, 105.750, 0);
		unlockTxt->setVisible(false);

		CCSprite* selectSpriteP1primary = getFromObjectContentSizeWidth<CCLayer*, CCSprite*>(this, 38, 0);
		CCSprite* selectSpriteP1secondary = getFromObjectContentSizeWidth<CCLayer*, CCSprite*>(this, 38, 1);

		selectSpriteP1primary->setColor({ 255, 175, 0 });
		selectSpriteP1secondary->setColor({ 255, 175, 0 });

		selectSpriteP1primary->setTag(16547);
		selectSpriteP1secondary->setTag(16548);

		CCSprite* selectSpriteP2primary = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
		CCSprite* selectSpriteP2secondary = CCSprite::createWithSpriteFrameName("GJ_select_001.png");

		selectSpriteP2primary->setColor({ 0, 255, 255 });
		selectSpriteP2secondary->setColor({ 0, 255, 255 });

		selectSpriteP2primary->setScale(0.8f);
		selectSpriteP2secondary->setScale(0.8f);


		selectSpriteP2primary->setTag(16549);
		selectSpriteP2secondary->setTag(16550);

		this->addChild(selectSpriteP2primary);
		this->addChild(selectSpriteP2secondary);

		CCLabelBMFont* p1Label = CCLabelBMFont::create("P1", "bigFont.fnt");
		CCLabelBMFont* p1Label2 = CCLabelBMFont::create("P1", "bigFont.fnt");

		CCLabelBMFont* p2Label = CCLabelBMFont::create("P2", "bigFont.fnt");
		CCLabelBMFont* p2Label2 = CCLabelBMFont::create("P2", "bigFont.fnt");

		p1Label->setScale(0.25);
		p1Label->setPosition({ 10, 31 });
		p1Label->setColor({ 255, 175, 0 });

		p1Label2->setScale(0.25);
		p1Label2->setPosition({ 10, 31 });
		p1Label2->setColor({ 255, 175, 0 });

		p2Label->setScale(0.25);
		p2Label->setPosition({ 28, 8 });
		p2Label->setColor({ 0, 255, 255 });

		p2Label2->setScale(0.25);
		p2Label2->setPosition({ 28, 8 });
		p2Label2->setColor({ 0, 255, 255 });

		selectSpriteP1primary->addChild(p1Label);
		selectSpriteP1secondary->addChild(p1Label2);

		selectSpriteP2primary->addChild(p2Label);
		selectSpriteP2secondary->addChild(p2Label2);

		selectSpriteP1primary->setZOrder(101);
		selectSpriteP1secondary->setZOrder(101);

		selectSpriteP2primary->setZOrder(101);
		selectSpriteP2secondary->setZOrder(101);

		CCMenuItemToggler* defaultToggler = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(ButtonStuff::setDefaultP2), 0.7f);
		defaultToggler->setTag(14736);
		defaultToggler->setPosition(106, -44);
		defaultToggler->setScale(0.675f);;



		CCLabelBMFont* defaultToggleLabel = CCLabelBMFont::create("Default P2", "bigFont.fnt");
		defaultToggleLabel->setPosition(176, -44);
		defaultToggleLabel->setScale(0.3f);
		defaultToggleLabel->setAnchorPoint({ 1, .5 });

		

		SimplePlayer* mainPlayer = reinterpret_cast<SimplePlayer*>(this->getChildByID("player-icon"));

		this->removeChild(mainPlayer);

		CCSprite* pointerLeft = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
		CCSprite* pointerRight = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");

		pointerRight->setFlipX(true);
		pointerLeft->setScale(0.4f);
		pointerRight->setScale(0.4f);

		pointerLeft->setTag(34729);
		pointerRight->setTag(34730);

		pointerLeft->setPosition({-90, 0});
		pointerRight->setPosition({ 90, 0 });

		pointerRight->setVisible(false);

		CCAction* moveLeft = CCMoveBy::create(0.5, {5, 0});
		CCAction* moveRight = CCMoveBy::create(0.5, {-5, 0});

		CCArray* actions = new CCArray();
		actions->addObject(moveLeft);
		actions->addObject(moveRight);

		CCSequence* moveSeq = CCSequence::create(actions);

		CCAction* moveLeft2 = CCMoveBy::create(0.5, { -5, 0 });
		CCAction* moveRight2 = CCMoveBy::create(0.5, { 5, 0 });

		CCArray* actions2 = new CCArray();
		actions2->addObject(moveLeft2);
		actions2->addObject(moveRight2);

		CCSequence* moveSeq2 = CCSequence::create(actions2);


		pointerLeft->runAction(CCRepeatForever::create(moveSeq));
		pointerRight->runAction(CCRepeatForever::create(moveSeq2));


		CCMenu* playerSelect = CCMenu::create();
		playerSelect->setPosition(mainPlayer->getPosition());

		SimplePlayer* secondPlayer = SimplePlayer::create(0);
		secondPlayer->setTag(43221);
		secondPlayer->setScale(1.6f);

		playerSelect->addChild(pointerLeft);
		playerSelect->addChild(pointerRight);

		mainPlayer->setContentSize({ 40,40 });
		secondPlayer->setContentSize({ 40,40 });


		CCMenuItemSpriteExtra* mainPlayerBtn = CCMenuItemSpriteExtra::create(mainPlayer, this, menu_selector(ButtonStuff::setP1));
		CCMenuItemSpriteExtra* secondPlayerBtn = CCMenuItemSpriteExtra::create(secondPlayer, this, menu_selector(ButtonStuff::setP2));
		secondPlayerBtn->setPosition({ 40, 0 });

		mainPlayerBtn->setPosition({ -40, 0 });

		mainPlayerBtn->setTag(1);
		secondPlayerBtn->setTag(2);




		playerSelect->setTag(74356);

		playerSelect->addChild(defaultToggler);
		playerSelect->addChild(defaultToggleLabel);

		playerSelect->addChild(mainPlayerBtn);
		playerSelect->addChild(secondPlayerBtn);

		mainPlayer->setAnchorPoint({ 0, 0 });
		secondPlayer->setAnchorPoint({ 0, 0 });

		CCMenu* menu = CCMenu::create();
		menu->setTag(23423);


		CCMenuItemToggler* toggler = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(ButtonStuff::setGlowA), 0.7f);
		toggler->setTag(67532);
		toggler->setPosition(-165, -38);

		

		CCLabelBMFont* glowP2Label = CCLabelBMFont::create("Glow P2", "bigFont.fnt");
		glowP2Label->setPosition(-73.25, -37);
		glowP2Label->setScale(0.5);
		glowP2Label->setAnchorPoint({1, .5});

		menu->addChild(glowP2Label);
		menu->addChild(toggler);
		this->addChild(menu);

		CCLabelBMFont* bothLabel = CCLabelBMFont::create("(Both Players)", "bigFont.fnt");
		bothLabel->setPosition(menu->getPosition().x - 50, menu->getPosition().y - 68);
		bothLabel->setScale(0.5);
		bothLabel->setAnchorPoint({ 1, .5 });
		bothLabel->setTag(63092);
		bothLabel->setVisible(false);
		//284 to 234
		//160 to 92

		this->addChild(bothLabel);


		int ID = 0;

		switch (lastPlayer)
		{
		case IconType::Cube:
			ID = icon;
			break;
		case IconType::Ship:
			ID = ship;
			break;
		case IconType::Ball:
			ID = ball;
			break;
		case IconType::Ufo:
			ID = UFO;
			break;
		case IconType::Wave:
			ID = wave;
			break;
		case IconType::Robot:
			ID = robot;
			break;
		case IconType::Spider:
			ID = spider;
			break;
		case IconType::DeathEffect:
			ID = deathEffect;
			break;
		case IconType::Special:
			ID = trail;
			break;
		default:
			break;
		}

		menu->setVisible(false);
		secondPlayer->updatePlayerFrame(ID, lastPlayer);
		this->addChild(playerSelect);

		setIconColor(this, primaryColor, true, true);
		setIconColor(this, secondaryColor, false, false);

		setSelectorPosColors(this, true);
		setSelectorPosColors(this, false);

		defaultToggler->toggle(usesDefault);
		
		GaragePage* cubePage = reinterpret_cast<GaragePage*>(this->getChildByID("cube-selection-menu"));
		setSelectorPosIcons(cubePage, true);
		setSelectorPosIcons(cubePage, false);

		GaragePage* shipPage = reinterpret_cast<GaragePage*>(this->getChildByID("ship-selection-menu"));
		setSelectorPosIcons(shipPage, true);
		setSelectorPosIcons(shipPage, false);

		GaragePage* ballPage = reinterpret_cast<GaragePage*>(this->getChildByID("ball-selection-menu"));
		setSelectorPosIcons(ballPage, true);
		setSelectorPosIcons(ballPage, false);

		GaragePage* ufoPage = reinterpret_cast<GaragePage*>(this->getChildByID("ufo-selection-menu"));
		setSelectorPosIcons(ufoPage, true);
		setSelectorPosIcons(ufoPage, false);

		GaragePage* wavePage = reinterpret_cast<GaragePage*>(this->getChildByID("wave-selection-menu"));
		setSelectorPosIcons(wavePage, true);
		setSelectorPosIcons(wavePage, false);

		GaragePage* robotPage = reinterpret_cast<GaragePage*>(this->getChildByID("robot-selection-menu"));
		setSelectorPosIcons(robotPage, true);
		setSelectorPosIcons(robotPage, false);

		GaragePage* spiderPage = reinterpret_cast<GaragePage*>(this->getChildByID("spider-selection-menu"));
		setSelectorPosIcons(spiderPage, true);
		setSelectorPosIcons(spiderPage, false);

		GaragePage* trailPage = reinterpret_cast<GaragePage*>(this->getChildByID("trail-selection-menu"));
		setSelectorPosIcons(trailPage, true);
		setSelectorPosIcons(trailPage, false);

		GaragePage* deathEffectPage = reinterpret_cast<GaragePage*>(this->getChildByID("death-effect-selection-menu"));
		setSelectorPosIcons(deathEffectPage, true);
		setSelectorPosIcons(deathEffectPage, false);

		return true;
	}

	void onTab(int tabNumber){
		GJGarageLayer::onTab(tabNumber);

		if (this->getChildByTag(63092)) {
			this->getChildByTag(63092)->setVisible(false);

			setGlowToggler(tabNumber == 99, this);
			if (tabNumber == 98) {
				this->getChildByTag(63092)->setVisible(true);
			}
		}
	}

	/*void showBlackCircleWave(){ //todo add these
		
	}

	void showCircleWave(){ //todo add these
		
	}*/

	void onPlayerIcon(CCObject* param_1){
		if (is2ndPlayer) {
			icon = param_1->getTag();
			setIcon(this, IconType::Cube, icon, true, true);
		}
		else {
			GJGarageLayer::onPlayerIcon(param_1);
			setIcon(this, IconType::Cube, icon, true, false);
		}
	}

	void onShipIcon(CCObject* param_1){
		if (is2ndPlayer) {
			ship = param_1->getTag();
			setIcon(this, IconType::Ship, ship, true, true);
		}
		else {
			GJGarageLayer::onShipIcon(param_1);
			setIcon(this, IconType::Ship, ship, true, false);
		}
	}

	void onBallIcon(CCObject* param_1){
		if (is2ndPlayer) {
			ball = param_1->getTag();
			setIcon(this, IconType::Ball, ball, true, true);

		}
		else {
			GJGarageLayer::onBallIcon(param_1);
			setIcon(this, IconType::Ball, ball, true, false);
		}
	}

	void onBirdIcon(CCObject* param_1){
		if (is2ndPlayer) {
			UFO = param_1->getTag();
			setIcon(this, IconType::Ufo, UFO, true, true);

		}
		else {
			GJGarageLayer::onBirdIcon(param_1);
			setIcon(this, IconType::Ufo, UFO, true, false);
		}
	}

	void onDartIcon(CCObject* param_1){
		if (is2ndPlayer) {
			wave = param_1->getTag();
			setIcon(this, IconType::Wave, wave, true, true);
		}
		else {
			GJGarageLayer::onDartIcon(param_1);
			setIcon(this, IconType::Wave, wave, true, false);
		}
	}

	void onRobotIcon(CCObject* param_1){
		if (is2ndPlayer) {
			robot = param_1->getTag();
			setIcon(this, IconType::Robot, robot, true, true);

		}
		else {
			GJGarageLayer::onRobotIcon(param_1);
			setIcon(this, IconType::Robot, robot, true, false);
		}
	}

	void onSpiderIcon(CCObject* param_1){
		if (is2ndPlayer) {
			spider = param_1->getTag();
			setIcon(this, IconType::Spider, spider, true, true);

		}
		else {
			GJGarageLayer::onSpiderIcon(param_1);
			setIcon(this, IconType::Spider, spider, true, false);
		}
	}

	void onPlayerTrail(CCObject* param_1){
		if (is2ndPlayer) {
			trail = param_1->getTag();
			setIcon(this, IconType::Special, trail, false, true);

		}
		else {
			GJGarageLayer::onPlayerTrail(param_1);
			setIcon(this, IconType::Special, trail, false, false);
		}
	}

	void onPlayerDeathEffect(CCObject* param_1){
		GJGarageLayer::onPlayerDeathEffect(param_1);
 		setIcon(this, IconType::DeathEffect, deathEffect, false, false);
	}

	void onPlayerColor1(CCObject* param_1){
		if (is2ndPlayer) {
			primaryColor = param_1->getTag();
			setIconColor(this, primaryColor, true, true);
		}
		else {
			GJGarageLayer::onPlayerColor1(param_1);
			setIconColor(this, primaryColor, true, false);
		}
	}

	void onPlayerColor2(CCObject* param_1){
		if (is2ndPlayer) {
			secondaryColor = param_1->getTag();
			setIconColor(this, secondaryColor, false, true);
		}
		else {
			GJGarageLayer::onPlayerColor2(param_1);
			setIconColor(this, secondaryColor, false, false);
		}
	}
};


class $modify(PlayerObject){

	void updatePlayerBirdFrame(int param_1){
		PlayerObject::updatePlayerBirdFrame(param_1);
		if (!usesDefault) {
			setPlayerColor(this);
			if (isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerBirdFrame(UFO);
			}
		}
	}

	void updatePlayerDartFrame(int param_1){
		PlayerObject::updatePlayerDartFrame(param_1);
		if (!usesDefault) {
			setPlayerColor(this);
			if (isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerDartFrame(wave);
			}
		}
	}

	void updatePlayerFrame(int param_1){
		PlayerObject::updatePlayerFrame(param_1);
		if (!usesDefault) {
			setPlayerColor(this);
			if (isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerFrame(icon);
			}
		}
	}

	void updatePlayerRollFrame(int param_1){
		PlayerObject::updatePlayerRollFrame(param_1);
		if (!usesDefault) {
			setPlayerColor(this);
			if (isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerRollFrame(ball);
			}
		}
	}

	void updatePlayerShipFrame(int param_1){
		PlayerObject::updatePlayerShipFrame(param_1);
		if (!usesDefault) {
			setPlayerColor(this);
			if (isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerShipFrame(ship);
			}
		}
	}

	void setupStreak(){
		if (!usesDefault) {
			int origStreak = GameManager::sharedState()->getPlayerStreak();

			if (PlayLayer::get()) {
				if (callPosStreak == 1) {
					GameManager::sharedState()->setPlayerStreak(trail);
				}

				callPosStreak++;
				if (callPosStreak == 2) callPosStreak = 0;
			}

			PlayerObject::setupStreak();

			GameManager::sharedState()->setPlayerStreak(origStreak);
		}
		else {
			PlayerObject::setupStreak();
		}
	}

	void switchedToMode(GameObjectType param_1){
		PlayerObject::switchedToMode(param_1);
		if (!usesDefault) {
			if (isSecondPlayerInPlay(this)) {
				if (param_1 == GameObjectType::RobotPortal) {
					PlayLayer::get()->m_player2->m_robotSprite->updateFrame(robot);
				}
				if (param_1 == GameObjectType::SpiderPortal) {
					PlayLayer::get()->m_player2->m_spiderSprite->updateFrame(spider);
				}
			}
		}
		setPlayerColor(this);
	}

};

class $modify(PlayLayer){

	bool init(GJGameLevel* level){
		callPosStreak = 0;
		if (!PlayLayer::init(level)) return false;

		if (!usesDefault) {

			PlayerObject* player2 = this->m_player2;

			if (player2->m_isShip) {
				player2->updatePlayerShipFrame(ship);
			}
			else if (player2->m_isBall) {
				player2->updatePlayerRollFrame(ball);
			}
			else if (player2->m_isBird) {
				player2->updatePlayerBirdFrame(UFO);
			}
			else if (player2->m_isDart) {
				player2->updatePlayerDartFrame(wave);
			}
			else if (player2->m_isRobot) {
				player2->m_robotSprite->updateFrame(robot);
			}
			else if (player2->m_isSpider) {
				player2->m_spiderSprite->updateFrame(spider);
			}
			else {
				player2->updatePlayerFrame(icon);
			}

			setPlayerColor(player2);
		}

		return true;
	}

};

class $modify(GJRobotSprite){

	void updateFrame(int iconID){
		if (!usesDefault && PlayLayer::get() && PlayLayer::get()->m_player2) {
			setPlayerColor(PlayLayer::get()->m_player2);
		}
		
		GJRobotSprite::updateFrame(iconID);
	}

};

void setSelectorPosIcons(GaragePage* page, bool isP2) {
    
    int ID = 0;
    bool hasSecondSelect = true;
    int tag = 0;

    CCSprite* originalSelector = getOriginalSelector(page);
    originalSelector->setOpacity(0);



    GameManager* manager = GameManager::sharedState();

    CCSprite* selector = nullptr;

    CCSprite* selector1 = reinterpret_cast<CCSprite*>(page->getChildByTag(69542));
    CCSprite* selector2 = reinterpret_cast<CCSprite*>(page->getChildByTag(69543));

    selector1->setZOrder(101);
    selector2->setZOrder(101);

    if (isP2) {
        selector = selector2;
    }
    else {
        selector = selector1;
    }

    selector->setZOrder(102);


	std::string pageID = page->getID();


	if(pageID == "cube-selection-menu"){
 		page->setTag(10);
        if (isP2) ID = icon;
        else ID = manager->getPlayerFrame();
        tag = 0;
	}
	else if(pageID == "ship-selection-menu"){
 		page->setTag(11);
        if (isP2) ID = ship;
        else ID = manager->getPlayerShip();
        tag = 1;
	}
	else if(pageID == "ball-selection-menu"){
		page->setTag(12);
        if (isP2) ID = ball;
        else ID = manager->getPlayerBall();
        tag = 2;
	}
	else if(pageID == "ufo-selection-menu"){
		page->setTag(13);
        if (isP2) ID = UFO;
        else ID = manager->getPlayerBird();
        tag = 3;
	}
	else if(pageID == "wave-selection-menu"){
 		page->setTag(14);
        if (isP2) ID = wave;
        else ID = manager->getPlayerDart();
        tag = 4;
	}
	else if(pageID == "robot-selection-menu"){
		page->setTag(15);
        if (isP2) ID = robot;
        else ID = manager->getPlayerRobot();
        tag = 5;
	}
	else if(pageID == "spider-selection-menu"){
		page->setTag(16);
        if (isP2) ID = spider;
        else ID = manager->getPlayerSpider();
        tag = 6;
	}
	else if(pageID == "death-effect-selection-menu"){
		page->setTag(17);
        hasSecondSelect = false;
        if (!isP2) ID = manager->getPlayerDeathEffect();
        tag = 98;
	}
	else if(pageID == "trail-selection-menu"){
		page->setTag(18);
        if (isP2) ID = trail;
        else ID = manager->getPlayerStreak();
        tag = 99;
	}

    CCLabelBMFont* label = reinterpret_cast<CCLabelBMFont*>(selector->getChildren()->objectAtIndex(0));

    if (!hasSecondSelect) {
        label->setVisible(false);
        selector->setColor({ 255,255,255 });
    }
    else {
        label->setVisible(true);
        if (isP2) {
            selector->setColor({ 0, 255, 255 });
        }
        else {
            selector->setColor({ 255, 175, 0 });
        }
    }

    if (hasSecondSelect || !isP2) {

        ListButtonBar* listButtonBar = reinterpret_cast<ListButtonBar*>(page->getChildByTag(tag));

        if (listButtonBar) {

            BoomScrollLayer* boomScrollLayer = reinterpret_cast<BoomScrollLayer*>(listButtonBar->getChildren()->objectAtIndex(0));
            CCLayer* extendedLayer = reinterpret_cast<CCLayer*>(boomScrollLayer->getChildren()->objectAtIndex(0));


            int pageNum = 0;
            for (unsigned int i = 0; i < extendedLayer->getChildrenCount(); i++) {
                if (ID <= ((pageNum + 1) * 36)) {
                    break;
                }
                pageNum++;
            }

            int xExtened = extendedLayer->getPositionX();

            CCLayer* pageLayer = reinterpret_cast<CCLayer*>(extendedLayer->getChildren()->objectAtIndex(pageNum));

            if(pageLayer->getPositionX() * -1 == xExtened){
                selector->setVisible(true);

                int IDtoPageValue = ID - pageNum * 36;

                int xPos = ((IDtoPageValue - 1) % 12) + 1;
                int yPos = ((IDtoPageValue - 1) / 12) + 1;

                auto winSize = CCDirector::sharedDirector()->getWinSize();

                float centerX = winSize.width / 2;
                float centerY = winSize.height / 2;

                selector->setPosition({ centerX - 165 + 30 * (xPos - 1), centerY - 6 - 30 * (yPos - 1) });
            }
            else {
                selector->setVisible(false);
            }
        }
    }
    else {
        selector->setVisible(false);
    }
}

void setSelectorPosColors(GJGarageLayer* page, bool isP2) {

    int ID = 0;
    bool hasSecondSelect = true;
    int tag = 0;

    GameManager* manager = GameManager::sharedState();


    CCSprite* selector1p1 = reinterpret_cast<CCSprite*>(page->getChildByTag(16547));
    CCSprite* selector2p1 = reinterpret_cast<CCSprite*>(page->getChildByTag(16548));

    if (!selector1p1 || !selector2p1) return;

    selector1p1->setZOrder(101);
    selector2p1->setZOrder(101);

    CCSprite* selector1p2 = reinterpret_cast<CCSprite*>(page->getChildByTag(16549));
    CCSprite* selector2p2 = reinterpret_cast<CCSprite*>(page->getChildByTag(16550));

    selector1p2->setZOrder(101);
    selector2p2->setZOrder(101);

    if (isP2) {
        selector1p2->setZOrder(102);
        selector2p2->setZOrder(102);
    }
    else {
        selector1p1->setZOrder(102);
        selector2p1->setZOrder(102);
    }


    if (isP2) {
        for (int c = 0; c < 2; c++) {

            if (c == 0) ID = primaryColor;
            if (c == 1) ID = secondaryColor;

            ListButtonBar* listButtonBar = reinterpret_cast<ListButtonBar*>(page->getChildByTag(1));

            if (listButtonBar) {

                BoomScrollLayer* boomScrollLayer = reinterpret_cast<BoomScrollLayer*>(listButtonBar->getChildren()->objectAtIndex(0));
                CCLayer* extendedLayer = getFromObjectIndex<CCLayer*, CCLayer*>(boomScrollLayer, 0);

                int posInPage = 0;
                int pageNum = 0;
                for (unsigned int i = 0; i < extendedLayer->getChildrenCount(); i++) {

                    CCLayer* pageLayer = reinterpret_cast<CCLayer*>(extendedLayer->getChildren()->objectAtIndex(i));
                    CCMenu* menu = reinterpret_cast<CCMenu*>(pageLayer->getChildren()->objectAtIndex(0));

                    for (unsigned int j = 0; j < menu->getChildrenCount() / 2; j++) {
                        if (menu->getChildren()->objectAtIndex(j)->getTag() == ID) {
                            posInPage = j;
                            pageNum = i;
                            goto to_break;
                        }
                    }
                }
                to_break:

                int xExtened = extendedLayer->getPositionX();
                CCLayer* pageLayer = reinterpret_cast<CCLayer*>(extendedLayer->getChildren()->objectAtIndex(pageNum));

                if (pageLayer->getPositionX() * -1 == xExtened) {

                    auto winSize = CCDirector::sharedDirector()->getWinSize();

                    float centerX = winSize.width / 2;

                    if (c == 0) {
                        selector1p2->setVisible(true);
                        selector1p2->setPosition({ centerX - 159.8f + 29.035f * (posInPage), 55.4f });
                    }
                    if (c == 1) {
                        selector2p2->setVisible(true);
                        selector2p2->setPosition({ centerX - 159.8f + 29.035f * (posInPage), 26.4f });
                    }
                }
                else {
                    if (c == 0) {
                        selector1p2->setVisible(false);
                    }
                    if (c == 1) {
                        selector2p2->setVisible(false);
                    }
                }
            }
        }
    }
}


void setGlow(GJGarageLayer* garage) {

    CCMenu* playerMenu = reinterpret_cast<CCMenu*>(garage->getChildByTag(74356));
    CCMenuItemSpriteExtra* button = reinterpret_cast<CCMenuItemSpriteExtra*>(playerMenu->getChildByTag(2));
    SimplePlayer* simplePlayer = reinterpret_cast<SimplePlayer*>(button->getChildren()->objectAtIndex(0));
    
    simplePlayer->setGlowOutline(hasGlow);
    simplePlayer->updateColors();
    saveIcons();
}

void setGlowToggler(bool enabled, GJGarageLayer* garage) {

    if (garage->getChildByTag(23423)) {
        CCMenu* menu = reinterpret_cast<CCMenu*>(garage->getChildByTag(23423));
        if (menu->getChildByTag(67532)) {

            CCMenuItemToggler* toggler = reinterpret_cast<CCMenuItemToggler*>(menu->getChildByTag(67532));

            if (enabled) {
                menu->setVisible(true);
                if (hasGlow && !toggler->isOn()) {
                    toggler->activate();
                }
            }
            else {
                menu->setVisible(false);
            }
        }
    }
}

CCSprite* getOriginalSelector(CCLayer* obj) {
    CCObject* pObj = nullptr;

    CCARRAY_FOREACH(obj->getChildren(), pObj) {
        CCNode* currentNode = (CCNode*)pObj;

        if (instanceof<CCSprite*>(pObj)) {
            
            if (pObj->getTag() == 69543 || pObj->getTag() == 69542) continue;
            return reinterpret_cast<CCSprite*>(pObj);
        }
    }
    return nullptr;
}

template<typename Base, typename T>
bool instanceof(const T ptr) {
    return dynamic_cast<const Base>(ptr) != nullptr;
}

void saveIcons() {
    std::ofstream configFile("p2IconData", std::ios::out | std::ios::trunc);
    configFile << std::to_string(icon) << ",";
    configFile << std::to_string(ship) << ",";
    configFile << std::to_string(ball) << ",";
    configFile << std::to_string(UFO) << ",";
    configFile << std::to_string(wave) << ",";
    configFile << std::to_string(robot) << ",";
    configFile << std::to_string(spider) << ",";
    configFile << std::to_string(trail) << ",";
    configFile << std::to_string(deathEffect) << ",";
    configFile << std::to_string(primaryColor) << ",";
    configFile << std::to_string(secondaryColor) << ",";
    configFile << std::to_string((int)hasGlow) << ",";
    configFile << std::to_string((int)lastPlayer) << ",";
    configFile << std::to_string((int)usesDefault) << ",";

    configFile.close();
}

template<typename O, typename T>
T getFromObjectContentSizeWidth(CCObject* obj, float width, int index) {
    CCObject* pObj = nullptr;

    int idx = 0;

    CCARRAY_FOREACH(dynamic_cast<O>(obj)->getChildren(), pObj) {
        CCNode* currentNode = (CCNode*)pObj;
        float objWidth = currentNode->getContentSize().width;

        T obj = dynamic_cast<T>(pObj);

        if (instanceof<T>(obj)) {
            if (objWidth == width) {
                if (idx == index) return obj;
                idx++;
            }
        }
    }
    return nullptr;
}

template<typename O, typename T>
T getFromObjectIndex(CCObject* obj, int index) {
    CCObject* pObj = nullptr;

    int idx = 0;

    CCARRAY_FOREACH(dynamic_cast<O>(obj)->getChildren(), pObj) {
        CCNode* currentNode = (CCNode*)pObj;

        T obj = dynamic_cast<T>(pObj);

        if (instanceof<T>(obj)) {
            if (idx == index) return obj;
            idx++;
        }
    }
    return nullptr;
}

void setIconColor(GJGarageLayer* self, int ID, bool primary, bool isP2) {

    if (self->getChildByTag(74356)) {
        CCMenu* playerMenu = reinterpret_cast<CCMenu*>(self->getChildByTag(74356));
        if (playerMenu->getChildByTag(2)) {
            CCMenuItemSpriteExtra* button = reinterpret_cast<CCMenuItemSpriteExtra*>(playerMenu->getChildByTag(2));
            SimplePlayer* simplePlayer = reinterpret_cast<SimplePlayer*>(button->getChildren()->objectAtIndex(0));

            ccColor3B color = GameManager::sharedState()->colorForIdx(ID);

            if (primary) simplePlayer->setColor(color);
            else simplePlayer->setSecondColor(color);

            simplePlayer->setGlowOutline(hasGlow);
            simplePlayer->updateColors();


            setSelectorPosColors(self, isP2);

            saveIcons();
        }
    }
}

void setIcon(GJGarageLayer* self, IconType type, int ID, bool changeIcon, bool isP2) {

    if (self->getChildByTag(74356)) {
        CCMenu* playerMenu = reinterpret_cast<CCMenu*>(self->getChildByTag(74356));
        if (playerMenu->getChildByTag(2)) {

            if (isP2) {

                CCMenuItemSpriteExtra* button = reinterpret_cast<CCMenuItemSpriteExtra*>(playerMenu->getChildByTag(2));
                SimplePlayer* simplePlayer = reinterpret_cast<SimplePlayer*>(button->getChildren()->objectAtIndex(0));

                if (changeIcon) {
                    lastPlayer = type;
                    simplePlayer->updatePlayerFrame(ID, type);
                }
            }
            int pos = 0;

            GaragePage* garagePage;


            switch (type)
            {
            case IconType::Cube:
				garagePage = reinterpret_cast<GaragePage*>(self->getChildByID("cube-selection-menu"));
                break;
            case IconType::Ship:
                garagePage = reinterpret_cast<GaragePage*>(self->getChildByID("ship-selection-menu"));
                break;
            case IconType::Ball:
                garagePage = reinterpret_cast<GaragePage*>(self->getChildByID("ball-selection-menu"));
                break;
            case IconType::Ufo:
                garagePage = reinterpret_cast<GaragePage*>(self->getChildByID("ufo-selection-menu"));
                break;
            case IconType::Wave:
                garagePage = reinterpret_cast<GaragePage*>(self->getChildByID("wave-selection-menu"));
                break;
            case IconType::Robot:
                garagePage = reinterpret_cast<GaragePage*>(self->getChildByID("robot-selection-menu"));
                break;
            case IconType::Spider:
                garagePage = reinterpret_cast<GaragePage*>(self->getChildByID("spider-selection-menu"));
                break;
            case IconType::DeathEffect:
                garagePage = reinterpret_cast<GaragePage*>(self->getChildByID("death-effect-selection-menu"));
                break;
            case IconType::Special:
                garagePage = reinterpret_cast<GaragePage*>(self->getChildByID("trail-selection-menu"));
                break;
            default:
                break;
            }


            setSelectorPosIcons(garagePage, isP2);

            if (isP2) {
                saveIcons();
            }
        }
    }
}

void setPlayerColor(PlayerObject* playerObject) {
    
	if(!usesDefault){

		if (isSecondPlayerInPlay(playerObject)) {
			ccColor3B colorPrimary = GameManager::sharedState()->colorForIdx(primaryColor);
			ccColor3B colorSecondary = GameManager::sharedState()->colorForIdx(secondaryColor);

			playerObject->setColor(colorPrimary);
			playerObject->setSecondColor(colorSecondary);
			playerObject->m_hasGlow = hasGlow;
			
			CCSpriteBatchNode* glowNode = GJBaseGameLayer::get()->m_batchNodePlayerGlow;

			if(glowNode->getChildren()->count() > 1){

				CCSprite* p2Glow = reinterpret_cast<CCSprite*>(glowNode->getChildren()->objectAtIndex(1));

				CCArray* glowSprites = p2Glow->getChildren();

				for(unsigned int i = 0; i < glowSprites->count(); i++){
					CCSprite* sprite = reinterpret_cast<CCSprite*>(glowSprites->objectAtIndex(i));
					sprite->setColor(colorSecondary);
				}
			}
			playerObject->updateGlowColor();
		}
	}
}


bool isSecondPlayerInPlay(PlayerObject* playerObject) {
    if (playerObject) {
        if (PlayLayer::get()) {
            if (PlayLayer::get()->m_player2) {
                return playerObject == PlayLayer::get()->m_player2;
            }
        }
    }
    return false;
}

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void loadIcons() {
    
    if (!is_file_exist("p2IconData")) {
        return;
    }

    std::ifstream configFile("p2IconData");

    try {
        std::stringstream buffer;
        buffer << configFile.rdbuf();

        std::string value = buffer.str();
        std::vector<std::string> values = split(value, ",");
        icon = std::stoi(values.at(0));
        ship = std::stoi(values.at(1));
        ball = std::stoi(values.at(2));
        UFO = std::stoi(values.at(3));
        wave = std::stoi(values.at(4));
        robot = std::stoi(values.at(5));
        spider = std::stoi(values.at(6));
        trail = std::stoi(values.at(7));
        deathEffect = std::stoi(values.at(8));
        primaryColor = std::stoi(values.at(9));
        secondaryColor = std::stoi(values.at(10));
        hasGlow = std::stoi(values.at(11));
        lastPlayer = (IconType)std::stoi(values.at(12));
        usesDefault = std::stoi(values.at(13));
    }
    catch (std::exception& E) {
        std::cout << E.what() << std::endl;
    }

    configFile.close();
}


$on_mod(Loaded) {

    loadIcons();

}