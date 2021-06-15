#include <string>
#include <iostream>
using namespace std;

struct Person
{
  Person (int id, string name): id(id), name(name){}
  int id;
  string name;
};

class PersonFactory
{
  int num_objs = -1;
public:
  Person create_person(const string& name)
  {
    num_objs++;
    return {num_objs,name};
  }
};

int main(){
    auto fc = PersonFactory();
    std::cout << fc.create_person("ankur").id;
    std::cout << fc.create_person("deshwal").id;
}