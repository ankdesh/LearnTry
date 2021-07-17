#ifndef EXPRGEN_HPP
#define EXPRGEN_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Expr.hpp"

class ExprGen
{
public:
    using ExprPtr = Expr*;

    static ExprPtr createExpr(std::string name);

    ~ExprGen() = default;

private:
    ExprGen() = delete;
    ExprGen(ExprGen &&) = delete;
    ExprGen(const ExprGen &) = delete;
    ExprGen &operator=(ExprGen &&) = delete;
    ExprGen &operator=(const ExprGen &) = delete;

    inline static std::vector<ExprPtr> listExprs_;
    
};




#endif // EXPRGEN_HPP
