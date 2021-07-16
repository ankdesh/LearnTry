#ifndef TREE_H
#define TREE_H

#include <memory>
#include "Nodes/Node.hpp"
#include "Nodes/NodeGen.hpp"

template <typename T> class Tree 
{
    typedef std::shared_ptr<T> NodePtr; 

public:
    ~Tree() = default;

    NodePtr get_root(){
        return root_;
    } 

protected:
    Tree(Tree &&) = delete;
    Tree(const Tree &) = delete;
    Tree &operator=(Tree &&) = delete;
    Tree &operator=(const Tree &) = delete;

protected:
    Tree (NodePtr rootNode): root_(rootNode) { }
    Tree (std::string name){
        root_ = NodeGen::createNode(enums::NODE_TYPE::RootNode, name);
    }

    NodePtr root_; 

};

#endif // TREE_H
