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