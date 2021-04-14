#include "MallardDuck.hpp"

int main() {
	Duck* mallard = new MallardDuck();
	mallard->display();
	mallard->performFly();
	mallard->performQuack();

	mallard->set_fly_behavior(new FlyNoWay());
	mallard->performFly();


	return 0;
}
