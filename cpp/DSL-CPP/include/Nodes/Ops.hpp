#ifndef OPS_HPP
#define OPS_HPP

#include <memory>
#include "Enums.hpp"
#include "Node.hpp" 

class Ops: public Node
{
    friend class OpsGen;
public:

protected:
    Ops() = delete;
    Ops(Ops &&) = delete;
    Ops(const Ops &) = delete;
    Ops &operator=(Ops &&) = delete;
    Ops &operator=(const Ops &) = delete;
    ~Ops() = default;

    Ops(enums::NODE_TYPE type, std::string name):
        Node(type, name){}
};

class OpsGen
{
public: 

     static std::shared_ptr<Ops> createOp(enums::NODE_TYPE opType, std::string name = ""){
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

private:
    OpsGen() = delete;
    OpsGen(OpsGen &&) = delete;
    OpsGen(const OpsGen &) = delete;
    OpsGen &operator=(OpsGen &&) = delete;
    OpsGen &operator=(const OpsGen &) = delete;
    ~OpsGen() = default;
   

};


#endif // OPS_HPP
