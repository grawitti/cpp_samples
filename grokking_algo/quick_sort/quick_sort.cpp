#include <iostream>
#include <vector>

#include "../../random/random.cpp"
using namespace std;

vector<int> quick_sort(const vector<int>& v)
{
	if (v.size() < 2) {
		return v;
	}
	else {
		int pivot = v[0];
		vector<int> less;
		vector<int> greater;

		for (size_t i = 1; i < v.size(); i++) {
			if (v[i] <= pivot) {
				less.push_back(v[i]);
			}
			else {
				greater.push_back(v[i]);
			}
		}

		less    = quick_sort(less);
		greater = quick_sort(greater);

		vector<int> res{less.begin(), less.end()};
		res.push_back(pivot);
		res.insert(res.end(), greater.begin(), greater.end());

		return res;
	}
}

template<class T>
void print_vector(const vector<T>& v)
{
	cout << "[";
	for (auto& e: v) {
		cout << e << " ";
	}
	cout << "]\n";
}

int main()
{
	vector<int> v;
	int max = 100;
	for (int i = 0; i < max; i++) {
	    v.push_back(get_random(max));
	}

	print_vector(v);

	print_vector(quick_sort(v));

	return 0;
}
