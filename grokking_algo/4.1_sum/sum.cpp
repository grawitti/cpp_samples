#include <iostream>
#include <vector>

using namespace std;

int sum(const vector<int>& v)
{
	return (v.empty()) ? 0 : v.front() + sum({v.begin() + 1, v.end()});
}

int main()
{
	vector v = {1, 2, 3};
	cout << sum(v) << endl;

	return 0;
}
