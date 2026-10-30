#ifndef ORBIT_HPP 
#define ORBIT_HPP

struct State {
	double x, y;
	double vx, vy; // velocity 
	double altitude;
	double elapsed_time;
};

extern "C" {

void falling_test(double spacecraft_mass, double altitude);

void orbit_start(double altitude);
void orbit_update(double altitude);
double pythagoras(double x, double y);

double get_x();
double get_y();
double get_altitude();
double get_time_elapsed();

}

constexpr double RADIUS = 6371000; // meters
constexpr double EARTHMU = 3.98600435507e14; // m^3/s^2

constexpr double GRAVITY = 9.8; // m/s^2
constexpr double PI = 3.1415926; // pi, you know what pi is 

constexpr double DT = 1;

constexpr int SUCCESS = 0;
constexpr int FAIL = 1;

#endif
