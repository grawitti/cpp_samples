#pragma once

#include "FlyBehavior.hpp"
#include "QuackBehavior.hpp"

class Duck {
public:
	Duck() {}

	virtual void display() = 0;

	void set_fly_behavior(FlyBehavior*);
	void set_quack_behavior(QuackBehavior*);
	void performFly();
	void performQuack();
	void swim();

protected:
	FlyBehavior* fly_behavior;
	QuackBehavior* quack_behavior;
};
