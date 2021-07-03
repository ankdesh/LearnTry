#ifndef TREE_H
#define TREE_H

#include <memory>
#include "Nodes/Node.hpp"

template <typename T> class Tree 
{
    using std::shared_ptr<T> NodePtr; 

public:
    NodePtr getRootPtr(){
        return root_;
    } 

    Tree (NodePtr& rootNode): root_(rootNode) {  }

protected:
    Tree() = default;
    Tree(Tree &&) = default;
    Tree(const Tree &) = default;
    Tree &operator=(Tree &&) = default;
    Tree &operator=(const Tree &) = default;
    ~Tree() = default;

protected:
    NodePtr root_; 

};

#endif // TREE_H
