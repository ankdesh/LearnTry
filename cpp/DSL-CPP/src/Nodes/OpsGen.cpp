#include "OpsGen.hpp"

std::shared_ptr<Ops> OpsGen::createOp(enums::NODE_TYPE opType, std::string name = ""){
        if ( ! ( opType==enums::NODE_TYPE::AddOp || 
                 opType==enums::NODE_TYPE::MultOp ) ){
                     throw enums::to_str(opType) + "is not an Op Type";
        }

        std::string tempName = name;
        if (tempName == ""){
            tempName = "NoName";
        }

        return std::make_shared<Ops>(opType, name);
    }

std::shared_ptr<AddOp> OpsGen::createAddOp(std::string name = ""){
        std::string tempName = name;
        if (tempName == ""){
            tempName = "NoName";
        }

        return std::make_shared<AddOp>(name);
    }

std::shared_ptr<MultOp> OpsGen::createMultOp(std::string name = ""){
        std::string tempName = name;
        if (tempName == ""){
            tempName = "NoName";
        }

        return std::make_shared<MultOp>(name);
    }

