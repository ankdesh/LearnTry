#include <iostream>
#include "Directory.hpp"
#include<memory>

int main(int argc, const char** argv) {

    auto empdir = EmpDirectory::make("InMemory");

    while(1){
        int choice;
        std::cout << std::endl << "Please enter choice - (1) Add an employee (2) Search an employee: " ;
        std::cin >> choice;
        std::string name, phone;
        switch (choice){
            case 1: 
                std::cout << std::endl << "Please enter Name:" ;
                std::cin >> name;
                std::cout << std::endl << "Please enter Phone:" ;
                std::cin >> phone;
                empdir->add(Employee::make(name, phone));
                break;
            case 2: 
                std::cout << std::endl << "Please enter Name to search:" ;
                std::cin >> name;
                std::cout << std::endl << "Employee Id:" << empdir->search(name)->getId();
                std::cout << std::endl << "Employee name:" << name;
                std::cout << std::endl << "Employee Phone:" << empdir->search(name)->getPhone();
                break;
            default:
                std::cout << std::endl << "Wrong choice try again";
        }
            
    }

    return 0;
}