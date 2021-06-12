#include <string>
#include <iostream>
using namespace std;

class CodeBuilder
{
  string classStr_;
public:
  CodeBuilder(const string& class_name)
  {
    classStr_ = "class " + class_name + "\n{\n";
  }

  CodeBuilder& add_field(const string& name, const string& type)
  {
    classStr_ += "  " + type + " " + name + ";\n"  ;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const CodeBuilder &rhs) {
      os << rhs.classStr_ << "};";
      return os;
  }
};

int main (){
    auto cb = CodeBuilder{"Person"}.add_field("name","string").add_field("age","int");
    std::cout << cb;

}