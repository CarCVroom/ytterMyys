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
		.elapsed_time = 0.0	
	};

	double ax; 
	double ay; 
	double V;
	bool in_orbit = true;
	while (in_orbit) {
		r = pythagoras(spacecraft_status.x, spacecraft_status.y);

		ax = - (EARTHMU * spacecraft_status.x)/ (r * r * r);
		ay = - (EARTHMU * spacecraft_status.y)/ (r * r * r);

		spacecraft_status.vx += ax * DT;
		spacecraft_status.vy += ay * DT;

		spacecraft_status.x += spacecraft_status.vx * DT;
		spacecraft_status.y += spacecraft_status.vy * DT;

		V = sqrt((spacecraft_status.vx * spacecraft_status.vx) + (spacecraft_status.vy * spacecraft_status.vy));
	
		r = pythagoras(spacecraft_status.x, spacecraft_status.y);

		spacecraft_status.altitude = r - RADIUS;

   		std::cout << std::fixed
             	<< "Altitude: " << spacecraft_status.altitude
              	<< " m | Speed: " << V
		<< " m/s | Time: " << spacecraft_status.elapsed_time
              	<< " s\n";
		
		spacecraft_status.elapsed_time += DT;
	}

}

double pythagoras(double x, double y) {
	return sqrt((x * x) + (y * y));
}

void falling_test(double spacecraft_mass, double altitude) { // This does not work
	if (altitude + RADIUS < RADIUS) {
		std::cout << "alititude must be greater then Radius + altitude. IE it can't be a negative number or 0." << std::endl;
		return;
	}

	State spacecraft_status = {
		.x = 0,
		.y = altitude + RADIUS,
		.vx = 0,
		.vy = 0,
		.altitude = altitude
	};

	// Make it fall to when it reaches the ground. 
	while (spacecraft_status.y > RADIUS) {
		double G = EARTHMU / std::pow((RADIUS + spacecraft_status.altitude), 2.0);

		spacecraft_status.vy = 0 - G * DT; // change - to + to get upward
		spacecraft_status.y = spacecraft_status.y + spacecraft_status.vy;	
		spacecraft_status.altitude = spacecraft_status.altitude + spacecraft_status.vy;	


		std::cout << std::fixed << "Spacecraft still in freefall at " << spacecraft_status.altitude << " meters. Traveling at " << spacecraft_status.vy << "m/s at T+" << DT << std::endl;
		std::cout << std::fixed << "Gravity is: " << G << std::endl;
		
		// if (DT == 10)2m {
		// 	return;	
		// }
		
	}	
	std::cout << "The spacecraft has hit the ground. Altitude and speed: " << spacecraft_status.altitude << " meters and " << spacecraft_status.vy << "m/s" << " After " << DT << " seconds"<< std::endl;
}
