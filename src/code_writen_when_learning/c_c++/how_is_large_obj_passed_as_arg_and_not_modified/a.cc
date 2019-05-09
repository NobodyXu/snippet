#include <iostream>

struct S
{
    int a[45];
    int b[45];
};

void  f(S s)
{
    std::cout << s.a[0];
}
