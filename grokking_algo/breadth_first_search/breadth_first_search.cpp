#include <iostream>
#include <deque>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

using Graph = unordered_map<const char*, vector<const char*>>;

bool person_is_seller(const char* name)
{
    return (string(name) == "Thom") ? true : false;
}

void search(const char* name, Graph& graph)
{
    deque<const char*> search_queue;
    for (const auto& s : graph[name]) {
	search_queue.push_back(s);
    }

    map<const char*, bool> searched; 

    while (!search_queue.empty()) {
	const char* person;
	person = search_queue.front();
	search_queue.pop_front();

	if (searched.find(person) == searched.end()) {
	    if (person_is_seller(person)) {
		cout << person << " is mango seller" << endl;
		return;
	    }
	    else {
		for (const auto& s: graph[person]) {
		    search_queue.push_back(s);
		}
		searched.emplace(person, true);
	    }
	}
    }

    cout << "Mango sellers not found\n";
}

int main()
{
    Graph graph = {
	{"You" , {"Alice", "Bob", "Claire"}},
	{"Bob" , {"Anuj", "Peggy"}},
	{"Alice" , {"Peggy"}},
	{"Claire" , {"Thom", "Jonny"}},
	{"Anuj" , {}},
	{"Peggy" , {}},
	{"Thom" , {}},
	{"Jonny" , {}},
    };

    search("You", graph);

    return 0;
}
