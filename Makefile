CFLAGS= -mno-mips16 -mgp32 -mfp32 -gpubnames  -mlong32 -mips1 -mabicalls -mlong-calls -mframe-header-opt -march=r2k

OBJS= tp1

all: tp1 tp1_mips

tp1_mips:main.c
	gcc -g $^ -o $@ 

tp1: main.c 
	gcc -g $^ -o $@

clean:
	rm tp1*