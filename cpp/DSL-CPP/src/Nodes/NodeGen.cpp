#include <iostream>
#include "NodeGen.hpp"

std::shared_ptr<RootNode> NodeGen::createRootNode(std::string name) {
    std::string tempName = name;
    if (tempName == ""){
        tempName = "RootNode";
    }

    return std::shared_ptr<RootNode>(new RootNode(tempName));
}

std::shared_ptr<AddOp> NodeGen::createAddOp(std::string name = ""){
    std::string tempName = name;
    if (tempName == ""){
        tempName = "AddOp";
    }

    return std::shared_ptr<AddOp>(new AddOp(tempName));
}

std::shared_ptr<MultOp> NodeGen::createMultOp(std::string name = ""){
    std::string tempName = name;
    if (tempName == ""){
        tempName = "MultOp";
    }

    return std::shared_ptr<MultOp>(new MultOp(tempName));
}

std::shared_ptr<IndexOp> NodeGen::createIndexOp(std::string name = ""){
    std::string tempName = name;
    if (tempName == ""){
        tempName = "IndexOp";
    }

    return std::shared_ptr<IndexOp>(new IndexOp(tempName));
}

std::shared_ptr<AssignOp> NodeGen::createAssignOp(std::string name="") {
    std::string tempName = name;
    if (tempName == ""){
        tempName = "AssignOp";
    }

    return std::shared_ptr<AssignOp>(new AssignOp(tempName));    
}

std::shared_ptr<Var> NodeGen::createVar(std::string name) {
    return std::shared_ptr<Var>(new Var(name));
}

std::shared_ptr<IndexVar> NodeGen::createIndexVar(std::string name) {
    return std::shared_ptr<IndexVar>(new IndexVar (name));
}

std::shared_ptr<Node> NodeGen::createNode(enums::NODE_TYPE nodeTy, std::string name = "") {
    std::string tempName = name;

    if (tempName == ""){
        tempName = enums::to_str(nodeTy);
    }

    // TODO: should it be replaced with typeid using RTTI ?
    switch (nodeTy){
        case enums::NODE_TYPE::RootNode:
            return NodeGen::createRootNode(tempName);

        case enums::NODE_TYPE::AddOp:
            return NodeGen::createAddOp(tempName);

        case enums::NODE_TYPE::MultOp:
            return NodeGen::createMultOp(tempName);
        
        case enums::NODE_TYPE::IndexOp:
            return NodeGen::createIndexOp(tempName);

        case enums::NODE_TYPE::AssignOp:
            return NodeGen::createAssignOp(tempName);

        case enums::NODE_TYPE::Var:
            return NodeGen::createVar(tempName);

        case enums::NODE_TYPE::IndexVar:
            return NodeGen::createIndexVar(tempName);

        default:
            std::cout << "Uknown type here: " << __FILE__ << " " << __LINE__; 
            break;
    }

    return nullptr;
}

void NodeGen::insertChild(NodeGen::NodePtr pNode, NodeGen::NodePtr cNode) {
    pNode->addChild(cNode);
}

NodeGen::NodePtr NodeGen::createParent(NodeGen::NodePtr node1, NodeGen::NodePtr node2, enums::NODE_TYPE pType) {
    return NodeGen::createParent({node1,node2}, pType);
}

NodeGen::NodePtr NodeGen::createParent(std::vector<NodeGen::NodePtr> nodes, enums::NODE_TYPE pType) {
    std::string pName = enums::to_str(pType) + "_";

    for (auto& cNode:nodes){
        pName += "_" + cNode->name();
    }
    
    auto pNode = NodeGen::createNode(pType, pName);
    
    for (auto& cNode:nodes){
        pNode->addChild(cNode);
    }
    
    return pNode;
}

