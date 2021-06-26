#ifndef OPSGEN_HPP
#define OPSGEN_HPP

#include <memory>
#include "Ops.hpp"
#include "AddOp.hpp"
#include "MultOp.hpp"

class OpsGen{
public: 

    static std::shared_ptr<Ops> createOp(enums::NODE_TYPE opType, std::string name);
    static std::shared_ptr<AddOp> createAddOp(std::string name);
    static std::shared_ptr<MultOp> createMultOp(std::string name);

private:
    OpsGen() = delete;
    OpsGen(OpsGen &&) = delete;
    OpsGen(const OpsGen &) = delete;
    OpsGen &operator=(OpsGen &&) = delete;
    OpsGen &operator=(const OpsGen &) = delete;
    ~OpsGen() = default;
   

};

#endif // OPSGEN_HPP
