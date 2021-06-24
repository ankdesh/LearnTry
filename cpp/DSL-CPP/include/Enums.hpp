#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <string>

namespace enums{

enum class NODE_TYPE{
    AddOp,
    MultOp,
    IndexOp
};

const std::string to_str(NODE_TYPE op){
    switch (op)        {
    case NODE_TYPE::AddOp:
        return "AddOp"; 
        break;
    case NODE_TYPE::MultOp:
        return "MultOp";
        break;
    case NODE_TYPE::IndexOp:
        return "IndexOp";
        break;
    default:
        break;
    }
}

}; // namespace enums

#endif // ENUMS_HPP
