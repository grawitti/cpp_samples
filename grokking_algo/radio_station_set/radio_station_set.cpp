/**
 Грокаем алгоритмы, стр. 187

 Задача о покрытии множества

 Условие:
 Из множества радио-станций, каждая их которых покрывает несколько штатов,
 США необходимо выбрать минимальное количество радио-станций покрывающих
 нужные штаты.
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <map>

using namespace std;
using States_set = set<const char*>;

/**
	Печать списка штатов
	@param st Список штатов
*/
void print_set(const States_set& st)
{
	cout << "{ ";
	for (auto& s : st) {
		cout << s << " ";
	}
	cout << "}" << endl;
}

/**
	Печать мапы с радио-станциями
	@param staions Мапа с радио-станциями
*/
void print_stations(const map<const char*, States_set> stations)
{
	cout << "stations {\n";
	for (auto& s : stations) {
		cout << "\t{" << s.first << ", {";
		for (auto& st : s.second) {
			cout << st << " ";
		}
		cout << "}}\n";
	}
	cout << "}\n";
}

/**
	Приближенный алгоритм поиска радиостанций
	@param[in] state_needed Список штатов которые необходимо покрыть
	@param[in] stations Мапа с описанием радио-станций
	@return States_set Список станций для покрытия необходимых штатов
*/
States_set greedly_algorithm(States_set states_needed,
                             const map<const char*, States_set>& stations)
{
	States_set result_st;

	while (!states_needed.empty()) {
		const char* best_station = "";	// Лучшая станция, которая покрывает больше штатов
		States_set states_covered;      // Штыты покрываемые лучшей станцией

		for (auto& st : stations) {
			States_set covered = {}; // Пересечение states_needed и штатами покрываемыми станцией
			set_intersection(states_needed.begin(), states_needed.end(),
			                 st.second.begin(), st.second.end(),
			                 inserter(covered, covered.begin()));

			if (covered.size() > states_covered.size()) { // Если количество станций больше
				best_station = st.first; // обновляем лучшую станцию
				states_covered = covered; // обновляем список штатов для лучшей станции
			}
		}

		// Удаляем штаты которые покрыла лучшая станция
		States_set diff_st; 
		set_difference(states_needed.begin(), states_needed.end(),
		               states_covered.begin(), states_covered.end(),
		               inserter(diff_st, diff_st.begin()));
		states_needed = diff_st;

		result_st.emplace(best_station);
	}

	return result_st;
}

int main(int argc, char const *argv[])
{

	// Список необходимых штатов
	States_set states_neded{"mt", "wa", "or", "id", "nv", "ut", "ca", "az"};
	cout << "Необходимые штаты: ";
	print_set(states_neded);

	/* Мапа для описания радио-станций и покрываемые ими штаты.
	   Если использовать unordered_map, то результат отличается от книжного так как изменяется
	   поледовательность элементов в контейнере, потому что в std:unordered_map другая хэш-
	   функция, не как в python dict.
	*/
	map<const char*, States_set> stations {
		{"1", {"id", "nv", "ut"}},
		{"2", {"wa", "id", "mt"}},
		{"3", {"or", "nv", "ca"}},
		{"4", {"nv", "ut"}},
		{"5", {"ca", "az"}}
	};

	print_stations(stations);

	// Итоговый набор радио-станций
	States_set final_stations = greedly_algorithm(states_neded, stations);

	cout << "Список станций покрывающих необходимые штаты: {";
	print_set(final_stations);

	return 0;
}