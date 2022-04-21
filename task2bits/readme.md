# Übung 2 - Bits

## Task 3.1.

Dokumentiert in `memory.cpp`. Nach Kompilieren mit `-g -O0` hat Valgrind 79,728 in 3 Allokationen und keine Memory Leaks gemeldet.

## Task 3.2.1

Dokumentiert in `data_type_sizes.cpp`

## Task 3.2.2

Funktion:
```
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
```

Tests dazu siehe `instruction_asimd_compute.cpp`.

## Task 3.2.3

Die Funktion aus Task 3.2.2 kombiniert die Parameter aus denen ARM A64 Vektor-Instruktionen bestehen (zwei Eingaberegister, ein Ausgaberegister und dem Instruktionscode) zu 32 Bit zusammen, vermutlich wie bei assemblierten (?) Assembler Code. zB passt es zu den Instruktionen AND, BFDOT, BFMLALB, BFMLALT, ...

Andere Vektor Operationen scheinen dem selben Schema zu folgen, haben jedoch zB einen weiteren Size-Parameter (siehe Bits 21-22 bei ADD, ADDP (vector)). 

Außerdem gibt es Instruktionen wie CLZ und CLS haben keine 2 Eingaberegister. In diesen Beispielen ist der Instruktionscode jedoch bei den relevanten Bits für das zweite Eingaberegister (Bits 16-20) 0. Leider habe ich für alle beobachteten Muster kein zugrundeliegendes Design-Dokument gefunden, weswegen es möglich ist, dass ich einfach die nicht passenden Instruktionen in Betracht gezogen habe.

Instruktionen siehe [ARM 64 SIMD&FP Instructions]( https://developer.arm.com/documentation/ddi0596/2020-12/SIMD-FP-Instructions?lang=en)