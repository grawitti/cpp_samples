#include <iostream>

#include "FlyBehavior.hpp"

void FlyWithWings::fly() {
	std::cout << "I'm flying!\n";
}

void FlyNoWay::fly() {
	std::cout << "I can't fly\n";
}

void FlyRocketPowered::fly() {
	std::cout << "I fly with a rocket!\n";
}
