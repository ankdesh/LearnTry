#ifndef INDEXVAR_HPP
#define INDEXVAR_HPP

#include "Enums.hpp"
#include "Node.hpp" 

class IndexVar: public Node{
    friend class NodeGen;
    
public:
    ~IndexVar() = default;

    static bool isIndexVarType(enums::NODE_TYPE nodeTy);

protected:
    IndexVar() = delete;
    IndexVar(IndexVar &&) = delete;
    IndexVar(const IndexVar &) = delete;
    IndexVar &operator=(IndexVar &&) = delete;
    IndexVar &operator=(const IndexVar &) = delete;

    IndexVar(std::string name):
        Node(enums::NODE_TYPE::IndexVar, name){}
};

#endif // INDEXVAR_HPP
