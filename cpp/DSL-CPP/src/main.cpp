#include "Expr.hpp"
#include "UnitTests/TestNodes.hpp"

int main(int argc, char const *argv[])
{
    Expr a("a"), b("b"), c("c"), i("i"), j("j");
    std::cout << ((a + b) * c[i][j]) <<std::endl;

    std::cout << "NodeCreateTest: " << testCreateNode() << std::endl;
    std::cout << "OpsTest1: " << testOps() << std::endl;
    std::cout << "VarTest: " << testVar() << std::endl;
    std::cout << "IndexVarTest: " << testIndexVar() << std::endl;

    return 0;
}

