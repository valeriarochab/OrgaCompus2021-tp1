#include <sys/regdef.h>

/* Stack size */
#define SS 8

/* SRA Offsets */
#define O_GP 4
#define O_FP 0


.text
.align 2

/*
unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N)
Devuelve el valor que va tener la celda [i + 1, j]
*/

.globl proximo
.ent proximo

proximo:
	subu sp, sp, SS
	/* SRA */
	sw gp, O_GP(sp)
	sw fp, O_FP(sp)

	move fp, sp

	sw a0, SS(fp)
	sw a1, (SS + 4)(fp)
	sw a2, (SS + 8)(fp)
	/* promoted to 32 bit */
	sw a3, (SS + 12)(fp)
	
	lw t0, (SS + 16)(fp)
	
	/* $t1 = (N * i) */
	mul t1, t0, a1

	/* $t2 = a[(N * i) + ((j - 1 + N) % N)] */
	addiu t2, a2, -1
	addu t2, t2, t0
	divu t2, t0
	mfhi t2
	addu t2, t2, t1
	addu t2, a0, t2
	lbu t2, 0(t2)
	
	/* $t3 = a[(N * i) + j] */
	addu t3, a2, t1
	addu t3, a0, t3
	lbu t3, 0(t3)

	/* $t4 = a[(N * i) + ((j + 1) % N)] */
	addiu t4, a2, 1
	divu t4, t0
	mfhi t4
	addu t4, t4, t1
	addu t4, a0, t4
	lbu t4, 0(t4)
	
	/* t0 = a3 >> (t2 << 2 | t3 << 1 | t4) */
	/* t0 = a3 >> (t2 << 2) */
	sll t2, t2, 2
	srlv t0, a3, t2
	/* t0 = t0 >> (t3 << 1) */
	sll t3, t3, 1
	srlv t0, t0, t3
	/* t0 = t0 >> t4 */
	srlv t0, t0, t4
	
	/* v0 = t0 & 1 */
	andi v0, t0, 1
	
	/* Stack unwinding */
	lw fp, O_FP(sp)
	lw gp, O_GP(sp)
	
	addiu sp, sp, SS
	jr ra
.end proximo
