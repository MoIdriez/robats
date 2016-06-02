/*
 * GamePad.h
 *
 *  Created on: 25 May 2016
 *      Author: midries
 */

#ifndef SRC_CONTROLENGINE_GAMEPAD_H_
#define SRC_CONTROLENGINE_GAMEPAD_H_

#define GAMEPAD_DEVNAME "/dev/input/js0"

#define GP_EVENT_BUTTON         0x01    /* button pressed/released */
#define GP_EVENT_AXIS           0x02    /* gamepad moved */
#define GP_EVENT_INIT           0x80    /* initial state of device */

struct gp_event {
	unsigned int time;      /* event timestamp in milliseconds */
	short value;   /* value */
	unsigned char type;     /* event type */
	unsigned char number;   /* axis/button number */
};

struct gp_values {
	int button[11];
	int stick1_x;
	int stick1_y;
	int stick2_x;
	int stick2_y;
};

class GamePad {
public:
	virtual ~GamePad();
	int readGamePadEvent(struct gp_event *gpe);
	int readGamePadValue(struct gp_values *gpv);
	GamePad();
private:
	int gamepad_fd = -1;
};

#endif /* SRC_CONTROLENGINE_GAMEPAD_H_ */


//struct wwvi_gp_event {
//	int button[11];
//	int stick1_x;
//	int stick1_y;
//	int stick2_x;
//	int stick2_y;
//};
//
//extern int open_gamepad(char *gamepad_device);
//extern int read_gamepad_event(struct gp_event *jse);
//extern void set_gamepad_y_axis(int axis);
//extern void set_gamepad_x_axis(int axis);
//extern void close_gamepad();
//extern int get_gamepad_status(struct wwvi_gp_event *wjse);