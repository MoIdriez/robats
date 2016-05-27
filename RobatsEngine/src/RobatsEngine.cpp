//============================================================================
// Name        : RobatsEngine.cpp
// Author      : Mohamed Idries
// Version     :
// Copyright   : Just use it for awesome stuff
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
// libcflie
#include "ControlEngine/GamePad.h";
#include "CrazyFlieEngine/CCrazyflie.h"
#include "CommunicationEngine/CrazyflieServer.h"

int main(int argc, char **argv) {
	CCrazyRadio *crRadio = new CCrazyRadio("radio://0/10/250K");

	if (crRadio->startRadio()) {
		int data[4];
		struct gp_values gpv;
		struct gp_event gpe;
		GamePad *gamepad = new GamePad();
		CCrazyflie *cflieCopter = new CCrazyflie(crRadio);

		//CrazyflieServer *sockety = new CrazyflieServer(4444, data);
		// Enable sending the setpoints. This can be used to temporarily
		// stop updating the internal controller setpoints and instead
		// sending dummy packets (to keep the connection alive).
		cflieCopter->setSendSetpoints(true);

		while (cflieCopter->cycle()) {
			//cflieCopter->setThrust(10001);
//			data[0] = cflieCopter->adc();
//			data[1] = cflieCopter->accX();
//			data[2] = cflieCopter->accY();
//			data[3] = cflieCopter->accZ();
//			cout << "Send Data: " << data[0] << "," << data[1] << "," << data[2]
//					<< "," << data[3] << endl;
			if (gamepad->readValues(&gpv)) {
				cout<< "Data: " << cflieCopter->adc() << "\nGamepad: Thrust " << gpv.thrust << ", Roll " << gpv.roll << ", Pitch " << gpv.pitch << ", Yaw " << gpv.yaw << endl;
				//cflieCopter->setThrust(gpv.thrust);
				cflieCopter->setRoll(gpv.roll);
				cflieCopter->setPitch(gpv.pitch);
				cflieCopter->setYaw(gpv.yaw);
			}

//			if (gamepad->readEvent(&gpe)) {
//				printf("Event: time %8u, value %8hd, type: %3u, axis/button: %u\n", gpe.time, gpe.value, gpe.type, gpe.number);
//			}
//    	std::cout << cflieCopter->adc() << ","
//    			 << cflieCopter->accX() << ","
//				 << cflieCopter->accY() << ","
//				 << cflieCopter->accZ() << std::endl;
		// Main loop. Currently empty.
		//cflieCopter->setThrust(16001);
		/* Examples to set thrust and RPY:
		 // Range: 10001 - (approx.) 60000

		 // All in degrees. R/P shouldn't be over 45 degree (it goes
		 // sidewards really fast!). R/P/Y are all from -180.0deg to 180.0deg.
		 cflieCopter->setRoll(20);
		 cflieCopter->setPitch(15);
		 cflieCopter->setYaw(140); */

		// Important note: When quitting the program, please don't just
		// SIGINT (i.e. CTRL-C) it. The CCrazyflie class instance
		// cflieCopter must be deleted in order to call the destructor
		// which stops logging on the device. If you fail to do this
		// when quitting your program, your copter will experience some
		// kind of buffer overflow (because of a lot of logging messages
		// summing up without being collected) and you will have to
		// restart it manually. This is not being done in this
		// particular example. You have been warned.
		// Other than that, this example covers pretty much everything
		// basic you will need for controlling the copter.
	}

	delete cflieCopter;
} else {
	std::cerr << "Could not connect to dongle. Did you plug it in?"
			<< std::endl;
}

delete crRadio;
return 0;
}
