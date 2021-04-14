#include<iostream>

int foo()
{
	return 7;
}

int main(int argc, char *argv[])
{
	std::cout << foo << std::endl;
	std::cout << reinterpret_cast<void*>(foo) << std::endl;
	std::cout << (void*)(foo) << std::endl;
	int (*ptrFoo)() = foo;
	std::cout << reinterpret_cast<void*>(ptrFoo) << std::endl;

	return 0;
}
