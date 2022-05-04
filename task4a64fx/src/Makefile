BUILD_DIR = ./build

micro_asimd: driver_asimd.cpp kernels/peak_asimd_fmla_sp.s kernels/peak_asimd_fmla_dp.s kernels/peak_asimd_fmadd_sp.s kernels/peak_asimd_fmadd_dp.s
		gcc -pedantic -Wall -Wextra -Werror -c kernels/peak_asimd_fmla_sp.s -o ${BUILD_DIR}/peak_asimd_fmla_sp.o
		gcc -pedantic -Wall -Wextra -Werror -c kernels/peak_asimd_fmla_dp.s -o ${BUILD_DIR}/peak_asimd_fmla_dp.o
		gcc -pedantic -Wall -Wextra -Werror -c kernels/peak_asimd_fmadd_sp.s -o ${BUILD_DIR}/peak_asimd_fmadd_sp.o
		gcc -pedantic -Wall -Wextra -Werror -c kernels/peak_asimd_fmadd_dp.s -o ${BUILD_DIR}/peak_asimd_fmadd_dp.o
		g++ -pedantic -Wall -Wextra -Werror -O2 -fopenmp driver_asimd.cpp ${BUILD_DIR}/peak_asimd_fmla_sp.o ${BUILD_DIR}/peak_asimd_fmla_dp.o ${BUILD_DIR}/peak_asimd_fmadd_sp.o ${BUILD_DIR}/peak_asimd_fmadd_dp.o -o ${BUILD_DIR}/micro_asimd
	
micro_sve: driver_sve.cpp kernels/peak_sve_fmla_sp.s kernels/peak_sve_fmla_dp.s
		gcc -march=armv8-a+sve -pedantic -Wall -Wextra -Werror -c kernels/peak_sve_fmla_sp.s -o ${BUILD_DIR}/peak_sve_fmla_sp.o
		gcc -march=armv8-a+sve -pedantic -Wall -Wextra -Werror -c kernels/peak_sve_fmla_dp.s -o ${BUILD_DIR}/peak_sve_fmla_dp.o
		g++ -pedantic -Wall -Wextra -Werror -O2 -fopenmp driver_sve.cpp ${BUILD_DIR}/peak_sve_fmla_sp.o ${BUILD_DIR}/peak_sve_fmla_dp.o -o ${BUILD_DIR}/micro_sve

all: micro_asimd micro_sve

$(shell mkdir -p build)
