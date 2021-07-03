#include "Expr.hpp"
#include "UnitTests/TestOps.hpp"

int main(int argc, char const *argv[])
{
    Expr a("a"), b("b"), c("c"), i("i"), j("j");
    std::cout << ((a + b) * c[i][j]) <<std::endl;

    std::cout << "OpsTest1" << testOps() << std::endl;

    return 0;
}

