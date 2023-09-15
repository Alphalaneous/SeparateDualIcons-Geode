#include <Geode/modify/GJGarageLayer.hpp>
#include "../ExtraStuff.hpp"

class $modify(GJGarageLayer) {

	bool init() {
		if (!GJGarageLayer::init()) return false;

		IconData::is2ndPlayer = false;

		CCSprite* unlockTxt = ExtraStuff::getFromObjectContentSizeWidthBetween<CCLayer*, CCSprite*>(this, 90, 120, 0);
		unlockTxt->setVisible(false);

		CCSprite* selectSpriteP1primary = ExtraStuff::getFromObjectContentSizeWidthBetween<CCLayer*, CCSprite*>(this, 30, 40, 0);
		CCSprite* selectSpriteP1secondary = ExtraStuff::getFromObjectContentSizeWidthBetween<CCLayer*, CCSprite*>(this, 30, 40, 1);

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

		CCMenuItemToggler* defaultToggler = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(ExtraStuff::setDefaultP2), 0.7f);
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

		pointerLeft->setPosition({ -90, 0 });
		pointerRight->setPosition({ 90, 0 });

		pointerRight->setVisible(false);

		CCAction* moveLeft = CCMoveBy::create(0.5, { 5, 0 });
		CCAction* moveRight = CCMoveBy::create(0.5, { -5, 0 });

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


		CCMenuItemSpriteExtra* mainPlayerBtn = CCMenuItemSpriteExtra::create(mainPlayer, this, menu_selector(ExtraStuff::setP1));
		CCMenuItemSpriteExtra* secondPlayerBtn = CCMenuItemSpriteExtra::create(secondPlayer, this, menu_selector(ExtraStuff::setP2));
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


