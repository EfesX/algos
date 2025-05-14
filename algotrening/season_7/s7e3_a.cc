#include <iostream>
#include <cstdint>

int main() 
{
    uint64_t x; std::cin >> x;
    std::cout << __builtin_popcountll (x) << std::endl;
    return 0;
}
