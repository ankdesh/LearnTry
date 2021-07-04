#ifndef ADDOP_HPP
#define ADDOP_HPP

#include "Ops.hpp" 

class AddOp: public Ops{
    friend class NodeGen;
public:
        ~AddOp() = default;
    
private:
    AddOp() = delete;
    AddOp(AddOp &&) = delete;
    AddOp(const AddOp &) = delete;
    AddOp &operator=(AddOp &&) = delete;
    AddOp &operator=(const AddOp &) = delete;

    AddOp(std::string name):
        Ops(enums::NODE_TYPE::AddOp, name){}
};

#endif // ADDOP_HPP
