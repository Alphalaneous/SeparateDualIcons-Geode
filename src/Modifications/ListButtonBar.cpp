#include <Geode/modify/ListButtonBar.hpp>
#include "../ExtraStuff.hpp"

class $modify(ListButtonBar) {

	void switchedPage(int param_1) {
		CCLayer* parent = reinterpret_cast<CCLayer*>(this->getParent());

		ListButtonBar::switchedPage(param_1);

		if (parent->getChildByTag(69543)) {

			GaragePage* garagePage = reinterpret_cast<GaragePage*>(parent);

			ExtraStuff::setSelectorPosIcons(garagePage, true);
			ExtraStuff::setSelectorPosIcons(garagePage, false);
		}
		else if (this->getID() == "color-selection-menu") {


			GJGarageLayer* garageLayer = reinterpret_cast<GJGarageLayer*>(parent);

			ExtraStuff::setSelectorPosColors(garageLayer, true);
			ExtraStuff::setSelectorPosColors(garageLayer, false);
		}
	}
};