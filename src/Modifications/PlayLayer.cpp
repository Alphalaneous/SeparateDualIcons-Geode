#include <Geode/modify/PlayLayer.hpp>
#include "../ExtraStuff.hpp"


class $modify(PlayLayer) {

	bool init(GJGameLevel* level) {
		IconData::callPosStreak = 0;
		if (!PlayLayer::init(level)) return false;

		if (!IconData::usesDefault) {

			PlayerObject* player2 = this->m_player2;

			if (player2->m_isShip) {
				player2->updatePlayerShipFrame(IconData::ship);
			}
			else if (player2->m_isBall) {
				player2->updatePlayerRollFrame(IconData::ball);
			}
			else if (player2->m_isBird) {
				player2->updatePlayerBirdFrame(IconData::UFO);
			}
			else if (player2->m_isDart) {
				player2->updatePlayerDartFrame(IconData::wave);
			}
			else if (player2->m_isRobot) {
				player2->m_robotSprite->updateFrame(IconData::robot);
			}
			else if (player2->m_isSpider) {
				player2->m_spiderSprite->updateFrame(IconData::spider);
			}
			else {
				player2->updatePlayerFrame(IconData::icon);
			}

			ExtraStuff::setPlayerColor(player2);
		}

		return true;
	}

};