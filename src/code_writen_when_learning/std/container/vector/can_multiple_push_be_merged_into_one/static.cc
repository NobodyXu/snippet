#include <vector>
#define TEN_X(exp) do { exp; exp; exp; exp; exp; exp; exp; exp; exp; exp; } while(0)
int main() {
    std::vector<int> v;

    int i{111};
    TEN_X(v.push_back(i++));
}
