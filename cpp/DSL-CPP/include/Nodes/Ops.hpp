#ifndef OPS_HPP
#define OPS_HPP

#include "Enums.hpp"
#include "Node.hpp" 

class Ops: public Node{
    friend class NodeGen;
    
public:
    ~Ops() = default;

    static bool isOpType(enums::NODE_TYPE nodeTy);

protected:
    Ops() = delete;
    Ops(Ops &&) = delete;
    Ops(const Ops &) = delete;
    Ops &operator=(Ops &&) = delete;
    Ops &operator=(const Ops &) = delete;

    Ops(enums::NODE_TYPE type, std::string name):
        Node(type, name){}
};

#endif // OPS_HPP
