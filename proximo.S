
.align 2
.globl proximo
.ent proximo

proximo:
	.frame fp, 24, ra

	#bloque para codigo pic
	.set noreorder
	.cpload t9
	.set reorder

	#creo stack frame, determinar espacio
	subu	sp, sp, 24

	#bloque para codigo pic
	.cprestore 16

	# salvando el callee
	sw	fp, 20(sp)

	move  fp, sp