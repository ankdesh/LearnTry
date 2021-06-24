#ifndef ADDOP_HPP
#define ADDOP_HPP

#include "Node.hpp" 

class AddOp: Node
{
public:
    
private:
    AddOp() = default;
    AddOp(AddOp &&) = default;
    AddOp(const AddOp &) = default;
    AddOp &operator=(AddOp &&) = default;
    AddOp &operator=(const AddOp &) = default;
    ~AddOp() = default;
};

#endif // ADDOP_HPP
