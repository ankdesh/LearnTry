#ifndef NODEGEN_HPP
#define NODEGEN_HPP

#include <memory>
#include "Ops.hpp"
#include "AddOp.hpp"
#include "MultOp.hpp"
#include "IndexOp.hpp"
#include "Var.hpp"
#include "IndexVar.hpp"

class NodeGen{
public: 

    static std::shared_ptr<Node> createNode(enums::NODE_TYPE node, std::string name); 

    static std::shared_ptr<AddOp> createAddOp(std::string name);
    static std::shared_ptr<MultOp> createMultOp(std::string name);
    static std::shared_ptr<Var> createVar(std::string name);
    static std::shared_ptr<IndexVar> createIndexVar(std::string name);
    static std::shared_ptr<IndexOp> createIndexOp(std::string name);

private:
    NodeGen() = delete;
    NodeGen(NodeGen &&) = delete;
    NodeGen(const NodeGen &) = delete;
    NodeGen &operator=(NodeGen &&) = delete;
    NodeGen &operator=(const NodeGen &) = delete;
    ~NodeGen() = default;
};


#endif // NODEGEN_HPP
