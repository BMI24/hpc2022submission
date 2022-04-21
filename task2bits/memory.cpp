#include <iostream>

int main(){
    std::cout << "sizeof(char)=" << sizeof(char) << std::endl;
    // prints 1
    // sizeof returns the size in bytes, so this is 8 bits
    // this does not match the c# char type (because c# uses UTF-16), I have to keep this in mind

    std::cout << "sizeof(unsigned char)=" << sizeof(unsigned char) << std::endl;
    // prints 1
    // I expect unsigned types to have the same size as signed

    std::cout << "sizeof(unsigned int)=" << sizeof(unsigned int) << std::endl;
    // prints 4
    // regular 32 bit integer, even when its unsigned

    std::cout << "sizeof(float)=" << sizeof(float) << std::endl;
    // prints 4
    // regular 32 bit floating point number

    std::cout << "sizeof(double)=" << sizeof(double) << std::endl;
    // prints 8
    // regular 64 bit floating point number

    std::cout << "sizeof(unsigned int*)=" << sizeof(unsigned int*) << std::endl;
    // prints 8
    // pointer size is dictated by the systems architecture
    // since this is running on a 64 bit system, the pointers should have 8 bytes always

    std::cout << "sizeof(float*)=" << sizeof(float*) << std::endl;
    // prints 8
    // as explained above, this is caused by the 64 bit system-ness

    int* arr = (int*)malloc(sizeof(int)*1500);
    for (int i = 0; i < 1500; ++i){
        arr[i] = 3 * i;
    }

    std::cout << "arr[500]=" << *(arr+500) << std::endl;
    // prints 1500
    // as expected because the arr[500] should be set to 500*3=1500

    std::cout << "memory address of arr[250]=" << arr+250 << std::endl;
    std::cout << "memory address of arr[750]=" << arr+750 << std::endl;
    // prints runtime-dependent memory address
    // interestingly, when running the program though valgrind I always get 0x4d224a8 and 0x4d22c78 (for now)

    std::cout << "Distance in bytes between arr[250] and arr[750]=" << (long)(arr+750) - (long)(arr+250) << std::endl;
    // prints 1000
    // as expected; index difference of 500
    // 500 * sizeof(int) = 500 * 4 = 2000

    free(arr);
    
    return 0;
}