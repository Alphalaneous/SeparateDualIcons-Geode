#include "ExtraStuff.hpp"

using namespace geode::prelude;

void ExtraStuff::setGlowA(CCObject* target) {
        
    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
    
    GJGarageLayer* garage = reinterpret_cast<GJGarageLayer*>(scene->getChildren()->objectAtIndex(0));

    CCMenu* menu = reinterpret_cast<CCMenu*>(garage->getChildByTag(23423));

    CCMenuItemToggler* toggler = reinterpret_cast<CCMenuItemToggler*>(menu->getChildByTag(67532));

    IconData::hasGlow = !toggler->isOn();

    setGlow(garage);
}

void ExtraStuff::setP2(CCObject* target) {

    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

    GJGarageLayer* garage = reinterpret_cast<GJGarageLayer*>(scene->getChildren()->objectAtIndex(0));

    CCMenu* playerMenu = reinterpret_cast<CCMenu*>(garage->getChildByTag(74356));
    CCSprite* rightArrow = reinterpret_cast<CCSprite*>(playerMenu->getChildByTag(34730));
    CCSprite* leftArrow = reinterpret_cast<CCSprite*>(playerMenu->getChildByTag(34729));
    rightArrow->setVisible(true);
    leftArrow->setVisible(false);

    IconData::is2ndPlayer = true;
}
void ExtraStuff::setP1(CCObject* target) {

    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

    GJGarageLayer* garage = reinterpret_cast<GJGarageLayer*>(scene->getChildren()->objectAtIndex(0));

    CCMenu* playerMenu = reinterpret_cast<CCMenu*>(garage->getChildByTag(74356));
    CCSprite* rightArrow = reinterpret_cast<CCSprite*>(playerMenu->getChildByTag(34730));
    CCSprite* leftArrow = reinterpret_cast<CCSprite*>(playerMenu->getChildByTag(34729));
    rightArrow->setVisible(false);
    leftArrow->setVisible(true);

    IconData::is2ndPlayer = false;
}
void ExtraStuff::setDefaultP2(CCObject* target) {

    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();

    GJGarageLayer* garage = reinterpret_cast<GJGarageLayer*>(scene->getChildren()->objectAtIndex(0));

    CCMenu* menu = reinterpret_cast<CCMenu*>(garage->getChildByTag(74356));

    CCMenuItemToggler* toggler = reinterpret_cast<CCMenuItemToggler*>(menu->getChildByTag(14736));

    IconData::usesDefault = !toggler->isOn();
}

