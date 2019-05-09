#include <iostream>

struct S
{
    int a;
    int b;
};

void  f(S s)
{
    std::cout << s.a << s.b;
}
