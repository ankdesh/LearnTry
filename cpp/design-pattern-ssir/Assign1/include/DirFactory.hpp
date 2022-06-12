#ifndef __FACTORY__
#define __FACTORY__
#include <memory>


class Factory {
public:
    static std::shared_ptr<Factory> make(std::string key);
    ~Factory() = default;

protected:
    Factory() = delete;
    Factory(Factory &&) = delete;
    Factory(const Factory &) = delete;
    Factory &operator=(Factory &&) = delete;
    Factory &operator=(const Factory &) = delete;

};

class EmployeeFactory : Factory
{
private:
    EmployeeFactory() = default;
    EmployeeFactory(EmployeeFactory &&) = default;
    EmployeeFactory(const EmployeeFactory &) = default;
    EmployeeFactory &operator=(EmployeeFactory &&) = default;
    EmployeeFactory &operator=(const EmployeeFactory &) = default;

public:
    ~EmployeeFactory() = default;



    
};

#endif // __FACTORY__
