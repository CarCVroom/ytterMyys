main: cpp/main.cpp cpp/orbit.cpp
	g++ cpp/main.cpp cpp/orbit.cpp -o build/main && ./build/main

wasm: cpp/orbit.cpp
	em++ cpp/orbit.cpp -o ts/orbit.js -O2 -sMODULARIZE=1 -sEXPORT_ES6=1 -sEXPORTED_FUNCTIONS=_orbit_start,_orbit_update,_get_x,_get_y,_get_altitude,_get_time_elapsed




