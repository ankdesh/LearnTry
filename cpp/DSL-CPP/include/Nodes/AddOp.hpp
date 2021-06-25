#ifndef ADDOP_HPP
#define ADDOP_HPP

#include "Ops.hpp" 

class AddOp: Ops{
    friend class OpsGen;
public:
    
private:
    AddOp() = delete;
    AddOp(AddOp &&) = delete;
    AddOp(const AddOp &) = delete;
    AddOp &operator=(AddOp &&) = delete;
    AddOp &operator=(const AddOp &) = delete;
    ~AddOp() = default;

    AddOp(std::string name):
        Ops(enums::NODE_TYPE::AddOp, name){}
};

#endif // ADDOP_HPP
