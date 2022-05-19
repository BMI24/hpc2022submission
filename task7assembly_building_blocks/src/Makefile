BUILD_DIR = ./build

gemm: driver_gemm.cpp kernels/gemm_asm_sve_64_6_1.s kernels/gemm_ref.cpp
		gcc -march=armv8-a+sve -g -pedantic -Wall -Wextra -Werror -c kernels/gemm_asm_sve_64_6_1.s -o ${BUILD_DIR}/gemm_asm_sve_64_6_1.o
		gcc -march=armv8-a+sve -g -pedantic -Wall -Wextra -Werror -c kernels/gemm_asm_sve_64_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_64_6_48.o
		g++ -pedantic -Wall -Wextra -Werror -O2 -fopenmp driver_gemm.cpp ${BUILD_DIR}/gemm_asm_sve_64_6_1.o ${BUILD_DIR}/gemm_asm_sve_64_6_48.o -o ${BUILD_DIR}/driver_gemm

all: gemm

$(shell mkdir -p build)
