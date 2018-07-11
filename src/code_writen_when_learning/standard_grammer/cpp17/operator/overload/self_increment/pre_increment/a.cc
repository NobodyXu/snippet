#include <utility>
int main() {
    using type = decltype( ++std::declval<int&>() );
}
