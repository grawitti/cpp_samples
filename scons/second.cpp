#include "class_b.h"

using namespace std;

int main()
{

#ifdef DEBUG
	cout << "DEBUG second\n";
#endif

	B b2("Second porgram ");

	b2.print();

	return 0;
}
