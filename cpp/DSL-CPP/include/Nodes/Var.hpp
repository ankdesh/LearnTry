#ifndef VAR_HPP
#define VAR_HPP

#include "Enums.hpp"
#include "Node.hpp" 

class Var: public Node{
    friend class NodeGen;
    
public:
    ~Var() = default;

    static bool isVarType(enums::NODE_TYPE nodeTy);

protected:
    Var() = delete;
    Var(Var &&) = delete;
    Var(const Var &) = delete;
    Var &operator=(Var &&) = delete;
    Var &operator=(const Var &) = delete;

    Var(std::string name):
        Node(enums::NODE_TYPE::Var, name){}
};

#endif // VAR_HPP
