#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int>& list, int item)
{
    int low = 0;
    int high = list.size() - 1;

    int i = 0;
    while (low <= high) {
		cout << ++i << endl;
		int mid = (low + high) / 2;
		int guess = list.at(mid);

		if (guess == item) {
			return mid;
		}

		if (guess > item) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
    }
    
    return -1;
}

int main()
{
    vector<int> my_list = {1, 3, 5, 7, 9};

    cout << binary_search(my_list, 3) << endl; // => 1
    cout << endl;
    cout << binary_search(my_list, -1) << endl; // => -1

    return 0;
}
