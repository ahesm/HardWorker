#pragma once

#include "Gasolinn.h"

class KeyboardEvent : public Root
{
private:
	bool flag = false;
	Timer *timer;
	int tick = 0;

	bool firstFlag = false;
	bool tickOn = false;
	bool moveOn = false;

public:
	static KeyboardEvent *Create() {
		auto ke = new KeyboardEvent;
		ke->flag = false;

		ke->timer = new Timer;

		return ke;
	}

	bool GetKeyPressed(unsigned char keycode) {
		if ((_keyState[keycode] & 0x80) && !flag) {
			flag = true;
			return true;
		}

		if (!(_keyState[keycode] & 0x80)) {
			flag = false;
		}

		return false;
	}

	bool GetKeyDelay(unsigned char keycode, unsigned int fDelay, unsigned int mDelay) {
		/// 키 처음 눌렀을때
		if ((_keyState[keycode] & 0x80) && !firstFlag) {
			tickOn = true;
			firstFlag = true;
			return true;
		}

		if (!(_keyState[keycode] & 0x80)) {
			tickOn = false;
			moveOn = false;
			firstFlag = false;
			tick = 0;
		}

		if (tickOn) {
			tick += 1;
			if (tick >= fDelay) {
				moveOn = true;
			}
		}

		bool check = false;
		if (moveOn) {
			timer->Start(mDelay, [&]{
				check = true;
			});
			if (check)
				return true;
			return false;
		}

		return false;
	}

};