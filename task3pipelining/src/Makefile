BUILD_DIR = ./build

micro_asimd: driver_asimd.cpp kernels/latency_src_asimd_fmla_sp.s kernels/latency_src_asimd_fmul_sp.s
		gcc -pedantic -Wall -Wextra -Werror -c kernels/latency_src_asimd_fmla_sp.s -o ${BUILD_DIR}/latency_src_asimd_fmla_sp.o
		gcc -pedantic -Wall -Wextra -Werror -c kernels/latency_src_asimd_fmul_sp.s -o ${BUILD_DIR}/latency_src_asimd_fmul_sp.o
		gcc -pedantic -Wall -Wextra -Werror -c kernels/latency_dst_asimd_fmla_sp.s -o ${BUILD_DIR}/latency_dst_asimd_fmla_sp.o
		gcc -pedantic -Wall -Wextra -Werror -c kernels/latency_dst_asimd_fmul_sp.s -o ${BUILD_DIR}/latency_dst_asimd_fmul_sp.o
		g++ -pedantic -Wall -Wextra -Werror -O2 -fopenmp driver_asimd.cpp ${BUILD_DIR}/latency_src_asimd_fmla_sp.o ${BUILD_DIR}/latency_src_asimd_fmul_sp.o ${BUILD_DIR}/latency_dst_asimd_fmla_sp.o ${BUILD_DIR}/latency_dst_asimd_fmul_sp.o -o ${BUILD_DIR}/micro_asimd
		

all: micro_asimd

$(shell mkdir -p build)
