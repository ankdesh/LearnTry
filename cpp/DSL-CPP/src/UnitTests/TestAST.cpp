#include "TestAST.hpp"
#include "Nodes/NodeGen.hpp"

bool testBuildASTBottomUp() {
    // Create AST for A = B * C 
    auto ast = AST::createAST("testAST");

    std::shared_ptr<Var> A = NodeGen::createVar("A");
    std::shared_ptr<Var> B = NodeGen::createVar("B");
    std::shared_ptr<Var> C = NodeGen::createVar("C");

    auto mult_op = NodeGen::createParent(B,C,enums::NODE_TYPE::MultOp);
    auto assign_op = NodeGen::createParent(A, mult_op, enums::NODE_TYPE::AssignOp); 

    ast->get_root()->addChild(assign_op);

    return true;
}

