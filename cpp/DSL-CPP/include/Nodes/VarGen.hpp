#ifndef VARGEN_HPP
#define VARGEN_HPP

#include <memory>
#include "Var.hpp"

class VarGen{
public: 

    static std::shared_ptr<Var> createVar(std::string name);
    
private:
    VarGen() = delete;
    VarGen(VarGen &&) = delete;
    VarGen(const VarGen &) = delete;
    VarGen &operator=(VarGen &&) = delete;
    VarGen &operator=(const VarGen &) = delete;
    ~VarGen() = default;
};

#endif // VARGEN_HPP
