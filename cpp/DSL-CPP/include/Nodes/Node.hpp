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
    virtual std::string name() final{
        return name_;
    }
    
    virtual std::string type_str() final{
        return enums::to_str(type_);
    };

    virtual enums::NODE_TYPE type () final {
        return type_;
    }
        
    virtual std::vector<NodePtr>::const_iterator children_begin() final{
        return children_.cbegin(); 
    }

    virtual std::vector<NodePtr>::const_iterator children_end() final {
        return children_.cend(); 
    }

    //TODO: Remove ? Should enforce type check of children
    virtual void add_child(NodePtr childPtr) { 
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
