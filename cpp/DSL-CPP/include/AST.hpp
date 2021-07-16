#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <vector>
#include "Nodes/Node.hpp"
#include "Tree.hpp"

class AST : public Tree<Node> {
public:
    ~AST() = default;

    static std::shared_ptr<AST> createAST(std::string name);

private:
    AST(std::string name): Tree<Node>(name){}
    AST(AST &&) = delete;
    AST(const AST &) = delete;
    AST &operator=(AST &&) = delete;
    AST &operator=(const AST &) = delete;
};

#endif // AST_HPP
