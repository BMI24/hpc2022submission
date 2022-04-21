#include <iostream>
#include <bitset>

#define printBits(o) std::cout << #o << "=" << std::bitset<sizeof(o) * 8>(o) << std::endl

int main() {
    unsigned char l_data1  = 1;
    printBits(l_data1);
    // prints l_data1=00000001
    // unsigned char is typicaly 8 bits long, 1 is stored as expected

    unsigned char l_data2  = 255;
    printBits(l_data2);
    // prints l_data2=11111111
    // 255 is the largest number that can be stored with 8 bits so its all 1 
    
    unsigned char l_data3  = l_data2 + 1;
    printBits(l_data3);
    // prints l_data3=00000000
    // adding 1 to l_data2 causes an integer overflow, wrapping back to all 0
    
    unsigned char l_data4  = 0xA1;
    printBits(l_data4);
    // prints l_data4=10100001
    // using hex notation to set integers
    // hex A = dec 10 and bin 1010
    // hex 1 = dec  1 and bin 0001
    // concatinating them we get the printed value


    unsigned char l_data5  = 0b1001011;
    printBits(l_data5);
    // prints l_data5=01001011
    // using bin notation we can set bit values of int directly

    unsigned char l_data6  = 'H';
    printBits(l_data6);
    // prints l_data6=01001000
    // 'H' has ascii encoding of dec 72 = bin 01001000

             char l_data7  = -4;
    printBits(l_data7);
    // prints l_data7=11111100
    // two's complement is used for negative numbers
    
    unsigned int  l_data8  = 1u << 11;
    printBits(l_data8);
    // prints l_data8=00000000000000000000100000000000
    // both unsigned ints and ints typicaly are 4 bytes = 32 bits long
    // 1u means 1 unsigned (dont think this makes a difference in this case)
    // shifting bin 1 by 11 bits to the left creates the observed output (gets filled with 0)
    
    unsigned int  l_data9 = l_data8 << 21;
    printBits(l_data9);
    // prints l_data9=00000000000000000000000000000000
    // shifting l_data8 by 21 to the right moves the 1 just out of bounds, resulting in all 0
    
    unsigned int  l_data10  = 0xFFFFFFFF >> 5;
    printBits(l_data10);
    // prints l_data10=00000111111111111111111111111111
    // 0xFFFFFFFF is a unsigned value, thus a logical right shift is used (filling with 0 in every case)

    unsigned int  l_data11 = 0b1001 ^ 0b01111;
    printBits(l_data11);
    // prints l_data11=00000000000000000000000000000110
    // ^ is the xor operator
    // 1001 xor 1111 = 0110, padded with 0 results in observed output
    
    unsigned int  l_data12 = ~0b1001;
    printBits(l_data12);
    // prints l_data12=11111111111111111111111111110110
    // 1001 gets padded with 0 on the left, then all bits get inverted
    
    unsigned int  l_data13 = 0xF0 & 0b1010101;
    printBits(l_data13);
    // prints l_data13=00000000000000000000000001010000
    // hex F0 = bin                            11110000
    // logical and with                         1010101 results in output
    
    unsigned int  l_data14 = 0b001 | 0b101;
    printBits(l_data14);
    // prints l_data14=00000000000000000000000000000101
    // simple logical or operation
    
    unsigned int  l_data15 = 7743;
    printBits(l_data15);
    // prints l_data15=00000000000000000001111000111111
    // 7743 = 1 * 4096 + 3647
    // 3647 = 1 * 2048 + 1599
    // 1599 = 1 * 1024 + 575
    // 575  = 1 *  512 + 63
    // 63   = 0 *  256 + 63
    // 63   = 0 *  128 + 63
    // 63   = 0 *   64 + 63
    // 63   = 1 *   32 + 31
    // 31   = 1 *   16 + 15
    // 15   = 1 *    8 + 7
    // 7    = 1 *    4 + 3
    // 3    = 1 *    2 + 1
    // 1    = 1 *    1 + 0
    
             int  l_data16 = -7743;
    printBits(l_data16);    
    // prints l_data16=11111111111111111110000111000001
    // twos complement, basicaly equals ~l_data15 + 1
}