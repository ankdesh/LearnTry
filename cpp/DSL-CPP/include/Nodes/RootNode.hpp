#ifndef ROOTNODE_HPP
#define ROOTNODE_HPP

#include "Ops.hpp" 

class RootNode: public Ops{
    friend class NodeGen;
public:
    ~RootNode() = default;
    
private:
    RootNode() = delete;
    RootNode(RootNode &&) = delete;
    RootNode(const RootNode &) = delete;
    RootNode &operator=(RootNode &&) = delete;
    RootNode &operator=(const RootNode &) = delete;

    RootNode(std::string name):
        Ops(enums::NODE_TYPE::RootNode, name){}
};

#endif // ROOTNODE_HPP
