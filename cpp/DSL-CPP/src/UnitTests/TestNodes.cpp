#include "Nodes/NodeGen.hpp"
#include "TestNodes.hpp"
#include <memory>

bool testCreateNode(){
    auto addOp = NodeGen::createNode(enums::NODE_TYPE::AddOp,"AddOp");
    bool result = (std::static_pointer_cast<AddOp>(addOp)->name() == "AddOp");

    return result;
}

bool testOps(){
    auto addOp1 = NodeGen::createAddOp("AddOp1");
    bool result1 = (addOp1->name() == "AddOp1");

    auto multOp1 = NodeGen::createMultOp("MultOp1");
    bool result2 = (multOp1->name() == "MultOp1");

    auto indexOp1 = NodeGen::createIndexOp("IndexOp1");
    bool result3 = (indexOp1->name() == "IndexOp1");

    return (result1 && result2 && result3);
}

bool testVar(){
    auto addOp1 = NodeGen::createVar("Var");
    bool result1 = (addOp1->name() == "Var");

    return result1;
}

bool testIndexVar() {
    auto addOp1 = NodeGen::createIndexVar("IndexVar");
    bool result1 = (addOp1->name() == "IndexVar");

    return result1;
}

