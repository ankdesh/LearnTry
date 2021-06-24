#ifndef EXPR_HPP
#define EXPR_HPP

#include <iostream>
#include <string>


class Expr
{
public:
    Expr (std::string name): name_(name) {}
    Expr() = default;
    Expr(Expr &&) = default;
    Expr(const Expr &) = default;
    Expr &operator=(Expr &&) = default;
    Expr &operator=(const Expr &) = default;
    ~Expr() = default;

    Expr& operator + (const Expr& rhs){
        // std::cout << "<" + rhs.name() + "> [add] attached to {" << this->name() + "}"; 
        return *(new Expr("(" + this->name() + "+" + rhs.name() +")" ));
    }

    Expr& operator * (const Expr& rhs){
        // std::cout << "<" + rhs.name() + "> [mult] attached to {" << this->name() + "}"; 
        return *(new Expr("(" + this->name() + "*" + rhs.name() + ")" ));
    }

    Expr& operator [] (const Expr& rhs){
        // std::cout << "<" + rhs.name() + "> [mult] attached to {" << this->name() + "}"; 
        return *(new Expr(this->name() + "[" + rhs.name() + "]" ));
    }

    std::string name() const { return name_; }
    void setName(const std::string &name) { name_ = name; }

    friend std::ostream &operator<<(std::ostream &os, const Expr &rhs) {
        os << rhs.name_;
        return os;
    }

private:
    std::string name_;
    
};


#endif // EXPR_HPP
