// In Python, integers have arbitrary precision and byte conversions happen 
// under the hood with int.to_bytes() or struct.pack(). In C, everything sits at concrete addresses in virtual memory.

// Problem
// Write a function void reverse_bytes(void *ptr, size_t size) that reverses the 
// raw bytes of any data type in place, without using heap allocation (malloc/free) or library string functions (memcpy/memmove).

// Then, use this function to test reversing:
// A 32-bit unsigned integer 0xAABBCCDD.
// A double or a small struct.

//soluton intrepe

#include<stdio.h>
#include<stdint.h>
#include <inttypes.h> // Required for PRIu32

// void reverse_bytes(void *ptr, size_t size){
//     //size in bytes is size variable(uint 64)
//     char * addr = (char *)ptr;
//     int left = 0;
//     int right = size -1;
//     while (left < right){
//         char temp = addr[left]; //*(addr + left) // returns that byte interpreted as charcter
//         addr[left] = addr[right];
//         addr[right] = temp;

//         left++;
//         right--;
//     }
// }

typedef unsigned char uint8;
//we can use from the header file uint8_t but i just want to use this 


void reverse_bytes(void *ptr, size_t size){

    uint8 * start = (unsigned char *)ptr;
    uint8 *end = start + (size - 1);
    //instead of bounding by ints we are bouding by memroy address itself
    while(start < end){
        uint8 temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }


}


int main(){
    //32
    uint32_t x = 32;
    //00000000 00000000 00000000 00100000
    //we are supposed to rever is it byte byte
    //00100000 00000000 00000000 00000000 -> 2^29
    printf("before value is: %" PRIu32 "\n", x);
    // char * start = (char *)&x;

    // for(int i = 0; i < 4; i++){
    //     printf("%c",start[i]);
    // }
    // printf("\n");


    // char char1 = *(start);  // interpret and assign first byte as char
    // char char2 = *(start+1);
    // char char3 = *(start+2);
    // char char4 = *(start+3);
    
    // start[0] = char4; // start[0] == *(start+0)
    // start[1] = char3;
    // start[2] = char2;
    // start[3] = char1;   

    reverse_bytes(&x, 4); 
    
    // for(int i = 0; i < 4; i++){
    //     printf("%c",start[i]);
    // }
    // printf("\n");



    printf("after value is: %" PRIu32 "\n", x);

    return 0;    

}