#include <iostream>

using namespace std;

template <class T1, class T2>
void func([[maybe_unused]] T1&& t1, [[maybe_unused]] T2&& t2)
{
    cout << "r-value: " << t1 << ", " << t2 << endl;
}

// template <class T1, class T2>
// void func([[maybe_unused]] T1& t1, [[maybe_unused]] T2& t2)
// {
    // cout << "l-value: " << t1 << ", " << t2 << endl;
// }

template <typename T1, typename T2>
void wrapper(T1&& e1, T2&& e2) {
    func(forward<T1>(e1), forward<T2>(e2));
}

int main()
{
    wrapper("str", 123);

    string s = "str2";
    int i = 321;
    wrapper(s, i);

    wrapper(s, 1);

    wrapper("str3", i);

    const string s2 = "str4";
    const int i2 = 2;
    wrapper(s2, i2);


    return 0;
}
