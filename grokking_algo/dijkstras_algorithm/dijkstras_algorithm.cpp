/**
  Грокаем алгоримы, Глава 7, стр. 170 - 181

  Нахождение кратчайшего пути обмена с наименьшим весом в направленном
  взвешенном ацикличном графе с помощью алгоритма Дейкстры.
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

using Costs = unordered_map<const char*, uint>;
using Graph = unordered_map<const char*, Costs>;
using Parrents = unordered_map<const char*, const char*>;

/**
 * Хэш-таблица описывающая граф
 * 
 *         6->(A)->1
 *        /    ^    \
 * (Start)     3    (Fin)
 *        \    |    /
 *         2->(B)->5
*/

Graph graph = {
	{"start", {{"a", 6}, {"b", 2}}},
	{"a", {{"fin", 1}}},
	{"b", {{"a", 3}, {"fin", 5}}},
	{"fin", {}}
};

// Хэш-таблица для стоимости перехoда
Costs costs{
	{"a", 6},
	{"b", 2},
	{"fin", UINT_MAX}
};

// Хэш-табица для записи родителей узлов
Parrents parents{
	{"a", "start"},
	{"b", "start"},
	{"fin", ""}
};
// Мапа для записи обработанных узлов
unordered_map<const char*, bool> processed;

// Функция нахождения узла с наименьшей стоимостью
const char* find_lowest_cost_node(Costs& costs)
{
	uint lowest_cost = UINT_MAX;
	const char* lowest_cost_node = "";

	for (auto& node : costs) {
		uint cost = costs[node.first];
		if (cost < lowest_cost &&
			(processed.find(node.first) == processed.end())) {
			lowest_cost = cost;
			lowest_cost_node = node.first;
		}
	}
	return lowest_cost_node;
}

/**
 * Алгоритм Дейкстры
 */
void dijkstras_algorithm()
{
	// Шаг 1: найти узел с наиментшим весом
	const char* node = find_lowest_cost_node(costs);

	// Шаг 3: повторять для всех узлов
	while (string(node) != "") {
		uint cost = costs[node];
		Costs neighbors = graph[node];
		// Шаг 2: проверить существует ли более дешевый путь к соседям узла
		for (auto& n : neighbors) {
			uint new_cost = cost + neighbors[n.first];
			// Если существует обновить их веса
			if (costs[n.first] > new_cost) {
				costs[n.first] = new_cost;
				parents[n.first] = node; // Шаг 4: вычисление итогового пути
			}
		}
		processed[node] = true;
		node = find_lowest_cost_node(costs);
	}	
}

int main(int argc, char const *argv[])
{
	dijkstras_algorithm();

	cout << "Итоговый путь: ";
	for (auto& p : parents) {
		cout << "{" << p.first << "<-" << p.second << "} ";
	}
	cout << endl;

	cout << "Стоимость пути до Fin: " << costs["fin"] << endl;	

	return 0;
}