#include <iostream>

#include "QuackBehavior.hpp"

void Quack::quack() {
	std::cout << "Quack!\n";
}

void MuteQuack::quack() {}

void Squeak::quack() {
	std::cout << "Squeak!\n";
}
