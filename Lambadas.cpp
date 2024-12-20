#include <iostream>
#include <functional>

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

    std::cout<<" typeid: "<<typeid(fn).name()<<std::endl<<std::endl;

    auto sum = [](int x, int y){
        return x+y;
    };

    std::cout<<"Sum: "<<sum(2,3)<<std::endl<<std::endl;

    auto dummy = [](int x, int y)->double {                      //here we have to mention type of value to be returned because lambda returns from multiple places.
        if(0){
            return 7.0;
        }
        return x+y;
    };
    
    std::cout<<"Dummy: "<<dummy(10,20)<<std::endl;
    

    int var = 100;
    auto print = [var]() mutable{
        std::cout<<"Print function, var="<<var<<std::endl;
        var = 200;
        std::cout<<"after modification, var="<<var<<std::endl;
    };

    print();
    std::cout<<"var= "<<var<<std::endl<<std::endl; 
    std::cout<<std::endl<<std::endl;

    auto print_capturebyref = [&var]() {
        std::cout<<"print_capturebyref function, var="<<var<<std::endl;
        var = 200;
        std::cout<<"after modification, var="<<var<<std::endl;
    };

    print_capturebyref();
    std::cout<<"var= "<<var<<std::endl<<std::endl;
    std::cout<<std::endl<<std::endl;

    int dummyvar = 2345;
    std::string name = "Nakul Chauhan";

    auto printcapbyallref = [&](){
        std::cout<<"printcapbyallref, var="<<var<<" dummyvar: "<<dummyvar<<" name: "<<name<<std::endl;
        var = 190;
        dummyvar = 89;
        name = "Nakul";
        std::cout<<" var="<<var<<" dummyvar="<<dummyvar<<" name: "<<name<<std::endl;
    };
    printcapbyallref();N
    std::cout<<"after lambda:"<<std::endl<<std::endl<<" var= "<<var<<" dummyvar= "<<dummyvar<<" name= "<<name<<std::endl;
    std::cout<<std::endl<<std::endl;


    std::cout<<"****************************************std::functions***************************************** "<<std::endl;
    std::function <int(double)>fobj1 = [](double x)->int {
        std::cout<<" x= "<<x<<std::endl;
        double y=x;
        return y;  
    };

    std::cout<<" outside std::func, "<<std::endl<<fobj1(900)<<std::endl;

    /*std::function, how it can be used as a general purpose function wrapper.
      It can wrap a function, a function object, or a lambda expression.*/


    return 0;
}
