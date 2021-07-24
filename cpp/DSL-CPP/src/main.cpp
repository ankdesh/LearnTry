#include "Expr.hpp"
#include "UnitTests/TestNodes.hpp"
#include "UnitTests/TestAST.hpp"

int main(int argc, char const *argv[])
{
    lang::IndexVar i("i"), j("j");
    lang::Var a("a"), b("b"), c("c");
    std::cout << ((a + b) * c[i][j]) <<std::endl;

    std::cout << "NodeCreateTest: " << testCreateNode() << std::endl;
    std::cout << "RootNodeTest: " << testRootNode() << std::endl;
    std::cout << "OpsTest1: " << testOps() << std::endl;
    std::cout << "VarTest: " << testVar() << std::endl;
    std::cout << "IndexVarTest: " << testIndexVar() << std::endl;

    std::cout << "AST Build BottomUP: " << testBuildASTBottomUp() <<std::endl;
    std::cout << "AST Build TopDown: " << testBuildASTTopDown() <<std::endl;
 
    return 0;
}

