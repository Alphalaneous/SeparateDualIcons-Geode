#include <Geode/modify/GJRobotSprite.hpp>
#include "../ExtraStuff.hpp"

class $modify(GJRobotSprite) {

	void updateFrame(int iconID) {
		if (!IconData::usesDefault && PlayLayer::get() && PlayLayer::get()->m_player2) {
			ExtraStuff::setPlayerColor(PlayLayer::get()->m_player2);
		}

		GJRobotSprite::updateFrame(iconID);
	}

};