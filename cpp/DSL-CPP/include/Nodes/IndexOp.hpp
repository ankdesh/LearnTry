#ifndef INDEXOP_HPP
#define INDEXOP_HPP

#include "Ops.hpp" 

class IndexOp: public Ops{
    friend class NodeGen;
public:
        ~IndexOp() = default;
    
private:
    IndexOp() = delete;
    IndexOp(IndexOp &&) = delete;
    IndexOp(const IndexOp &) = delete;
    IndexOp &operator=(IndexOp &&) = delete;
    IndexOp &operator=(const IndexOp &) = delete;

    IndexOp(std::string name):
        Ops(enums::NODE_TYPE::IndexOp, name){}
};

#endif // INDEXOP_HPP
