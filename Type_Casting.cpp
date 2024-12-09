#include<iostream>

class Person
{
    public:
    int data;
    Person(){}
    Person(int data){
        this->data=data;
    }

    explicit operator int();             // C++11 allows us to use the explicit keyword on the operator function so that the compiler can never use implicit conversion.
                                         // so, now Person p7{ 9002 }; int temp = p7; will give error because compiler will not be able to implicitly call this function
};

Person::operator int(){
    return data;
}


int main()
{    
    std::cout<<std::endl<<std::endl;
    std::cout<<"***********************Type Casting***********************"<<std::endl;
    int a=100, b=3;
    float f=a/b;                    //wrong implicit type cast: loss of data           
    float f2=(float)a/b;            //explicit type cast: C style
    float f3=static_cast<float>(a)/b;   //explicit type cast: C++ style
    std::cout<<std::endl<<std::endl;
    std::cout<<"Implict type cast:"<<std::endl<<"f: "<<f<<std::endl;
    std::cout<<"Explicit type caste (C style) "<<std::endl<<"f2: "<<f2<<std::endl;
    std::cout<<"Explicit type caste (C++ style) "<<std::endl<<"f3: "<<f3<<std::endl;

    int c=0x3E8;                            //c=1000
    char* str=(char*)&c;                    //using C style cast this conversion is easily allowed, ie type casting pointer to different type
    // char* str2=static_cast<char*>(&c);      //but C++ style cast throws error because we ideally we shouldnot type caste pointer to different type

    char* reinterpret_str=reinterpret_cast<char*>(&c);  //in C++ style type casting there is reinterpret_cast for converting ponters between different types
    
    int* ptr=&c;
    std::cout<<std::endl<<std::endl;
    std::cout<<"Using same pointer type: addr= "<<ptr<<std::endl;
    std::cout<<"*ptr --> "<<*ptr<<std::endl;

    std::cout<<std::endl<<std::endl;
    std::cout<<"Using different pointer type: addr= "<<std::hex<<(void*)str<<std::endl;
    std::cout<<"*str first byte --> "<<std::hex<<(int)(*str)<<std::endl;
    std::cout<<"*str second byte--> "<<std::hex<<(int)(*(str+1))<<std::endl;

    std::cout<<std::endl<<std::endl;
    std::cout<<"Using reinterpret_cast<>: "<<std::endl;
    std::cout<<"Using different pointer type: addr= "<<std::hex<<(void*)reinterpret_str<<std::endl;
    std::cout<<"*str first byte --> "<<std::hex<<static_cast<int>(*reinterpret_str)<<std::endl;
    std::cout<<"*str second byte--> "<<std::hex<<static_cast<int>(*(reinterpret_str+1))<<std::endl;

    std::cout<<"*******************Primitive to User defined type conversion*********************************************"<<std::dec<<std::endl<<std::endl;

    int int_var=9999;
    Person p1{ int_var };                 //integer to user defined type conversion (is done using constructor)
    Person p2{ 1000 };                     //converted using parameterised constructor
    
    //note: above two are explicit type conversion

    Person p3 = 4999;                   //this is implicit primitive to user defined type conversion

    std::cout<<"Person1: "<<p1.data<<std::endl;
    std::cout<<"Person2: "<<p2.data<<std::endl;

    // Remember:
    // Constructors are used by the compiler implicitly to convert one type into another. If you want to prevent the compiler from using the constructors implicitly, you can mark them with the explicit keyword.

    std::cout<<"*******************User defined to Primitive type conversion*********************************************"<<std::dec<<std::endl<<std::endl;


    Person p7{ 9002 };
    //int temp = p7;                    //type casted because of operator<int>(); (type conversion operator) defined inside user defined type
    //note: the compiler implicitly invokes the type conversion operator function.

    //note: line 74 is giving now error because we added explicit keyword, correct way is to do like this:
    int temp = static_cast<int>(p7);
    
    std::cout<<std::endl<<std::endl;
    std::cout<<"temp: "<<temp<<std::endl;

    std::cout<<"*******************User defined to User Define type conversion*********************************************"<<std::dec<<std::endl<<std::endl;
    

    return 0;
}

/*
C-style casts are discouraged in C++ because they do not check for the validness of the cast. So that is why C++ provides a casting operator called as static_cast. Static_cast is superior to C-style casting because it checks,
if the cast is valid or not.



note: 
C-style cast discards the qualifiers but if we had used a reinterpret_cast, it does not discard the qualifiers.


const int x=9;
int* ptr=&x;                   
//this is error because we are pointing int type pointer to const int

int* ptr=(int*)&x;                      //this works fine, C style cast discards qualifiers
int* ptr=reinterpret_cast<int*>(&x);           //but this gives error

*/