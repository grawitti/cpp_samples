#include <iostream>

class Animal {
	public:
		virtual std::string say() = 0;
};

class Dog : public Animal {
	std::string say() { return "ГАВ-ГАВ!"; }
};

class Cat : public Animal {
	std::string say() { return "МЯУ!"; }
};

int main() {
	Animal* dog = new Dog();
	std::cout << "Dog say: " << dog->say() + "\n";

	Animal* cat = new Cat();
	std::cout << "Cat say: " << cat->say() + "\n";

	return 0;
}
