#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__
#include <string>
#include <memory>

class Employee : std::enable_shared_from_this<Employee>
{
private:
    Employee(std::string name, std::string phone, int id): name_(name),
                                                           phone_(phone),
                                                           id_(id){}

    Employee() = delete;

    std::string name_;
    std::string phone_;
    int id_;
    static int id_counter_; 

public:
    ~Employee() = default;

    static std::shared_ptr<Employee> make(std::string name, std::string phone){
        id_counter_++;
        return std::shared_ptr<Employee>(new Employee(name, phone, id_counter_));
    }

};




#endif // !__EMPLOYEE_H__