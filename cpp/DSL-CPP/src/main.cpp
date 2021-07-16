#include "Expr.hpp"
#include "UnitTests/TestNodes.hpp"
#include "UnitTests/TestAST.hpp"

int main(int argc, char const *argv[])
{
    Expr a("a"), b("b"), c("c"), i("i"), j("j");
    std::cout << ((a + b) * c[i][j]) <<std::endl;

    std::cout << "NodeCreateTest: " << testCreateNode() << std::endl;
    std::cout << "RootNodeTest: " << testRootNode() << std::endl;
    std::cout << "OpsTest1: " << testOps() << std::endl;
    std::cout << "VarTest: " << testVar() << std::endl;
    std::cout << "IndexVarTest: " << testIndexVar() << std::endl;

    std::cout << "AST Build BottomUP: " << testBuildASTBottomUp() <<std::endl;
 
    return 0;
}

