#include <iostream>
#include "MallardDuck.hpp"

MallardDuck::MallardDuck() {
	fly_behavior   = new FlyWithWings();
	quack_behavior = new Quack();
}

void MallardDuck::display() {
	// mallard duck image
	std::cout << "Mallard duck:\n\n"
			  << "\t      =-\n"
	          << "\t\\    /\n"
	          << "\t ####\n"
	          << "\t ###\n\n";
}
