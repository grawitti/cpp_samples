#include <iostream>
#include <vector>

#include "random/random.cpp"

/**
 * Сортировка выбором
 *
 * Создание отсортированного массива путём выбора минимального\максимального
 * элемента из оригинального массива.
 *
 * Создаём новый массив и добавляем в него минимальный элемент
 * из не отсортированного массива и одновременно удаляем этот
 * элемент из не отсортированного массива пока в нем не останется
 * элементов.
 */

using namespace std;

void print_vec(const vector<int>& vec)
{
    for (uint i = 0; i < vec.size(); i++) {
	cout << ((i == 0) ? "[" : "")
	     << vec[i]
	     << ((i != vec.size()-1) ? ", " : "]\n");
    }
}

uint find_smallest(const vector<int>& vec)
{
    int smallest = vec[0];
    uint smallest_index = 0;

    for (uint i = 0; i < vec.size(); i++) {
        if (vec[i] < smallest) {
            smallest = vec[i];
            smallest_index = i;
        }
    }

    return smallest_index;
}

vector<int> selection_sort(vector<int>& vec)
{
    vector<int> new_vec;

    while (vec.size() >= 1) {
        uint smallest_index = find_smallest(vec);
        new_vec.push_back(vec[smallest_index]);
        vec.erase(vec.begin() + smallest_index);
    }
    
    return new_vec;
}

int main()
{
    int max = 1000000;
    vector<int> vec;
    for (int i = 0; i < max; i++) {
        vec.push_back(get_random(max));
    }
    cout << "original vector: ";
    print_vec(vec);

    vector<int> sorted_vec = selection_sort(vec);
    cout << "sorted vector: ";
    print_vec(sorted_vec);

    return 0;
}
