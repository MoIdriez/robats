/*
 * AutonomousFlight.cpp
 *
 *  Created on: 27 May 2016
 *      Author: midries
 */
#include <iostream>
#include <cmath>
#include "AutoFlight.h"

AutoFlight::AutoFlight(CCrazyflie *cf) : cf(cf), targetAlt(0) { }

void AutoFlight::hover(int targetAltitude) {
	targetAlt = targetAltitude;
	isLive = true;
	clock_t prev = clock();
	clock_t cur;
	while (isLive) {
		if (cf->cycle()) {
//			if (cf->thrust() < 20000) {
//				cf->setThrust(20000);
//			}
			cur = clock();
			if (this->diff(cur, prev)) {
				double curThrust = cf->thrust();
				double alt = cf->asl();
				double changeThrust = this->thrustchange(alt);
				cf->setThrust(curThrust + changeThrust);
				std::cout << "Thrust: " << curThrust + changeThrust << ", \tAlt: " << cf->asl() << std::endl;
				prev = cur;
			}

		}
	}
}

double AutoFlight::thrustchange(double curAlt){
	// do we actually care about small changes?
	if (std::abs(targetAlt - curAlt) > threshold){

		// firstly we obtain the error value
		double er = targetAlt - curAlt;

		// to obtain the proportional term we multiply kp with the error value
		double pt = kp * er;

		// accumulated error is used in the integration to calculate the average error
		itemp += er;

		// setting some limits to the error rate
		if (itemp > iMax)
		{itemp = iMax;}
		else if (itemp < iMin)
		{itemp = iMin;}

		// for the integral error we multiply ki with the accumulated integral value
		double it = ki * itemp;

		// calculating the derivative term
		double dt = kd * (dtemp - er);

		// setting the error rate to the historical error value
		dtemp = er;

		// this is just application specific
		return ttemp + pt + it + dt;
	}
	return 0;
}


void AutoFlight::stop() {
	isLive = false;
}

void AutoFlight::print(int level, std::string message) {
	if (level <= lvl) {

	}
}

void AutoFlight::setInformationLevel(int level) {
	lvl = level;
}

bool AutoFlight::diff(clock_t clock1,clock_t clock2)
{
    double diffticks=clock1-clock2;
    double diffms=(diffticks)/(CLOCKS_PER_SEC/1000);
    return diffms > mscount;
}

AutoFlight::~AutoFlight() {
	delete cf;
}