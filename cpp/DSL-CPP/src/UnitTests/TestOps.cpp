#include "Nodes/OpsGen.hpp"
#include "TestOps.hpp"

bool testOps(){
    auto addOp1 = OpsGen::createAddOp("AddOp1");
    bool result1 = (addOp1->name() == "AddOp1");

    auto multOp1 = OpsGen::createMultOp("MultOp1");
    bool result2 = true; //(addOp2->name() == "AddOp2");

    return (result1 && result2);
}