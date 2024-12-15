#include <iostream>

int main() {
    // Lambdas are a feature of C++ that allows you to define a function at the location where you want to use it.

    [](){
        std::cout << "Anonymous lambada expression but not called"<<std::endl;
    };

    [](){
        std::cout << "Anonymous lambada expression but called"<<std::endl;
    }();

    auto fn = [](){
        std::cout << "Named lambada expression"<<std::endl;
    };
    
    fn();
    

    return 0;
}