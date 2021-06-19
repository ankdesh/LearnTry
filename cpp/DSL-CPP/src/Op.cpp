#include "Op.hpp"

int main(int argc, char const *argv[])
{
    Op a("a"), b("b"), c("c");
    std::cout << (a + b * c);
    return 0;
}
