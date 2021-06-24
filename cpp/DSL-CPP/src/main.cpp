#include "Expr.hpp"

int main(int argc, char const *argv[])
{
    Expr a("a"), b("b"), c("c"), i("i"), j("j");
    std::cout << ((a + b) * c[i][j]) <<std::endl;
    return 0;
}
