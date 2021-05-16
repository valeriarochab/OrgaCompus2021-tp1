CFLAGS= -mno-mips16 -mgp32 -mfp32 -gpubnames  -mlong32 -mips1 -mabicalls -mlong-calls -mframe-header-opt -march=r2k

OBJS= tp1

all: tp1 tp1_mips

tp1_mips: main.c proximo.S pbmWriter.c
	gcc -g $^ -o $@ 

tp1: main.c pbmWriter.c proximo.c
	gcc -g $^ -o $@

run_test: tp1
	./tp1 126 80 test/firstTest output

run_test_mips: tp1_mips
	./tp1_mips 126 80 test/firstTest output

.PHONY : clean
clean:
	rm tp1*