void ExtraStuff::setSelectorPosIcons(GaragePage* page, bool isP2) {

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


    if (pageID == "cube-selection-menu") {
        page->setTag(10);
        if (isP2) ID = IconData::icon;
        else ID = manager->getPlayerFrame();
        tag = 0;
    }
    else if (pageID == "ship-selection-menu") {
        page->setTag(11);
        if (isP2) ID = IconData::ship;
        else ID = manager->getPlayerShip();
        tag = 1;
    }
    else if (pageID == "ball-selection-menu") {
        page->setTag(12);
        if (isP2) ID = IconData::ball;
        else ID = manager->getPlayerBall();
        tag = 2;
    }
    else if (pageID == "ufo-selection-menu") {
        page->setTag(13);
        if (isP2) ID = IconData::UFO;
        else ID = manager->getPlayerBird();
        tag = 3;
    }
    else if (pageID == "wave-selection-menu") {
        page->setTag(14);
        if (isP2) ID = IconData::wave;
        else ID = manager->getPlayerDart();
        tag = 4;
    }
    else if (pageID == "robot-selection-menu") {
        page->setTag(15);
        if (isP2) ID = IconData::robot;
        else ID = manager->getPlayerRobot();
        tag = 5;
    }
    else if (pageID == "spider-selection-menu") {
        page->setTag(16);
        if (isP2) ID = IconData::spider;
        else ID = manager->getPlayerSpider();
        tag = 6;
    }
    else if (pageID == "death-effect-selection-menu") {
        page->setTag(17);
        hasSecondSelect = false;
        if (!isP2) ID = manager->getPlayerDeathEffect();
        tag = 98;
    }
    else if (pageID == "trail-selection-menu") {
        page->setTag(18);
        if (isP2) ID = IconData::trail;
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

            if (pageLayer->getPositionX() * -1 == xExtened) {
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

void ExtraStuff::setSelectorPosColors(GJGarageLayer* page, bool isP2) {

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

            if (c == 0) ID = IconData::primaryColor;
            if (c == 1) ID = IconData::secondaryColor;

            ListButtonBar* listButtonBar = reinterpret_cast<ListButtonBar*>(page->getChildByTag(1));

            if (listButtonBar) {

                BoomScrollLayer* boomScrollLayer = reinterpret_cast<BoomScrollLayer*>(listButtonBar->getChildren()->objectAtIndex(0));
                CCLayer* extendedLayer = reinterpret_cast<CCLayer*>(boomScrollLayer->getChildren()->objectAtIndex(0));

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


void ExtraStuff::setGlow(GJGarageLayer* garage) {

    CCMenu* playerMenu = reinterpret_cast<CCMenu*>(garage->getChildByTag(74356));
    CCMenuItemSpriteExtra* button = reinterpret_cast<CCMenuItemSpriteExtra*>(playerMenu->getChildByTag(2));
    SimplePlayer* simplePlayer = reinterpret_cast<SimplePlayer*>(button->getChildren()->objectAtIndex(0));

    simplePlayer->setGlowOutline(IconData::hasGlow);
    simplePlayer->updateColors();
    saveIcons();
}

void ExtraStuff::setGlowToggler(bool enabled, GJGarageLayer* garage) {

    if (garage->getChildByTag(23423)) {
        CCMenu* menu = reinterpret_cast<CCMenu*>(garage->getChildByTag(23423));
        if (menu->getChildByTag(67532)) {

            CCMenuItemToggler* toggler = reinterpret_cast<CCMenuItemToggler*>(menu->getChildByTag(67532));

            if (enabled) {
                menu->setVisible(true);
                if (IconData::hasGlow && !toggler->isOn()) {
                    toggler->activate();
                }
            }
            else {
                menu->setVisible(false);
            }
        }
    }
}

CCSprite* ExtraStuff::getOriginalSelector(CCLayer* obj) {
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



void ExtraStuff::saveIcons() {
    std::ofstream configFile("p2IconData", std::ios::out | std::ios::trunc);
    configFile << std::to_string(IconData::icon) << ",";
    configFile << std::to_string(IconData::ship) << ",";
    configFile << std::to_string(IconData::ball) << ",";
    configFile << std::to_string(IconData::UFO) << ",";
    configFile << std::to_string(IconData::wave) << ",";
    configFile << std::to_string(IconData::robot) << ",";
    configFile << std::to_string(IconData::spider) << ",";
    configFile << std::to_string(IconData::trail) << ",";
    configFile << std::to_string(IconData::deathEffect) << ",";
    configFile << std::to_string(IconData::primaryColor) << ",";
    configFile << std::to_string(IconData::secondaryColor) << ",";
    configFile << std::to_string((int)IconData::hasGlow) << ",";
    configFile << std::to_string((int)IconData::lastPlayer) << ",";
    configFile << std::to_string((int)IconData::usesDefault) << ",";

    configFile.close();
}





void ExtraStuff::setIconColor(GJGarageLayer* self, int ID, bool primary, bool isP2) {

    if (self->getChildByTag(74356)) {
        CCMenu* playerMenu = reinterpret_cast<CCMenu*>(self->getChildByTag(74356));
        if (playerMenu->getChildByTag(2)) {
            CCMenuItemSpriteExtra* button = reinterpret_cast<CCMenuItemSpriteExtra*>(playerMenu->getChildByTag(2));
            SimplePlayer* simplePlayer = reinterpret_cast<SimplePlayer*>(button->getChildren()->objectAtIndex(0));

            ccColor3B color = GameManager::sharedState()->colorForIdx(ID);

            if (primary) simplePlayer->setColor(color);
            else simplePlayer->setSecondColor(color);

            simplePlayer->setGlowOutline(IconData::hasGlow);
            simplePlayer->updateColors();


            setSelectorPosColors(self, isP2);

            saveIcons();
        }
    }
}

void ExtraStuff::setIcon(GJGarageLayer* self, IconType type, int ID, bool changeIcon, bool isP2) {

    if (self->getChildByTag(74356)) {
        CCMenu* playerMenu = reinterpret_cast<CCMenu*>(self->getChildByTag(74356));
        if (playerMenu->getChildByTag(2)) {

            if (isP2) {

                CCMenuItemSpriteExtra* button = reinterpret_cast<CCMenuItemSpriteExtra*>(playerMenu->getChildByTag(2));
                SimplePlayer* simplePlayer = reinterpret_cast<SimplePlayer*>(button->getChildren()->objectAtIndex(0));

                if (changeIcon) {
                    IconData::lastPlayer = type;
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

void ExtraStuff::setPlayerColor(PlayerObject* playerObject) {

    if (!IconData::usesDefault) {

        if (isSecondPlayerInPlay(playerObject)) {
            ccColor3B colorPrimary = GameManager::sharedState()->colorForIdx(IconData::primaryColor);
            ccColor3B colorSecondary = GameManager::sharedState()->colorForIdx(IconData::secondaryColor);

            playerObject->setColor(colorPrimary);
            playerObject->setSecondColor(colorSecondary);
            playerObject->m_hasGlow = IconData::hasGlow;

            CCSpriteBatchNode* glowNode = GJBaseGameLayer::get()->m_batchNodePlayerGlow;

            if (glowNode->getChildren()->count() > 1) {

                CCSprite* p2Glow = reinterpret_cast<CCSprite*>(glowNode->getChildren()->objectAtIndex(1));

                CCArray* glowSprites = p2Glow->getChildren();

                for (unsigned int i = 0; i < glowSprites->count(); i++) {
                    CCSprite* sprite = reinterpret_cast<CCSprite*>(glowSprites->objectAtIndex(i));
                    sprite->setColor(colorSecondary);
                }
            }
            playerObject->updateGlowColor();
        }
    }
}


bool ExtraStuff::isSecondPlayerInPlay(PlayerObject* playerObject) {
    if (playerObject) {
        if (PlayLayer::get()) {
            if (PlayLayer::get()->m_player2) {
                return playerObject == PlayLayer::get()->m_player2;
            }
        }
    }
    return false;
}

std::vector<std::string> ExtraStuff::split(std::string s, std::string delimiter) {
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

bool ExtraStuff::fileExists(std::string fileName){
    std::ifstream infile(fileName);
    return infile.good();
}

void ExtraStuff::loadIcons() {

    if (!fileExists("p2IconData")) {
        return;
    }

    std::ifstream configFile("p2IconData");

    try {
        std::stringstream buffer;
        buffer << configFile.rdbuf();

        std::string value = buffer.str();
        std::vector<std::string> values = split(value, ",");
        IconData::icon = std::stoi(values.at(0));
        IconData::ship = std::stoi(values.at(1));
        IconData::ball = std::stoi(values.at(2));
        IconData::UFO = std::stoi(values.at(3));
        IconData::wave = std::stoi(values.at(4));
        IconData::robot = std::stoi(values.at(5));
        IconData::spider = std::stoi(values.at(6));
        IconData::trail = std::stoi(values.at(7));
        IconData::deathEffect = std::stoi(values.at(8));
        IconData::primaryColor = std::stoi(values.at(9));
        IconData::secondaryColor = std::stoi(values.at(10));
        IconData::hasGlow = std::stoi(values.at(11));
        IconData::lastPlayer = (IconType)std::stoi(values.at(12));
        IconData::usesDefault = std::stoi(values.at(13));
    }
    catch (std::exception& E) {
        std::cout << E.what() << std::endl;
    }

    configFile.close();
}

