#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <memory>
#include <string>
#include <map>
#include "Employee.hpp"


class RepositoryIf
{
protected:
    RepositoryIf() = default;
    
public:
    ~RepositoryIf() = default;

    virtual void add(std::shared_ptr<Employee> e) = 0; 
    virtual std::shared_ptr<Employee> read(std::string name) = 0; 
};

class InMemoryRepository : public RepositoryIf
{
 
public:
    ~InMemoryRepository() = default;

    void add(std::shared_ptr<Employee> e) override {
        repo_[e->getName()] = e; 
    } 
    
    std::shared_ptr<Employee> read(std::string name) override {
        return repo_[name];
    }     

public:
    InMemoryRepository() = default; // No one should be able to create this object except friends. How to handle Composition ??

private:
    std::map<std::string, std::shared_ptr<Employee>> repo_; 
};


#endif // !__REPOSITORY_H__
