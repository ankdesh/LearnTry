#ifndef ASSIGNOP_HPP
#define ASSIGNOP_HPP

#include "Ops.hpp" 

class AssignOp: public Ops{
    friend class NodeGen;
public:
        ~AssignOp() = default;
    
private:
    AssignOp() = delete;
    AssignOp(AssignOp &&) = delete;
    AssignOp(const AssignOp &) = delete;
    AssignOp &operator=(AssignOp &&) = delete;
    AssignOp &operator=(const AssignOp &) = delete;

    AssignOp(std::string name):
        Ops(enums::NODE_TYPE::AssignOp, name){}
};

#endif // ASSIGNOP_HPP
