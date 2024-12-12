#include <iostream>

int main() {
    std::cout<<"*********************************************************************************************************************"<<std::endl;

    int x = 1000;
    int& l_ref = x;
    int&& r_ref = 120;
    
    std::cout<<"before conversion"<<std::endl<<" lref: "<<l_ref<<" rref: "<<r_ref<<std::endl;

    l_ref = r_ref;                           //changing value of l_ref and accordingly x
    std::cout<<"after conversion 2"<<std::endl<<" lref: "<<l_ref<<" rref: "<<r_ref<<std::endl;
    std::cout<<std::endl<<std::endl;
    
    std::cout<<"*********************************************************************************************************************"<<std::endl;

    int memory = 1123;
    int& lvalue_ref = memory;
    int&& rvalue_ref = 1234;
    std::cout<<"before conversion"<<std::endl<<" lvalue_ref: "<<lvalue_ref<<" rvalue_ref: "<<rvalue_ref<<std::endl;

    rvalue_ref = lvalue_ref;                 //changing value of rvalue_ref
    std::cout<<"after conversion 2"<<std::endl<<" lvalue_ref: "<<lvalue_ref<<" rvalue_ref: "<<rvalue_ref<<std::endl;

    int variable = 7889;
    int& lvalue_ref2 = variable;
    int&& rvalue_ref2 = 999;
    
    rvalue_ref2 = variable;                     //changing value of rvalue_ref
    std::cout<<"after conversion 3"<<std::endl<<" lvalue_ref2: "<<lvalue_ref2<<" rvalue_ref2: "<<rvalue_ref2<<std::endl;
    variable = 909038;
    std::cout<<"after conversion 4"<<std::endl<<" lvalue_ref2: "<<lvalue_ref2<<" rvalue_ref2: "<<rvalue_ref2<<std::endl;
    std::cout<<std::endl<<std::endl;

    std::cout<<"*********************************************************************************************************************"<<std::endl;
    //note: How references can be converted

    int memory2 = 1987;
    int& lvalue_ref3 = memory2;
    int&& rvalue_ref3 = (int&&)memory2;
    int&& rvalue_ref4 = (int&&)lvalue_ref3;
    //int& lvalue_ref4 = (int&)98881;                              //not allowed because lvalue_ref4 is lvalue reference and 98881 is rvalue
    int&& rvalue_ref5 = 98881;
    int& lvalue_ref5 = (int&)rvalue_ref5;                          // and int& lvalue_ref5 = rvlaue_ref5;   both are allowed

    std::cout<<"before conversion"<<std::endl<<" lvalue_ref3: "<<lvalue_ref3<<" rvalue_ref3: "<<rvalue_ref3<<" rvalue_ref4: "<<rvalue_ref4<<" rvalue_ref5: "<<rvalue_ref5<<" lvalue_ref5: "<<lvalue_ref5<<std::endl;
    return 0;
}



//Remember: while rvalue references are primarily intended to bind to temporary objects, they can still be assigned values from lvalues after their initial binding.

// Using std::move to cast lvalue to rvalue --------> int&& rvalue_ref2 = std::move(a);