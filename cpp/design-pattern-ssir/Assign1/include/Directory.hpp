#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#include <memory>
#include "Employee.hpp"
#include "Repository.hpp"

class DirectoryIf
{
protected:
    DirectoryIf() = default;
    
public:
    ~DirectoryIf() = default;

    virtual void add(std::shared_ptr<Employee> e) = 0; 
    virtual std::shared_ptr<Employee> search(std::string name) = 0; 
};

class EmpDirectory : DirectoryIf
{
 
public:
    ~EmpDirectory() = default;

    void add(std::shared_ptr<Employee> e) override {
        repo_->add(e);
    } 
    std::shared_ptr<Employee> search(std::string name) override {
        return repo_->read(name);
    }     

    static std::shared_ptr<EmpDirectory> make(std::string repo_type);

private:
    EmpDirectory() = default;

    std::shared_ptr<RepositoryIf> repo_; 
};


#endif // !__DIRECTORY_H__
