BUILD_DIR = ./build

load_asm: driver_load_asm.cpp kernels/load_asm.s
		gcc -pedantic -Wall -Wextra -Werror -g -c kernels/load_asm.s -o ${BUILD_DIR}/load_asm.o
		g++ -pedantic -Wall -Wextra -Werror -g driver_load_asm.cpp ${BUILD_DIR}/load_asm.o -o ${BUILD_DIR}/load_asm
		
copy: driver_copy.cpp kernels/copy.s
		gcc -pedantic -Wall -Wextra -Werror -c kernels/copy.s -o ${BUILD_DIR}/copy_asm.o
		g++ -pedantic -Wall -Wextra -Werror -O2 -S -c kernels/copy.c -o ${BUILD_DIR}/copy_c.s
		g++ -pedantic -Wall -Wextra -Werror -O2 -c kernels/copy.c -o ${BUILD_DIR}/copy_c.o
		g++ -pedantic -Wall -Wextra -Werror driver_copy.cpp ${BUILD_DIR}/copy_asm.o ${BUILD_DIR}/copy_c.o -o ${BUILD_DIR}/copy_asm

gemm: driver_gemm.cpp kernels/gemm_asm_gp.s
		gcc -pedantic -Wall -Wextra -Werror -c kernels/gemm_asm_gp.s -o ${BUILD_DIR}/gemm_asm_gp.o
		g++ -pedantic -Wall -Wextra -Werror driver_gemm.cpp ${BUILD_DIR}/gemm_asm_gp.o -o ${BUILD_DIR}/gemm

all: load_asm copy gemm

$(shell mkdir -p build)