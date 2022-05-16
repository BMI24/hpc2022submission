# Übung 6 Writing Assembly Code: AArch64

## Task 6.1

(included in next tasks)

## Task 6.2.1

`ldr x1, [x0, #8]!` loads a 64 bit (x1=extended (64 bit) view of the register) value from memory at the address stored in register `x0` (which is the first input value for the kernel) AFTER incrementing `x0` by 8 (bytes). This is called a pre-increment/pre-indexed immediate offset. Basicaly `x1=x0+8; x1=memory[x1];` 
`ldp x2, x3, [x0]` loads two consecutive 64 bit values (a pair) from memory at the address stored in register `x0` (which is still changed by the last command). Basicaly `x2=memory[x0]; x3=memory[x0+8]`. `x1` and `x2` should contain the same value now.
`ldp x4, x5, [x0, #16]` loads two consecutive 64 bit values from memory at the adress stored in register `x0` + 16 bytes (without changing `x0`). Basicaly `x4=memory[x0+16]; x5=memory[x0+16+8]`.

The driver initializes `l_a` as `[100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]` and passes `l_a+2` into the kernel as `x0`, which points to value 300 in the array. As each value is 8 bytes/64 bits long, we get the following values in the registers:
```
x1=400
x2=400
x3=500
x4=600
x5=700
```

## Task 6.2.2

To load gdb4hpc: `module load gdb4hpc`. Then launch it: `gdb4hpc` and use `maint set unsafe on`. Launch our program using `launch $prog1 ./build/load_asm` and enter regular gdb mode using `gdbmode`. Set the breakpoint `break load_asm`. Continue running till the next breakpoint using `continue` (error `prog1{0}: Debugger error: Hit unknown breakpoint!` is expected/can be ignored). Use `info registers` to display the contents of the registers. Use `step`to advance one instruction. Stepping to line 10 and then using `info registers` shows that registers `x1` to `x5` contain the expected content (see solution for 6.2.1). Use `quit` to exit gdb.

## Task 6.2.3

To load valgrind4hpc: `module load valgrind4hpc`.
After uncommenting `not ok #1` I get three errors when using `valgrind4hpc ./build/load_asm`:
```
RANKS: <0>

Invalid read of size 8
  at main (in driver_load_asm.cpp:19)
Address is 24 bytes after a block of size 80 in arena "client"


RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:7)
Address is 24 bytes after a block of size 80 in arena "client"


RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:8)
Address is 24 bytes before an unallocated block of size 4,121,296 in arena "client"
```

`l_a+12` points behind our allocated memory, so every memory access is bad. The first warning seems to be miss-attributed to `driver_load_asm.cpp:19` (which just calls the kernel) instead of `load_asm.s:6` (which really is a problematic memory access). The following two errors are expected, because every memory access after address `l_a+9` is bad.

After uncommenting `not ok #2` I get two errors when using `valgrind4hpc ./build/load_asm`:
```
RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:7)
Address is 0 bytes after a block of size 80 alloc'd
  at operator new[](unsigned long) (in vg_replace_malloc.c:429)
  by main (in driver_load_asm.cpp:10)


RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:8)
Address is 8 bytes after a block of size 80 alloc'd
  at operator new[](unsigned long) (in vg_replace_malloc.c:429)
  by main (in driver_load_asm.cpp:10)
```
`load_asm.s:6` does not cause a error anymore because it accesses `*(l_a+8+1)` which is still in our allocated memory. `load_asm.s:7` causes a error because it tries to access `*(l_a+8+1)` (which is ok) and `*(l_a+8+2)` (which is bad). Similarly, `load_asm.s:8` also causes a error.

After uncommenting `not ok #3` I get one error when using `valgrind4hpc ./build/load_asm`:
```
RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:8)
Address is 0 bytes after a block of size 80 alloc'd
  at operator new[](unsigned long) (in vg_replace_malloc.c:429)
  by main (in driver_load_asm.cpp:10)
```
`load_asm.s:7` does not cause a error anymore because its accessing `*(l_a+6+1)` and `*(l_a+6+2)` which is okay. `load_asm.s:8` tries to access `*(l_a+6+3)` (okay) and `*(l_a+6+4)` (bad).

## Task 6.3

Created kernels. Relevant compiler generated assembler code (using `-O2 -S`):
```
	ldp	w7, w6, [x0]
	ldp	w5, w4, [x0, 8]
	ldp	w3, w2, [x0, 16]
	ldr	w0, [x0, 24]
	stp	x7, x6, [x1]
	stp	x5, x4, [x1, 16]
	stp	x3, x2, [x1, 32]
	str	x0, [x1, 48]
	ret
```
Very similar to my hand-written assembler-code. Differences:
- offsets dont use `#` prefix
- starting with `w7`, then `w6`, ... (I'm starting with `w2`, `w3`, ...)
- Compiler uses `w0` to store last value of array (I use w8 which is fine according to ABI)

We can use a disassembler to get similar code: `objdump -d ./build/copy_c.o`
```
./build/copy_c.o:     file format elf64-littleaarch64


Disassembly of section .text:

0000000000000000 <_Z6copy_cPKjPm>:
   0:   29401807        ldp     w7, w6, [x0]
   4:   29411005        ldp     w5, w4, [x0, #8]
   8:   29420803        ldp     w3, w2, [x0, #16]
   c:   b9401800        ldr     w0, [x0, #24]
  10:   a9001827        stp     x7, x6, [x1]
  14:   a9011025        stp     x5, x4, [x1, #16]
  18:   a9020823        stp     x3, x2, [x1, #32]
  1c:   f9001820        str     x0, [x1, #48]
  20:   d65f03c0        ret
```

Note: Both the Assembly and C kernels could be written using a loop (which probably takes longer using less instructions)

## Task 6.4

Done. (driver: `driver_gemm.cpp`, test passed)