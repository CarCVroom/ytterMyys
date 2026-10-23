#include "orbit.hpp"
#include <iostream>
#include <cmath>

void orbit_test(double altitude) {
	if (altitude + RADIUS < RADIUS) {
		std::cout << "alititude must be greater then Radius + altitude. IE it can't be a negative number or 0." << std::endl;
		return;
	}

	double r = RADIUS + altitude;
	State spacecraft_status = {
		.x = r,
		.y = 0,
		.vx = 0,
		.vy = std::sqrt(EARTHMU / r),
		.timeDT = 0.0, // Seconds
	};

	bool in_orbit = true;
	while (in_orbit) {
		r = pythagoras(spacecraft_status.x, spacecraft_status.y);
		spacecraft_status.x = r;

		std::cout <<std::fixed << "y is: " << spacecraft_status.y << ". x is: "<< spacecraft_status.x << std::endl;

		spacecraft_status.timeDT = spacecraft_status.timeDT + 0.10;
	}

}

double pythagoras(double x, double y) {
	return sqrt((x * x) + (y * y));
}

void falling_test(double spacecraft_mass, double altitude) {
	if (altitude + RADIUS < RADIUS) {
		std::cout << "alititude must be greater then Radius + altitude. IE it can't be a negative number or 0." << std::endl;
		return;
	}

	State spacecraft_status = {
		.x = 0,
		.y = altitude + RADIUS,
		.vx = 0,
		.vy = 0,
		.timeDT= 0,
		.altitude = altitude
	};

	// Make it fall to when it reaches the ground. 
	while (spacecraft_status.y > RADIUS) {
		double G = EARTHMU / std::pow((RADIUS + spacecraft_status.altitude), 2.0);

		spacecraft_status.vy = 0 - G * spacecraft_status.timeDT; // change - to + to get upward
		spacecraft_status.y = spacecraft_status.y + spacecraft_status.vy;	
		spacecraft_status.altitude = spacecraft_status.altitude + spacecraft_status.vy;	


		std::cout << std::fixed << "Spacecraft still in freefall at " << spacecraft_status.altitude << " meters. Traveling at " << spacecraft_status.vy << "m/s at T+" << spacecraft_status.timeDT << std::endl;
		std::cout << std::fixed << "Gravity is: " << G << std::endl;
		spacecraft_status.timeDT++;
		// if (spacecraft_status.timeDT == 10)2m {
		// 	return;	
		// }
		
	}	
	std::cout << "The spacecraft has hit the ground. Altitude and speed: " << spacecraft_status.altitude << " meters and " << spacecraft_status.vy << "m/s" << " After " << spacecraft_status.timeDT << " seconds"<< std::endl;
}
