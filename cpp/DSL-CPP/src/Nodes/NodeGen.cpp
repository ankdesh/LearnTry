#include <iostream>
#include "NodeGen.hpp"

std::shared_ptr<AddOp> NodeGen::createAddOp(std::string name = ""){
    std::string tempName = name;
    if (tempName == ""){
        tempName = "NoName";
    }

    return std::shared_ptr<AddOp>(new AddOp(name));
}

std::shared_ptr<MultOp> NodeGen::createMultOp(std::string name = ""){
    std::string tempName = name;
    if (tempName == ""){
        tempName = "NoName";
    }

    return std::shared_ptr<MultOp>(new MultOp(name));
}

std::shared_ptr<IndexOp> NodeGen::createIndexOp(std::string name = ""){
    std::string tempName = name;
    if (tempName == ""){
        tempName = "NoName";
    }

    return std::shared_ptr<IndexOp>(new IndexOp(name));
}

std::shared_ptr<Var> NodeGen::createVar(std::string name) {
    std::string tempName = name;
    if (tempName == ""){
        tempName = "NoName";
    }

    return std::shared_ptr<Var>(new Var (name));
}

std::shared_ptr<IndexVar> NodeGen::createIndexVar(std::string name) {
    std::string tempName = name;
    if (tempName == ""){
        tempName = "NoName";
    }

    return std::shared_ptr<IndexVar>(new IndexVar (name));
}
std::shared_ptr<Node> NodeGen::createNode(enums::NODE_TYPE nodeTy, std::string name) {
    std::string tempName = name;

    if (tempName == ""){
        tempName = "NoName";
    }

    // TODO: should it be replaced with typeid using RTTI ?
    switch (nodeTy){
        case enums::NODE_TYPE::AddOp:
            return NodeGen::createAddOp(name);

        case enums::NODE_TYPE::MultOp:
            return NodeGen::createMultOp(name);
        
        case enums::NODE_TYPE::IndexOp:
            return NodeGen::createIndexOp(name);

        case enums::NODE_TYPE::Var:
            return NodeGen::createVar(name);

        case enums::NODE_TYPE::IndexVar:
            return NodeGen::createIndexVar(name);

        default:
            std::cout << "Uknown type here: " << __FILE__ << " " << __LINE__; 
            break;
    }

    return std::shared_ptr<IndexVar>(new IndexVar (name));
}
