/*
 * GamePad.cpp
 *
 *  Created on: 25 May 2016
 *      Author: midries
 */

#include "GamePad.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

GamePad::GamePad() {
	gamepad_fd = open(GAMEPAD_DEVNAME, O_RDONLY | O_NONBLOCK); /* read write for force feedback? */
	if (gamepad_fd < 0)
		throw "Couldn't open gamepad";
}

int GamePad::readGamePadEvent(struct gp_event *gpe) {
	int bytes;
	bytes = read(gamepad_fd, gpe, sizeof(*gpe));

	if (bytes == -1)
		return 0;

	if (bytes == sizeof(gpe))
		return 1;

	printf("Unexpected bytes from gamepad:%d\n", bytes);
	return -1;
}

int GamePad::readGamePadValue(struct gp_values *gpv) {
	int rc;
	struct gp_event gpe;

	if ((rc = readGamePadEvent(&gpe)) == 1) {

		gpe.type &= ~GP_EVENT_INIT; /* ignore synthetic events */
		if (gpe.type == GP_EVENT_AXIS) {
			switch (gpe.number) {
			case 0:
				gpv->stick1_x = gpe.value;
				break;
			case 1:
				gpv->stick1_y = gpe.value;
				break;
			case 2:
				gpv->stick2_x = gpe.value;
				break;
			case 5:
				gpv->stick2_y = gpe.value;
				break;
			default:
				break;
			}
		} else if (gpe.type == GP_EVENT_BUTTON) {
			if (gpe.number < 10) {
				switch (gpe.value) {
				case 0:
				case 1:
					gpv->button[gpe.number] = gpe.value;
					break;
				default:
					break;
				}
			}
		}
	} else {
		printf("Something is wrong. Value given is %d\n", rc);
	}

}

GamePad::~GamePad() {
	close(gamepad_fd);
}

//int get_gamepad_status(struct wwvi_gp_event *wjse)
//{
//        int rc;
//        struct gp_event jse;
//        if (gamepad_fd < 0)
//                return -1;
//
//        // memset(wjse, 0, sizeof(*wjse));
//        while ((rc = read_gamepad_event(&jse) == 1)) {
//                jse.type &= ~GP_EVENT_INIT; /* ignore synthetic events */
//                if (jse.type == GP_EVENT_AXIS) {
//                        switch (jse.number) {
//                        case 0:
//                        	wjse->stick1_x = jse.value;
//                            break;
//                        case 1:
//                        	wjse->stick1_y = jse.value;
//                            break;
//                        case 2:
//                        	wjse->stick2_x = jse.value;
//                            break;
//                        case 3:
//                        	wjse->stick2_y = jse.value;
//                            break;
//                        default:
//                                break;
//                        }
//                } else if (jse.type == GP_EVENT_BUTTON) {
//                        if (jse.number < 10) {
//                                switch (jse.value) {
//                                case 0:
//                                case 1: wjse->button[jse.number] = jse.value;
//                                        break;
//                                default:
//                                        break;
//                                }
//                        }
//                }
//        }
//        // printf("%d\n", wjse->stick1_y);
//        return 0;
//}

