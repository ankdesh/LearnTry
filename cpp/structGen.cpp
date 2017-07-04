// This code can be used for generating c code for struct definitions and creating objects

#include <iostream>
#include <string>
#include <map>

using namespace std;

class StructElemDef{
public:
    StructElemDef(std::string elemType, std::string elemVal){
        type = elemType;
        val = elemVal;
    };

    std::string type;
    std::string val;
};

class StructDef{

    // Struct Name
    std::string name;
    // Maps name of elems to elements
    std::map<std::string, StructElemDef*> elems;

public:
    StructDef(std::string structName){
        name = structName;
    }

    void addElem(std::string name, std::string type){
        elems[name] = new StructElemDef(type, "0"); 
    }
    
    void update(std::string name, std::string val){
        elems[name]->val = val;
    }
   
    void printDef(){
        std::cout << "struct " << name << " {\n";
        for (auto& elem : elems){
            std::cout << "    " << elem.second->type << " " << elem.first << ";\n";
        }
        std::cout << "};\n";
    } 

};

int main(){
    StructDef abcStruct("abc");
    
    abcStruct.addElem("a", "int");

    abcStruct.printDef();
    
    abcStruct.update("a", "10");
}

