#include "AST.hpp"
#include "NodeGen.hpp"
#include "Enums.hpp"

void AST::insertChild(AST::NodePtr pNode, AST::NodePtr cNode) {
    pNode->addChild(cNode);
}

AST::NodePtr AST::createParent(AST::NodePtr node1, AST::NodePtr node2, enums::NODE_TYPE pType) {
    return this->createParent({node1,node2}, pType);
}

AST::NodePtr AST::createParent(std::vector<AST::NodePtr> nodes, enums::NODE_TYPE pType) {
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
