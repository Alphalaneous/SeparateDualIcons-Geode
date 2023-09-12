#include <Geode/modify/GaragePage.hpp>
#include "../ExtraStuff.hpp"

class $modify(GaragePage) {

	bool init(IconType type, GJGarageLayer * pGarage, cocos2d::SEL_MenuHandler pSelectCallback) {

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


		ExtraStuff::setSelectorPosIcons(this, true);
		ExtraStuff::setSelectorPosIcons(this, false);


		return true;
	}
};