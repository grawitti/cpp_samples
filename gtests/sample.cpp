#include <iostream>

class Foo
{
public:
	Foo() : i(0) {
		std::cout << "Conctructed\n"; 
	}
	~Foo() {
		std::cout << "Destructed\n"; 
	}

	void set_i(int input_v) {
		if (input_v < 0) {
			throw std::runtime_error("Negative value");
		}
		else {
			i = input_v;
		}
	}

	int i;
	static int ii;

};

bool is_positive(int i)
{
	return (i >= 0) ? true : false;
}

int is_positive_i(int i)
{
	return (i >= 0) ? 1 : 0;
}

const char* is_positive_char(int i)
{
	return (i >= 0) ? "true" : "false";
}
