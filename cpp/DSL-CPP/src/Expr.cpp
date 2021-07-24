#include "Expr.hpp"
#include "ExprGen.hpp"

using namespace lang;

Expr& Expr::operator + (const Expr& rhs) {
    
    // std::cout << "<" + rhs.name() + "> [add] attached to {" << this->name() + "}"; 
    return *(ExprGen::createExpr("(" + this->name() + "+" + rhs.name() +")" ));
}


Expr& Expr::operator * (const Expr& rhs){
    // std::cout << "<" + rhs.name() + "> [mult] attached to {" << this->name() + "}"; 
    return *(ExprGen::createExpr("(" + this->name() + "*" + rhs.name() +")" ));
}

Expr& Expr::operator [] (const Expr& rhs){
    // std::cout << "<" + rhs.name() + "> [mult] attached to {" << this->name() + "}"; 
    return *(ExprGen::createExpr(this->name() + "[" + rhs.name() + "]" ));
}
