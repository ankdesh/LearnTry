#ifndef EXPR_HPP
#define EXPR_HPP

#include <iostream>
#include <string>

namespace lang{

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

class Var : public Expr
{
public:
    Var(std::string name): Expr(name){}
    ~Var() = default;

private:
    Var(Var &&) = delete;
    Var(const Var &) = delete;
    Var &operator=(Var &&) = delete;
    Var &operator=(const Var &) = delete;
};

class IndexVar : public Expr
{
public:
    IndexVar(std::string name): Expr(name){}
    ~IndexVar() = default;
    
private:
    IndexVar(IndexVar &&) = delete;
    IndexVar(const IndexVar &) = delete;
    IndexVar &operator=(IndexVar &&) = delete;
    IndexVar &operator=(const IndexVar &) = delete;
};



}

#endif // EXPR_HPP
