/*
 * AutonomousFlight.h
 *
 *  Created on: 27 May 2016
 *      Author: midries
 */
#include "../CrazyFlieEngine/CCrazyflie.h"
class AutoFlight {
public:
	AutoFlight(CCrazyflie *cf);
	~AutoFlight();
	void stop();
	void hover(int targetAltitude);
	void setInformationLevel(int level);
	int start(bool showInformation = true);
private:
	bool isLive = false;
	double threshold = 0.001; // threshold on which we care about alt change
	double mscount = 10; // 10ms
	float targetAlt;
	int lvl = 0; /* 0 = nothing, 1 = warnings, 2 = everything */
	CCrazyflie *cf;

	void print(int level, std::string message);
	bool diff(clock_t clock1,clock_t clock2);
	double thrustchange(double curAlt);

	/* PID Controller */
	const double kp = 100, ki = 100, kd = 100; // gain constants
	double itemp = 0; // accumulated error
	double iMax = 1000, iMin = -1000; // error limits
	double dtemp = 0; // historic error
	double ttemp = 0; // historic thrust
	//double sp, fv, er; // set point, feedback value, error value

	//double tp, ti, td;
};