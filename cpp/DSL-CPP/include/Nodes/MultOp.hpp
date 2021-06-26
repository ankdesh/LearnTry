#ifndef MULTOP_HPP
#define MULTOP_HPP

#include "Ops.hpp" 

class MultOp: Ops{
    friend class OpsGen;
public:
    ~MultOp() = default;
    
private:
    MultOp() = delete;
    MultOp(MultOp &&) = delete;
    MultOp(const MultOp &) = delete;
    MultOp &operator=(MultOp &&) = delete;
    MultOp &operator=(const MultOp &) = delete;

    MultOp(std::string name):
        Ops(enums::NODE_TYPE::MultOp, name){}
};

#endif // MULTOP_HPP
