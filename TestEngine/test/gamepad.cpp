#include "GamePad.h"
#include "CCrazyflie.h"
#include "CrazyEngine.h"

bool gamepad() {
	CrazyEngine * ce = new CrazyEngine(gamepadFunc);
	ce->run();
	return true;
}

void gamepadFunc(CCrazyflie* cflieCopter) {
	struct gp_values gpv;
	GamePad *gamepad = new GamePad();

	gamepad->readValues(&gpv);
	cflieCopter->setRoll(gpv.roll);
	cflieCopter->setPitch(gpv.pitch);
	cflieCopter->setYaw(gpv.yaw); // disable this to makes flying easier
}
