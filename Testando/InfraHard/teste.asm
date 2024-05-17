# inicializando as variaveis da memória
lw x18, a
lw x19, b
lw x20, c
#==========================================================================================================
# criando auxiliares que serão utilizados no decorrer do código
addi x28, x0, 0 #contador
addi x29, x0, 43 #'+'
addi x30, x0, 45 #'-'
addi x31, x0, 0x30 #0 em Hex na ASCII
# x18 -> a, x19-> b e x20 ->c
#==========================================================================================================
# carregando o valores
loop:
	lb x5, 1025(x0)
	beq x5, x29, continue
	beq x5, x30, continue
	beq x0, x0, loop
continue:
	lb x6, 1025(x0)
	lb x7, 1025(x0)
	sub x6, x6, x31  
	sub x7, x7, x31
	beq x5, x29, mais
	beq x5, x30, menos
mais:
	addi x28, x28, 1 #incrementando o contador
	slli x5, x6, 1 #vezes 2
	slli x6, x6, 3 #vezes 8
	add x6, x5, x6 #vezes 2 + vezes 8 = vezes 10
	add x6, x6, x7 #dezena + unidade
	# se for para salvar no a (x18)
	addi x5, x0, 1
	beq x5, x28, A	
	# se for para salvar no b (x19)
	addi x5, x0, 2
	beq x5, x28, B
	#se for para salvar no c (x20)
	addi x5, x0, 3
	beq x5, x28, C
menos:
	addi x28, x28, 1 #incrementando o contador
	slli x5, x6, 1 #vezes 2
	slli x6, x6, 3 #vezes 8
	add x6, x5, x6 #vezes 2 + vezes 8 = vezes 10
	add x6, x6, x7 #dezena + unidade
	sub x6, x0, x6 #transformando em negativo
	# se for para salvar no a (x18)
	addi x5, x0, 1
	beq x5, x28, A		
	# se for para salvar no b (x19)
	addi x5, x0, 2
	beq x5, x28, B
	#se for para salvar no c (x20)
	addi x5, x0, 3
	beq x5, x28, C
#=====================================================
A:
	add x18, x0, x6
	sw x18, a
	beq x0, x0, loop
B:
	add x19, x0, x6
	sw x19, b
	beq x0, x0, loop
C:
	add x20, x0, x6
	sw x20, c
#==========================================================================================================
#colocando o valor de x em um registrador
lw x11, x
# x = 0 
add x11, x0, x0
# a >= 5
addi x5, x0, 5
bge x18, x5, if1
beq x0, x0, else
# b < 66 (b <= 65)
if1:
	addi x5, x0, 66
	blt x19, x5, if2
	beq x0, x0, else
# c >= 16 (c > 15)
if2:
	addi x5, x0, 16
	bge x20, x5, if3
	beq x0, x0, else
# x = 1
if3:
	addi x11, x0, 1
# atualiza o valor de x na memória e halt
else:
	sw x11, x
	addi x11, x11, 0x30
	sb x11, 1024(x0)
	halt
a: .word 0x0
b: .word 0x0
c: .word 0x0
x: .word 0xf
