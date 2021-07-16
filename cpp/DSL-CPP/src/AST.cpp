#include "AST.hpp"

std::shared_ptr<AST> AST::createAST(std::string name = "") {
    auto tempName = name;
    if (tempName == ""){
        tempName = "AST";
    }

    std::shared_ptr<AST> ast(new AST(tempName));

    return ast;
}
