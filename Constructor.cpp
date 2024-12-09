// Online C++ compiler to run C++ program online
#include <iostream>

struct car
{
    int m;
    
    //resource obtained by object
    int* resource;
    
    //default
    car(){
        std::cout<<"Default Constructor"<<std::endl<<std::endl;
    }
    
    //parameterized
    car(int m, int* resource){
        this->m=m;
        this->resource=resource;

        std::cout<<"Parameterized Constructor"<<std::endl<<std::endl;
    }
    
    //copy constructor   (user defined)
    car(struct car& x){
        //performing deep copy
        //note: compiler generates copy constructor which performs shallow copy and that can cause dangling pointer issue.
        this->m=x.m;
        this->resource=new int[5];
        memcpy(this->resource, x.resource, 5*sizeof(int));

        std::cout<<"Copy Constructor: Performing deep copy"<<std::endl<<std::endl;
    }
    
    //copy assignment operator
    car& operator=(car& x){
        this->m=x.m;
        this->resource=new int[5];
        memcpy(this->resource, x.resource, 5*sizeof(int));

        std::cout<<"Copy assignment Operator: Performing deep copy"<<std::endl<<std::endl;

        return *this;
    }

    //+ operator
    car operator +(const car& x){
        car res;
        res.m=x.m+this->m;
        res.resource=new int[5];
        for(int i=0;i<5;i++)
        {
            res.resource[i]=x.resource[i]+this->resource[i];
        }

        return res;
    }

    // //user defined move constructor (avoiding deep copy for temporary objects) (optimization)
    // car(car&& ref){
    //     this->m=ref.m;
    //     this->resource=ref.resource;

    //     ref.resource=nullptr;

    //     std::cout<<"Move Constructor: Performing shallow copy"<<std::endl<<std::endl;
    // }

    // //user defined move assignment operator (avoiding deep copy for temporary objects) (optimization)
    // car& operator=(car&& ref){
    //     this->m=ref.m;
    //     this->ref=ref.resource;
        
    //     ref.resource=nullptr;

    //     std::cout<<"Move assignment operator: Performing shallow copy"<<std::endl;
    // }
};

void print(struct car& ref)
{
    std::cout<<"m: "<<ref.m<<std::endl;

    for(int i=0;i<5;i++)
    {
        std::cout<<ref.resource[i]<<" ";
    }
    std::cout<<std::endl<<std::endl;
}

int main() {
    // Write C++ code here
    
    int* memory=new int[5]{1,2,3,4,5};
    struct car x;
    struct car y{10, memory};

    std::cout<<"y info: "<<std::endl;
    print(y);

    struct car z=y;

    std::cout<<"z info: "<<std::endl;
    print(z);

    struct car op;
    
    //below is applicable when move constructor is provided
    //note: op=y; gives segmentation fault because resource is already moved to z, so resource is null in y.
    op=z;

    std::cout<<"op info: "<<std::endl;
    print(op);


    struct car dummy = (y+z);

    std::cout<<"dummy info: "<<std::endl;
    print(dummy);
    
    return 0;
}



// Note: Move semantics is nothing but a user defined copy constructor with r-value reference as a argument.


/*

Resource Management:
• Some classes may own some kind of a resource, and this resource may be a pointer file, handle, socket, thread, etc., and these resources may be acquired by the class in the constructor.
• We have to decide what to do in case the object that holds this kind of resource is copied, moved or destroyed.
For example, during destruction in the destructor, the resource must be released. And this is important in order to avoid leaks.
• Similarly, we also have to decide what to do when the object that holds the resource is copied or moved.


Rules of 5:

What is Rule of 5?
-> These are rules to implement for classes which has taken resource (read above points)

If a class has ownership semantics, then you must provide user-defined:
• Destructor
• Copy Constructor
• Copy assignment operator
• Move constructor
• Move assignment operator

Why we should we do all this?
This is required so that the underlying resource can be correctly handled in case of various class operations.



For example,
-> In the Destructor, the resource may be released.
-> In copy constructor, we may create a copy of the underlying resource.
For example, if the resource is a pointer to heap-based memory, then we should allocate new memory and then copy the data that is inside the memory.
->  In copy assignment operator, we have to do the same thing.
-> In move constructor, we have to ensure that we move the underlying resource from one object to the other. 
-> In move assignment operator, we have to the same like move constructor.



now, Rule of 0:

-> what is Rule of 0?
What if the class does not have ownership semantics, it does not acquire any resource, then in that case we should not implement any function from the rule of 5.

In this case, the compiler will automatically synthesize the necessary functions.

note: Providing user defined implementation of some member functions will prevent the compiler from synthesizing the other member functions.


note: if we want any member function which usually is synthesized by compiler then we can use "default" keyword for telling compiler to synthesize it.



note: You'll find many such classes in the standard library that only provide support for move but not for copy. One example is the unique pointer whose objects can be only moved but not copied.




std::move() function:

std::move() is always used with L values. It forces the compiler to use the move functions instead of the copy.

It forces the compiler to use move semantics instead of copy semantics.


auto b{a};                          //copy of object A in B


Because "a" is l-value, the function overload resolution will choose copy constructor, because the parameter type here is an l-value.


In some cases, you may not want to create a copy of this object.

Instead, you may want to move it into B, but by default, because of function overload resolution, the compiler will always use the copy constructor.

To force the compiler to use the move constructor, we can use move() function   (in reality apply a type cast on this object and the type cast can be a static cast to an r-value reference).

ie
auto b{static_cast<Node&& > (a)};     //calls move instead of copy constructor

note:
auto b{a};                                                      //calls copy construtor
auto b{static_cast<Node&& > (a)};           //calls move construtor

for readability there is Move(), which internally performs the same cast.

auto b{static_cast<Node&& > (a)};   
              =
auto b{ std::move(a) };



note: when we do this programmer intends to move the state from A into B, rather then do copy (deep copy) on l-value references as well.

Why we would want to do this? (ie calling move() for r-value reference)

1. First use:
 After you create a object, and maybe we perform some operations on it and we no longer needed its state, but the state that it contains is required in some other object.
eg:
Node a(1);
a.print();                                 //now lets say we dont need this obj
auto b{std::move(a)};           //but we want its state in some other obj ie b here


eg:

void print(Node val){}

Node a(1);
a.doSomthing();               //a is no longer needed
print(a);                             //but needed inside print


note:
if we dont move, then copy will be created and on end of print() resources of val (which is copied new obj) is released and for "a" release resources will happen again when scope ends.
So, idea is we are optimizing the release of resources by moving the object (its like moving ownership of resource and take deep breathe).


Note: This is optimization, not something mandatory, but its used everytime.

Remember:
after you move from an object, you should not read from it because it is an unspecified state, because ownership is moved, but you can always reinitialize and reuse it.



2. Second use:
Common usage of std::move is with those objects that are non copyable, a non copyable object, does not provide copy operations. Instead, it only provides move operations.

But why would you want to create such a class?
Because the class may contain members that cannot be copied.



NOTE:
std::move() is just a optimization technique, whenever you see it in code then remember that programmer is trying to optimize the code by moving the state of object instead of copying it.
Remember, move semantics prevents creating of new dynamic memory allocation, which is a costly operation.



Which is the best way to make a class object non-copyable?
Ans: by deleting the copy and copy assignment operator

*/