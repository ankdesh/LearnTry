#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>
#include <memory>
#include "Enums.hpp"

class Node
{
    using NodePtr = std::shared_ptr<Node>; 
public:
    std::string name() {
        return name_;
    }
    
    std::string typeStr() {
        return enums::to_str(type_);
    };

    enums::NODE_TYPE type ()  {
        return type_;
    }
        
    std::vector<NodePtr>::const_iterator children_begin() {
        return children_.cbegin(); 
    }

    std::vector<NodePtr>::const_iterator children_end()  {
        return children_.cend(); 
    }

    void addChild(NodePtr childPtr) { 
        children_.push_back(childPtr);
    }


protected:
    Node() = delete;
    Node(Node &&) = delete;
    Node(const Node &) = delete;
    Node &operator=(Node &&) = delete;
    Node &operator=(const Node &) = delete;
    ~Node() = default;

    Node(enums::NODE_TYPE type, std::string name):
        type_(type),
        name_(name){} 

protected:
    enums::NODE_TYPE type_;
    std::string name_;
    std::vector<std::shared_ptr<Node>> children_;
};

#endif // NODE_HPP
