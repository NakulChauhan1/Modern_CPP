#include<iostream>
#include<memory>
#include<vector>

// class dummy{
//     public:
//     int x;

//     void print(){
//         std::cout<<" x: "<<x<<std::endl;

//         std::cout<<"arr: "<<std::endl;
//         for(auto i:arr){
//             std::cout<<arr[i]<<" ";
//         }
//         std::cout<<std::endl;
//     }
// }
void print(int* ptr, int size){

    for(int i=0;i<size;i++){
        std::cout<<ptr[i]<<" ";
    }
    std::cout<<std::endl;
}

void print(std::shared_ptr<int[]> sptr, int size){
    std::cout<<"Reference count (inside print fxn ): "<<sptr.use_count()<<std::endl;
    for(int i=0;i<size;i++){
        std::cout<<" sptr[i] = "<<sptr[i]<<" ";
    }
    std::cout<<std::endl;
}

int main(){
    std::cout<<"Smart Pointers"<<std::endl;

    int* ptr=new int{55};                           //using raw pointer
    std::unique_ptr<int> uptr( ptr );       //using smart pointer

    std::cout<<"var="<<*ptr<<std::endl;
    std::cout<<"var="<<*uptr<<std::endl;


    int* arr =  new int[5]{1,3,5,7,9};        //using raw pointer
    std::unique_ptr<int[]> sptr( arr );       //using smart pointer
    std::unique_ptr<int[]> sptr1( new int[5]{10,20,30,40,50} );


    print(arr, 5);

    std::cout<<"using sptr( arr ) "<<std::endl;
    print(sptr.get(), 5);
    print(sptr1.get(), 5);

    // std::unique_ptr<int> uptr2(uptr);                       //error: because copy is not allowed with unique pointer
    // std::unique_ptr<int> uptr3 = uptr;                      //error: because copy is not allowed with unique pointer
    std::unique_ptr<int> uptr4 = std::move(uptr);              //not an error: because copy is not allowed with unique pointer, but moving of a resource is allowed
    // std::cout<<"var="<<*uptr<<std::endl;                    //runtime error: because uptr underlying resource (ie int here) is moved to uptr4
                                                               //note: we cannot use objects like unique pointer once they are moved


    std::shared_ptr<int> sharedptr1( new int(1000) );
    std::cout<<"sharedptr1: "<<*sharedptr1<<std::endl;

    std::shared_ptr<int> sharedptr2(sharedptr1);
    std::cout<<"sharedptr2: "<<*sharedptr2<<std::endl;
    std::cout<<"sharedptr1: "<<*sharedptr1<<std::endl;        //can access even after assigning to some other pointer

    // TODOOOO:
    // std::vector<int> array{1,2,3,4,5};
    // std::unique_ptr<std::vector<int>> sptr2(array.data());

    std::cout<<"******************************************** Weak Pointers *************************************************************************"<<std::endl;
    std::shared_ptr<int[]> sharedptr3{ new int[5]{1,2,3,4,5} };
    std::shared_ptr<int[]> sharedptr4;
    sharedptr4 = sharedptr3;

    print(sharedptr3, 5);
    print(sharedptr4, 5);

    std::cout<<"Reference count, sharedptr3: "<<sharedptr3.use_count()<<std::endl;
    std::cout<<"Reference count, sharedptr4: "<<sharedptr4.use_count()<<std::endl;

    sharedptr3 = NULL;                  //make pointer NULL to decrement reference count, its like freeing memory, but in reality memory is freed after object will go out of scope

    std::cout<<"Reference count, sharedptr3: "<<sharedptr3.use_count()<<std::endl;
    std::cout<<"Reference count, sharedptr4: "<<sharedptr4.use_count()<<std::endl;

    std::cout<<std::endl<<"after freeing sharedptr3"<<std::endl;
    
    print(sharedptr4, 5);
    // print(sharedptr3, 5);

    //note: above when one object is released then other object which was assigned from it still points to that underlying resource, this may be not wanted in some situations.
    /* in some places, we would want if original object is freed then other object which were initialized from it should also get released. We would want some kind of communication
       between these objects. (from there comes the need of new shared pointer called as weak_pointer) */


    std::shared_ptr<int> sharedptr5 {new int { 97800 }};
    std::weak_ptr<int> wkptr {sharedptr5};

    std::cout<<"Printing information via weak ptr"<<std::endl;

    if (std::shared_ptr<int> sptrrrr = wkptr.lock()) { // Obtain a shared_ptr from the weak_ptr
        std::cout << "Weak ptr: " << *sptrrrr << std::endl;
    } else {
        std::cout << "The managed object has been deleted." << std::endl;
    }

    std::cout<<"Weak ptr: "<<*wkptr<<std::endl;


    return 0;
}
