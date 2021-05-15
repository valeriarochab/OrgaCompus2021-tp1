
.align 2
.globl proximo
.ent proximo

	####################### STACK FRAME ######################

	#	+---------------+
	# 36	|		|	\
	#	+---------------+	|
	# 32	|		|	|
	#	+---------------+	|	ABA CALLER
	# 28	|	a1	|	|
	#	+---------------+	|
	# 24	|	a0	|	/
	# 	+---------------+
	# 20	|	fp	|	\
	# 	+---------------+	|   SRA
	# 16	|	gp	|	/
	# 	+---------------+
	# 12	|		|	\
	# 	+---------------+	|
	# 8		|		|	|
	# 	+---------------+	|   LTA
	# 4		|   	|	|
	# 	+---------------+	|
	# 0		|   	|	/
	# 	+---------------+

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