/*
 * ControlTest.cpp
 *
 *  Created on: 25 May 2016
 *      Author: midries
 */
#include "ControlEngine/GamePad.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int done = 0, rc = 0;
	GamePad * gamepad = new GamePad();
	struct gp_event gpe;
	struct gp_values gpv;


	while (!done) {
		rc = gamepad->readGamePadEvent(&gpe);
		//rc = gamepad->readGamePadValue(&gpv);
		//usleep(1000);
		if (rc == 1){// && rv == 1){
			printf("Event: time %8u, value %8hd, type: %3u, axis/button: %u\n",
					gpe.time, gpe.value, gpe.type, gpe.number);
//			printf("Event: stick1x %u, stick1y %u, stick2x %u, stick2y %u\n", gpv.stick1_x, gpv.stick1_y, gpv.stick2_x, gpv.stick2_y);

		}
	}

}