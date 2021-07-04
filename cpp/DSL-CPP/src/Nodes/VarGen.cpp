#include "VarGen.hpp"

std::shared_ptr<Var> VarGen::createVar(std::string name) {
    std::string tempName = name;
    if (tempName == ""){
        tempName = "NoName";
    }

    return std::shared_ptr<Var>(new Var (name));
}
