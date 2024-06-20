lw x18, var1
lw x19, var2
lw x20, res

#contador
addi x6, x0, 5 

#tentando fazer uma multiplicacao entre dois valores
multiplica_loop: 
    andi x5, x18, 1 #x14 = x11 & 1
    bne x5, x0, pula_adicao # x5 != x0
    add x20, x20, x18 #x20 = x20 + x18

pula_adicao:
    slli x18, x18, 1 #x18 = x18 << 1
    srli x19, x19, 1 #x19 = x19 >> 1 
    addi x6, x6, -1
    bne x6, x0, multiplica_loop

#registrando o resultado na memória
sw x11, prod

halt

var1: .word 5 
var2: .word 2 
prod: .word 0xf