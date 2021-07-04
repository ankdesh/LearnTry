#ifndef TREE_H
#define TREE_H

#include <memory>
#include "Nodes/Node.hpp"

template <typename T> class Tree 
{
    typedef std::shared_ptr<T> NodePtr; 

public:
    ~Tree() = default;
    Tree (NodePtr& rootNode): root_(rootNode) { }

    NodePtr getRootPtr(){
        return root_;
    } 

protected:
    Tree() = delete;
    Tree(Tree &&) = delete;
    Tree(const Tree &) = delete;
    Tree &operator=(Tree &&) = delete;
    Tree &operator=(const Tree &) = delete;


protected:
    NodePtr root_; 

};

#endif // TREE_H
