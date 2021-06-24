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

    virtual void add_child(Node& child) final {
         children_.push_back(child);
    }



private:
    Node() = default;
    Node(Node &&) = default;
    Node(const Node &) = default;
    Node &operator=(Node &&) = default;
    Node &operator=(const Node &) = default;
    ~Node() = default;

protected:
    std::string name_;
    enums::NODE_TYPE type_;
    std::vector<Node> children_;
};

#endif // NODE_HPP
