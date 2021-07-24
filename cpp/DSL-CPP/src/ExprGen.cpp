#include "ExprGen.hpp"

using namespace lang;

ExprGen::ExprPtr ExprGen::createExpr(std::string name) {
    auto expr = new Expr(name);
    ExprGen::listExprs_.push_back(expr);
    return expr;
}
