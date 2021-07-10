#include <iostream>
#include <typeinfo>

class ABS
{
private:
    /* data */
public:
    ABS(/* args */) {}
    virtual ~ABS() {}
    virtual void qwe() {}   
};

class ABD : public ABS
{
private:
    /* data */
public:
    ABD(/* args */) {}
    ~ABD() {}
    void qwe () override{
        
    }
};

void print (const std::type_info& asd){
    std::cout << "Typeinfo: " << asd.name() << std::endl;
}

void verbose_print (const std::type_info& ty){
    
    if (ty == typeid(ABS)){
        std::cout << "Found ABS" << std::endl;
    }
    
    else if (ty == typeid(ABD)){
        std::cout << "Found ABD" << std::endl;
    }

    else {
        std::cout << "What !!" << std::endl;
    }   
}
    



int main(int argc, const char** argv) {
    ABS abs;
    ABS* abd = new ABD();
  
    print (typeid(abs));

    print (typeid(*abd));

    std::cout << "Type abd: " << typeid(abd).name() << std::endl;
    std::cout << "Type *abd: " << typeid(*abd).name() << std::endl;

    verbose_print(typeid(abs));
    verbose_print(typeid(abd));
    verbose_print(typeid(*abd));
    return 0;
}