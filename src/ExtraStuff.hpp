#include <Geode/Geode.hpp>
#include "IconData.hpp"

using namespace geode::prelude;

class ExtraStuff {

public:
    void setGlowA(CCObject* target);
    void setP2(CCObject* target);
    void setP1(CCObject* target);
    void setDefaultP2(CCObject* target);

    static void setSelectorPosIcons(GaragePage* page, bool isP2);
    static void setSelectorPosColors(GJGarageLayer* page, bool isP2);
    static void setGlow(GJGarageLayer* garage);
    static void setGlowToggler(bool enabled, GJGarageLayer* garage);
    static CCSprite* getOriginalSelector(CCLayer* obj);

    template<typename Base, typename T>
    static bool instanceof(const T ptr) {
        return dynamic_cast<const Base>(ptr) != nullptr;
    }
    static void saveIcons();

    template<typename O, typename T>
    static T getFromWidth(CCObject* obj, float width, int index) {
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
    static T getFromObjectIndex(CCObject* obj, int index) {
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
    static void setIconColor(GJGarageLayer* self, int ID, bool primary, bool isP2);
    static void setIcon(GJGarageLayer* self, IconType type, int ID, bool changeIcon, bool isP2);
    static void setPlayerColor(PlayerObject* playerObject);
    static bool isSecondPlayerInPlay(PlayerObject* playerObject);
    static std::vector<std::string> split(std::string s, std::string delimiter);
    static bool fileExists(std::string fileName);
    static void loadIcons();

};
