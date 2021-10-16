#include <iostream>

using namespace std;

class MemoryBlock
{
};

void g(const MemoryBlock&)
{
    cout << "In f(const MemoryBlock&). This version cannot modify the parameter\n";
}

void g(MemoryBlock&&)
{
    cout << "In f(const MemoryBlock&&). This version can modify the parameter\n";
}

MemoryBlock&& f_move(MemoryBlock&& mb)
{
    g(mb); // mb - l-value
    return move(mb);
}

MemoryBlock&& f_cast(MemoryBlock&& mb)
{
    g(mb); // mb - l-value
    return static_cast<MemoryBlock&&>(mb);
}

int main()
{
    MemoryBlock mb;
    g(mb); // l-value parameter
    g(MemoryBlock()); // r-value parameter

    g(f_move(MemoryBlock()));
    g(f_cast(MemoryBlock()));

    return 0;
}
