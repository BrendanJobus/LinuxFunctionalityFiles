#include <iostream>
using namespace std;

#define a_macro(args...) sum(args)

int sum()
{
    return 0;
}

template<typename T, typename... Args>
auto sum(T a, Args... args)
{
    return a + sum(args...);
}

int main()
{
    cout << a_macro(5, 7, 2, 2.2) + a_macro(3.14, 4.89) << endl;
}