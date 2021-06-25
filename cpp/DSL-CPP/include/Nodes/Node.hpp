#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>
#include "Enums.hpp"

class Node
{
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
        
    virtual std::vector<Node>::const_iterator children_begin() final{
        return children_.cbegin(); 
    }

    virtual std::vector<Node>::const_iterator children_end() final {
        return children_.cend(); 
    }

    //TODO: Remove ? Should enforce type check of children
    virtual void add_child(Node& child) { 
         children_.push_back(child);
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
    std::string name_;
    enums::NODE_TYPE type_;
    std::vector<Node> children_;
};

#endif // NODE_HPP
