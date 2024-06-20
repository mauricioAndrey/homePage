#consegui fazer uma divisão 
lw x5, a        # Carregar dividendo em x11
lw x6, b        # Carregar divisor em x12

add x7, x0, x0  # Inicializar contador em 0
addi x28, x0, 32  # Limite de 32 bits

add x31, x0, x0  # Inicializar quociente em 0
add x30, x0, x0  # Inicializar resto em 0

loop:
	slli x30, x30, 1 # Deslocar resto à esquerda
	srli x9, x5, 31   # Deslocar dividendo à direita (alinhando para comparação)
	or x30, x30, x9  # Adicionar próximo bit do dividendo ao resto
	slli x5, x5, 1 	

	bge x30, x6, bigger # Se resto >= divisor
	bge x0, x0, jump 

	bigger:
		sub x30, x30, x6  # Subtrair divisor do resto
		addi x31, x31, 1  # Incrementar quociente
	
	jump:
		slli x31, x31, 1
		addi x7, x7, 1  # Incrementar contador
		blt x7, x28, loop # Repetir até atingir o limite de 32 bits
	#ajuste 
	srli x31, x31, 1

halt

a: .word 22       # Dividendo
b: .word 5        # Divisor

