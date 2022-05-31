BUILD_DIR = ./build

gemm: driver_gemm.cpp kernels/gemm_asm_sve_128_6_48.S kernels/gemm_asm_sve_128_48_48.S kernels/gemm_ref.cpp
		gcc -march=armv8-a+sve -g -pedantic -Wall -Wextra -Werror -c kernels/gemm_asm_sve_128_6_48.S -o ${BUILD_DIR}/gemm_asm_sve_128_6_48.o
		gcc -march=armv8-a+sve -g -pedantic -Wall -Wextra -Werror -c kernels/gemm_asm_sve_128_48_48.S -o ${BUILD_DIR}/gemm_asm_sve_128_48_48.o
		g++ -std=c++17 -pedantic -Wall -g -Wextra -Werror driver_gemm.cpp ${BUILD_DIR}/gemm_asm_sve_128_6_48.o ${BUILD_DIR}/gemm_asm_sve_128_48_48.o -o ${BUILD_DIR}/driver_gemm
all: gemm

$(shell mkdir -p build)
