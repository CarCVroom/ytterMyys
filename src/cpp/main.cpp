#include <iostream>
#include "orbit.hpp"

int main() {
	std::cout << "Hello, World" << std::endl;

	int result = test();
	if (result != 0) {
		std::cout << "Something went wrong" << std::endl;
	}

	return 0;
}
