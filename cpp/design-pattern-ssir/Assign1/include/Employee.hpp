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
    static int id_counter_; // Auto increment id

public:
    ~Employee() = default;

    std::string getName(){
        return name_;
    }

    std::string getPhone(){
        return phone_;
    }

    int getId(){
        return id_;
    }

    static std::shared_ptr<Employee> make(std::string name, std::string phone){
        id_counter_++;
        return std::shared_ptr<Employee>(new Employee(name, phone, id_counter_));
    }

};




#endif // !__EMPLOYEE_H__