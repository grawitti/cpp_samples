#include "class_a.h"

using namespace std;

class B : public A {
	public:
		B(string s) : A(s){}
		void print();
};
