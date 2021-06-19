#include <iostream>
#include <string>


class Op
{
public:
    Op (std::string name): name_(name) {}
    Op() = default;
    Op(Op &&) = default;
    Op(const Op &) = default;
    Op &operator=(Op &&) = default;
    Op &operator=(const Op &) = default;
    ~Op() = default;

    Op& operator + (const Op& rhs){
        // std::cout << "<" + rhs.name() + "> [add] attached to {" << this->name() + "}"; 
        return *(new Op("(" + this->name() + "+" + rhs.name() +")" ));
    }

    Op& operator * (const Op& rhs){
        // std::cout << "<" + rhs.name() + "> [mult] attached to {" << this->name() + "}"; 
        return *(new Op("(" + this->name() + "*" + rhs.name() + ")" ));
    }

    std::string name() const { return name_; }
    void setName(const std::string &name) { name_ = name; }

    friend std::ostream &operator<<(std::ostream &os, const Op &rhs) {
        os << rhs.name_;
        return os;
    }

private:
    std::string name_;
    
};

