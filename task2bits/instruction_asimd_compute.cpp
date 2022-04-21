#include <iostream>
#include <bitset>

#define printBits(o) std::cout << #o << "=" << std::bitset<sizeof(o) * 8>(o) << std::endl

unsigned int instruction_asimd_compute( unsigned int  i_vec_instr,
                                        unsigned char i_vec_reg_dst,
                                        unsigned char i_vec_reg_src_0,
                                        unsigned char i_vec_reg_src_1 ){
    unsigned int l_vec_reg_dst_mask =   0b00000000'00000000'00000000'00011111;
    unsigned int l_vec_reg_src_0_mask = 0b00000000'00000000'00000011'11100000;
    unsigned int l_vec_reg_src_1_mask = 0b00000000'00011111'00000000'00000000;
    unsigned int l_vec_instr_mask = ~(l_vec_reg_dst_mask | l_vec_reg_src_0_mask | l_vec_reg_src_1_mask);

    return i_vec_instr & l_vec_instr_mask |
        ((i_vec_reg_dst << 0) & l_vec_reg_dst_mask) |
        ((i_vec_reg_src_0 << 5) & l_vec_reg_src_0_mask) |
        ((i_vec_reg_src_1 << 16) & l_vec_reg_src_1_mask);
}

int main(){
    unsigned int output = instruction_asimd_compute(0b01001110001000001100110000000000, 
        0b00000000,
        0b00000001,
        0b00000010);
    printBits(output);
    return 0;
}