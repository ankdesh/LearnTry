#ifndef EXPR_HPP
#define EXPR_HPP

#include <iostream>
#include <string>

class Expr
{
    friend class ExprGen;
public:
    
    Expr& operator + (const Expr& rhs);


    Expr& operator * (const Expr& rhs);

    Expr& operator [] (const Expr& rhs);

    std::string name() const { return name_; }

    friend std::ostream &operator<<(std::ostream &os, const Expr &rhs) {
        os << rhs.name_;
        return os;
    }

    ~Expr() = default;

public:
    Expr (std::string name): name_(name) {}
    Expr() = delete;
    Expr(Expr &&) = delete;
    Expr(const Expr &) = delete;
    Expr &operator=(Expr &&) = delete;
    Expr &operator=(const Expr &) = delete;
    
    std::string name_;
};


#endif // EXPR_HPP
