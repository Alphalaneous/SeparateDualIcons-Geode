#include <Geode/modify/PlayerObject.hpp>
#include "../ExtraStuff.hpp"

class $modify(PlayerObject) {

	void updatePlayerBirdFrame(int param_1) {
		PlayerObject::updatePlayerBirdFrame(param_1);
		if (!IconData::usesDefault) {
			ExtraStuff::setPlayerColor(this);
			if (ExtraStuff::isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerBirdFrame(IconData::UFO);
			}
		}
	}

	void updatePlayerDartFrame(int param_1) {
		PlayerObject::updatePlayerDartFrame(param_1);
		if (!IconData::usesDefault) {
			ExtraStuff::setPlayerColor(this);
			if (ExtraStuff::isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerDartFrame(IconData::wave);
			}
		}
	}

	void updatePlayerFrame(int param_1) {
		PlayerObject::updatePlayerFrame(param_1);
		if (!IconData::usesDefault) {
			ExtraStuff::setPlayerColor(this);
			if (ExtraStuff::isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerFrame(IconData::icon);
			}
		}
	}

	void updatePlayerRollFrame(int param_1) {
		PlayerObject::updatePlayerRollFrame(param_1);
		if (!IconData::usesDefault) {
			ExtraStuff::setPlayerColor(this);
			if (ExtraStuff::isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerRollFrame(IconData::ball);
			}
		}
	}

	void updatePlayerShipFrame(int param_1) {
		PlayerObject::updatePlayerShipFrame(param_1);
		if (!IconData::usesDefault) {
			ExtraStuff::setPlayerColor(this);
			if (ExtraStuff::isSecondPlayerInPlay(this)) {
				PlayerObject::updatePlayerShipFrame(IconData::ship);
			}
		}
	}

	void setupStreak() {
		if (!IconData::usesDefault) {
			int origStreak = GameManager::sharedState()->getPlayerStreak();

			if (PlayLayer::get()) {
				if (IconData::callPosStreak == 1) {
					GameManager::sharedState()->setPlayerStreak(IconData::trail);
				}

				IconData::callPosStreak++;
				if (IconData::callPosStreak == 2) IconData::callPosStreak = 0;
			}

			PlayerObject::setupStreak();

			GameManager::sharedState()->setPlayerStreak(origStreak);
		}
		else {
			PlayerObject::setupStreak();
		}
	}

	void switchedToMode(GameObjectType param_1) {
		PlayerObject::switchedToMode(param_1);
		if (!IconData::usesDefault) {
			if (ExtraStuff::isSecondPlayerInPlay(this)) {
				if (param_1 == GameObjectType::RobotPortal) {
					PlayLayer::get()->m_player2->m_robotSprite->updateFrame(IconData::robot);
				}
				if (param_1 == GameObjectType::SpiderPortal) {
					PlayLayer::get()->m_player2->m_spiderSprite->updateFrame(IconData::spider);
				}
			}
		}
		ExtraStuff::setPlayerColor(this);
	}

};