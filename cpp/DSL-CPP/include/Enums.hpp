#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <string>

namespace enums{

enum class NODE_TYPE
{
    RootNode,
    AddOp,
    MultOp,
    IndexOp,
    AssignOp,
    Var,
    IndexVar
};

const std::string to_str(NODE_TYPE op);

}; // namespace enums

#endif // ENUMS_HPP
