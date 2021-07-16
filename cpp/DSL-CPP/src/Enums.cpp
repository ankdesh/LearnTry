#include "Enums.hpp"

namespace enums{

const std::string to_str(NODE_TYPE op) {
    switch (op) {
    case NODE_TYPE::RootNode:
        return "RootNode"; 
        break;
    case NODE_TYPE::AddOp:
        return "AddOp"; 
        break;
    case NODE_TYPE::MultOp:
        return "MultOp";
        break;
    case NODE_TYPE::IndexOp:
        return "IndexOp";
        break;
    case NODE_TYPE::AssignOp:
        return "AssignOp";
        break;
    case NODE_TYPE::Var:
        return "Var";
        break;
    case NODE_TYPE::IndexVar:
        return "IndexVar";
        break;
    default:
        return "";
        break;
    }
}
};
