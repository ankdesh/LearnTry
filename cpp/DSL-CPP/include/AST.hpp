#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <vector>
#include "Nodes/Node.hpp"
#include "Tree.hpp"

class AST : public Tree<Node> {

    typedef std::shared_ptr<Node> NodePtr;

public:
    ~AST() = default;

    void insertChild(NodePtr pNode, NodePtr cNode);
    NodePtr createParent(NodePtr node1, NodePtr node2, enums::NODE_TYPE pType);
    NodePtr createParent(std::vector<NodePtr> nodes, enums::NODE_TYPE pType);

private:

    AST() = delete;
    AST(AST &&) = delete;
    AST(const AST &) = delete;
    AST &operator=(AST &&) = delete;
    AST &operator=(const AST &) = delete;


};

#endif // AST_HPP
