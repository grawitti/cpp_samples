#include <iostream>

#include "Duck.hpp"

void Duck::set_fly_behavior(FlyBehavior* fb) {
	fly_behavior = fb;
}

void Duck::set_quack_behavior(QuackBehavior* qb) {
	quack_behavior = qb;
}

void Duck::performFly() {
	fly_behavior->fly();
}

void Duck::performQuack() {
	quack_behavior->quack();
}

void Duck::swim() {
	std::cout << "All ducks float!\n";
}
