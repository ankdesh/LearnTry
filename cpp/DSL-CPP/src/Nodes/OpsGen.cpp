#include "OpsGen.hpp"

std::shared_ptr<AddOp> OpsGen::createAddOp(std::string name = ""){
    std::string tempName = name;
    if (tempName == ""){
        tempName = "NoName";
    }

    return std::shared_ptr<AddOp>(new AddOp(name));
}

std::shared_ptr<MultOp> OpsGen::createMultOp(std::string name = ""){
    std::string tempName = name;
    if (tempName == ""){
        tempName = "NoName";
    }

    return std::shared_ptr<MultOp>(new MultOp(name));
}

