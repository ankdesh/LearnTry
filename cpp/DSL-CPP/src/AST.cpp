#include "AST.hpp"

void AST::insertChild(AST::NodePtr pNode, AST::NodePtr cNode) {
    pNode->add_child(cNode);
}

AST::NodePtr AST::createParent(AST::NodePtr node1, AST::NodePtr node2, enums::NODE_TYPE pType) {

}

AST::NodePtr AST::createParent(std::vector<AST::NodePtr> nodes, enums::NODE_TYPE pType) {
    
}
