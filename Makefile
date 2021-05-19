CFLAGS= -mno-mips16 -mgp32 -mfp32 -gpubnames  -mlong32 -mips1 -mabicalls -mlong-calls -mframe-header-opt -march=r2k

OBJS= autcel

all: autcel autcel_mips

autcel_mips: main.c proximo.S pbmWriter.c utils.c
	gcc -g $^ -o $@ 

autcel: main.c pbmWriter.c proximo.c utils.c
	gcc -g $^ -o $@

run_test: autcel
	./test/test.sh

run_test_mips: autcel_mips
	./test/test_mips.sh

.PHONY : clean
clean:
	rm autcel*