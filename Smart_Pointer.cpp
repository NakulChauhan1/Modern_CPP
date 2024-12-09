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

int main(){
    std::cout<<"Smart Pointers"<<std::endl;

    int var=10;

    int* ptr=&var;                           //using raw pointer
    std::unique_ptr<int> uptr( &var );       //using smart pointer

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

    TODOOOO:
    // std::vector<int> array{1,2,3,4,5};
    // std::unique_ptr<std::vector<int>> sptr2(array.data());



    return 0;
}
