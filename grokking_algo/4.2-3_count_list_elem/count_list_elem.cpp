#include <iostream>

using namespace std;

template<class T>
struct ListNode {
	T value;
	ListNode* next = nullptr;
};

template<class T>
struct List {
	// TODO Реализовать коструктор со списком инициализации
	// TODO Реализовать с умными указателями

	List() = default;
	List(ListNode<T>* begin, ListNode<T>* end) : _first{begin}, _last{end} {}

	void push_back(T v)
	{
		if (!_first) {
			_first        = new ListNode<T>;
			_first->value = v;
			_last         = _first;
		}
		else {
			_last->next        = new ListNode<T>;
			_last->next->value = v;
			_last              = _last->next;
		}
	}

	ListNode<T>* first() { return _first; }
	ListNode<T>* last() { return _last; }

	void print()
	{
		cout << '[';
		for (auto cur = _first; cur; cur = cur->next) {
			cout << cur->value << ' ';
		}
		cout << "]\n";
	}

	void print() const
	{
		cout << '[';
		for (auto cur = _first; cur; cur = cur->next) {
			cout << cur->value << ' ';
		}
		cout << "]\n";
	}

	ListNode<T>* _first = nullptr;
	ListNode<T>* _last  = nullptr;
};

// 4.2 Подсчёт колличества элементов списка с помощью рекурсивной функции
template<typename T>
uint count_elements(const List<T>& l)
{
	uint count = 1;
	if (l._first == l._last) {
		return count;
	}
	else {
		return count += count_elements(List<T>{l._first->next, l._last});
	}
}

// 4.3 Нахождение наибольшего числа в сиске с помощью рекурсии
int find_max(const List<int>& l)
{
	if (l._first == l._last) {
		return l._first->value;
	}
	else {
		int max = find_max(List<int>{l._first->next, l._last});
		return (max > l._first->value) ? max : l._first->value;
	}
}


int main()
{
	List<int> l;
	l.push_back(-90);
	l.push_back(30);
	l.push_back(3);
	l.push_back(3);
	l.push_back(4);

	cout << "l ";
	l.print();

	cout << "l size = " << count_elements(l) << endl;

	cout << "l max = " << find_max(l) << endl;

	return 0;
}
