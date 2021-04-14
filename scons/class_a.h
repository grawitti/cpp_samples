#include <iostream>
#include <string>

using namespace std;

class A {
	public:
		A(string s) : _s(s){}
		void print();
		string str(){ return _s; }
	private:
		string _s;
};