		CCMenuItemToggler* toggler = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(ExtraStuff::setGlowA), 0.7f);
		toggler->setTag(67532);
		toggler->setPosition(-165, -38);



		CCLabelBMFont* glowP2Label = CCLabelBMFont::create("Glow P2", "bigFont.fnt");
		glowP2Label->setPosition(-73.25, -37);
		glowP2Label->setScale(0.5);
		glowP2Label->setAnchorPoint({ 1, .5 });

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

		switch (IconData::lastPlayer)
		{
		case IconType::Cube:
			ID = IconData::icon;
			break;
		case IconType::Ship:
			ID = IconData::ship;
			break;
		case IconType::Ball:
			ID = IconData::ball;
			break;
		case IconType::Ufo:
			ID = IconData::UFO;
			break;
		case IconType::Wave:
			ID = IconData::wave;
			break;
		case IconType::Robot:
			ID = IconData::robot;
			break;
		case IconType::Spider:
			ID = IconData::spider;
			break;
		case IconType::DeathEffect:
			ID = IconData::deathEffect;
			break;
		case IconType::Special:
			ID = IconData::trail;
			break;
		default:
			break;
		}

		menu->setVisible(false);
		secondPlayer->updatePlayerFrame(ID, IconData::lastPlayer);
		this->addChild(playerSelect);

		ExtraStuff::setIconColor(this, IconData::primaryColor, true, true);
		ExtraStuff::setIconColor(this, IconData::secondaryColor, false, false);

		ExtraStuff::setSelectorPosColors(this, true);
		ExtraStuff::setSelectorPosColors(this, false);

		defaultToggler->toggle(IconData::usesDefault);

		GaragePage* cubePage = reinterpret_cast<GaragePage*>(this->getChildByID("cube-selection-menu"));
		ExtraStuff::setSelectorPosIcons(cubePage, true);
		ExtraStuff::setSelectorPosIcons(cubePage, false);

		GaragePage* shipPage = reinterpret_cast<GaragePage*>(this->getChildByID("ship-selection-menu"));
		ExtraStuff::setSelectorPosIcons(shipPage, true);
		ExtraStuff::setSelectorPosIcons(shipPage, false);

		GaragePage* ballPage = reinterpret_cast<GaragePage*>(this->getChildByID("ball-selection-menu"));
		ExtraStuff::setSelectorPosIcons(ballPage, true);
		ExtraStuff::setSelectorPosIcons(ballPage, false);

		GaragePage* ufoPage = reinterpret_cast<GaragePage*>(this->getChildByID("ufo-selection-menu"));
		ExtraStuff::setSelectorPosIcons(ufoPage, true);
		ExtraStuff::setSelectorPosIcons(ufoPage, false);

		GaragePage* wavePage = reinterpret_cast<GaragePage*>(this->getChildByID("wave-selection-menu"));
		ExtraStuff::setSelectorPosIcons(wavePage, true);
		ExtraStuff::setSelectorPosIcons(wavePage, false);

		GaragePage* robotPage = reinterpret_cast<GaragePage*>(this->getChildByID("robot-selection-menu"));
		ExtraStuff::setSelectorPosIcons(robotPage, true);
		ExtraStuff::setSelectorPosIcons(robotPage, false);

		GaragePage* spiderPage = reinterpret_cast<GaragePage*>(this->getChildByID("spider-selection-menu"));
		ExtraStuff::setSelectorPosIcons(spiderPage, true);
		ExtraStuff::setSelectorPosIcons(spiderPage, false);

		GaragePage* trailPage = reinterpret_cast<GaragePage*>(this->getChildByID("trail-selection-menu"));
		ExtraStuff::setSelectorPosIcons(trailPage, true);
		ExtraStuff::setSelectorPosIcons(trailPage, false);

		GaragePage* deathEffectPage = reinterpret_cast<GaragePage*>(this->getChildByID("death-effect-selection-menu"));
		ExtraStuff::setSelectorPosIcons(deathEffectPage, true);
		ExtraStuff::setSelectorPosIcons(deathEffectPage, false);

		return true;
	}

	void onTab(int tabNumber) {
		GJGarageLayer::onTab(tabNumber);

		if (this->getChildByTag(63092)) {
			this->getChildByTag(63092)->setVisible(false);

			ExtraStuff::setGlowToggler(tabNumber == 99, this);
			if (tabNumber == 98) {
				this->getChildByTag(63092)->setVisible(true);
			}
		}
	}

	void showBlackCircleWave() {
		//do nothing
	}

	void showCircleWave() {
		//do nothing
	}

	void onPlayerIcon(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::icon = param_1->getTag();
			ExtraStuff::setIcon(this, IconType::Cube, IconData::icon, true, true);
		}
		else {
			GJGarageLayer::onPlayerIcon(param_1);
			ExtraStuff::setIcon(this, IconType::Cube, IconData::icon, true, false);
		}
	}

	void onShipIcon(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::ship = param_1->getTag();
			ExtraStuff::setIcon(this, IconType::Ship, IconData::ship, true, true);
		}
		else {
			GJGarageLayer::onShipIcon(param_1);
			ExtraStuff::setIcon(this, IconType::Ship, IconData::ship, true, false);
		}
	}

	void onBallIcon(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::ball = param_1->getTag();
			ExtraStuff::setIcon(this, IconType::Ball, IconData::ball, true, true);

		}
		else {
			GJGarageLayer::onBallIcon(param_1);
			ExtraStuff::setIcon(this, IconType::Ball, IconData::ball, true, false);
		}
	}

	void onBirdIcon(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::UFO = param_1->getTag();
			ExtraStuff::setIcon(this, IconType::Ufo, IconData::UFO, true, true);

		}
		else {
			GJGarageLayer::onBirdIcon(param_1);
			ExtraStuff::setIcon(this, IconType::Ufo, IconData::UFO, true, false);
		}
	}

	void onDartIcon(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::wave = param_1->getTag();
			ExtraStuff::setIcon(this, IconType::Wave, IconData::wave, true, true);
		}
		else {
			GJGarageLayer::onDartIcon(param_1);
			ExtraStuff::setIcon(this, IconType::Wave, IconData::wave, true, false);
		}
	}

	void onRobotIcon(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::robot = param_1->getTag();
			ExtraStuff::setIcon(this, IconType::Robot, IconData::robot, true, true);

		}
		else {
			GJGarageLayer::onRobotIcon(param_1);
			ExtraStuff::setIcon(this, IconType::Robot, IconData::robot, true, false);
		}
	}

	void onSpiderIcon(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::spider = param_1->getTag();
			ExtraStuff::setIcon(this, IconType::Spider, IconData::spider, true, true);

		}
		else {
			GJGarageLayer::onSpiderIcon(param_1);
			ExtraStuff::setIcon(this, IconType::Spider, IconData::spider, true, false);
		}
	}

	void onPlayerTrail(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::trail = param_1->getTag();
			ExtraStuff::setIcon(this, IconType::Special, IconData::trail, false, true);

		}
		else {
			GJGarageLayer::onPlayerTrail(param_1);
			ExtraStuff::setIcon(this, IconType::Special, IconData::trail, false, false);
		}
	}

	void onPlayerDeathEffect(CCObject * param_1) {
		GJGarageLayer::onPlayerDeathEffect(param_1);
		ExtraStuff::setIcon(this, IconType::DeathEffect, IconData::deathEffect, false, false);
	}

	void onPlayerColor1(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::primaryColor = param_1->getTag();
			ExtraStuff::setIconColor(this, IconData::primaryColor, true, true);
		}
		else {
			GJGarageLayer::onPlayerColor1(param_1);
			ExtraStuff::setIconColor(this, IconData::primaryColor, true, false);
		}
	}

	void onPlayerColor2(CCObject * param_1) {
		if (IconData::is2ndPlayer) {
			IconData::secondaryColor = param_1->getTag();
			ExtraStuff::setIconColor(this, IconData::secondaryColor, false, true);
		}
		else {
			GJGarageLayer::onPlayerColor2(param_1);
			ExtraStuff::setIconColor(this, IconData::secondaryColor, false, false);
		}
	}
};